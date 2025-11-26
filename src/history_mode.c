#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "storage.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "character.h"
#include "projectile.h"
#include "enemy.h"
#include "npc.h"
#include "logic.h"
#include "item.h"
#include "desafio_bau.h"
#include "desafio_boss.h"
#include "game_input.h"
#include "collision.h"
#include "game_progression.h"
#include "game_render.h"
#include "ui.h"
#include "menu.h" 
#include "creditos.h"
#include "boss_final.h"

void iniciarModoHistoria()
{
    exibirNarrativaHistoria();
    screenInit(1);
    keyboardInit();
    timerInit(50); 
    srand(time(NULL));

    Character jogador;
    GerenciadorProjetil gp;
    GerenciadorInimigo gi;
    GerenciadorBau gb;
    Boss boss;

    memset(&jogador, 0, sizeof(Character));
    memset(&gp, 0, sizeof(GerenciadorProjetil));
    memset(&gi, 0, sizeof(GerenciadorInimigo));
    memset(&gb, 0, sizeof(GerenciadorBau));
    memset(&boss, 0, sizeof(Boss));
    
    EstadoDesafioBau desafio_bau;
    EstadoDesafioBoss desafio_boss;

    memset(&desafio_bau, 0, sizeof(EstadoDesafioBau));
    memset(&desafio_boss, 0, sizeof(EstadoDesafioBoss));
    
    int tecla = 0;
    int contador_frames = 0;
    int fps_atual = 0;
    
    int base_enemy_count = 2;
    int base_enemy_life = 2;
    int base_boss_life = 10;
    int boss_life_final = 0;
    int level = 1;
    int boss_spawned = 0;
    int boss_timer = 0;
    int score = 0;
    int velocidade_inicial = 10;
    int velocidade_final = 0;
    
    int recorde_atual = storageCarregarRecorde();

    const char *nomes_bosses[11] = {
        "",                     
        "Soldado da lógica",          
        "O Sofista Macabro",       
        "O Cavaleiro do axioma",           
        "Templário de PIF",          
        "Carrasco da recursividade",         
        "Assassino de memória",          
        "Sanguinário da tautologia",        
        "Destruidor da tabela verdade",         
        "Malenia lamina de Utron",        
        "NÚCLEO CORROMPIDO (O TENEBROSO)"       
    };

    SistemaLogica *sl = (SistemaLogica*)malloc(sizeof(SistemaLogica));
    memset(sl, 0, sizeof(SistemaLogica));
    if (sl == NULL) {
        screenDestroy();
        printf("ERRO FATAL: Falha de memória (SistemaLogica).\n");
        exit(1); 
    }

    logicaIniciar(sl);
    desafioBauIniciar(&desafio_bau);
    desafioBossIniciar(&desafio_boss);
    
    gerenciadorProjetilIniciar(&gp);
    gerenciadorInimigoIniciar(&gi, base_enemy_count * level);
    gerenciadorBauIniciar(&gb, 10);

    characterInit(&jogador, 40, 12, "(-_-)/*");
    jogador.lives = 3;
    
    characterDraw(&jogador);
    screenUpdate();

    for (int i = 0; i < base_enemy_count * level; ++i) {
        int x = (rand() % (MAXX - MINX - 6)) + MINX + 2;
        int y = (rand() % (MAXY - MINY - 2)) + MINY + 1;
        inimigoSpawn(&gi, x, y, base_enemy_life * level, 
                     velocidade_inicial - (level > 1 ? level-1 : 0));
    }

    while (tecla != 27 && jogador.lives > 0 && level <= 10)
    {
        if (timerTimeOver()) {
            int px, py;
            characterClear(&jogador);
            gerenciadorProjetilLimpar(&gp);
            gerenciadorInimigoLimpar(&gi);
            gerenciadorBauLimpar(&gb);
            if (boss.eh_final) {
                bossFinalLimpar(&boss); 
            }
            else{
                bossLimpar(&boss);
            }
            
            if (boss_spawned && boss.ativo && boss.desafio_ativo) {
                bossLimparEquivalencia(&boss);
            }

            if (!desafioBauEstaAtivo(&desafio_bau) && !desafioBossEstaAtivo(&desafio_boss)) {
                uiLimparAreaDesafio();
                uiLimparAreaInput();
            }

            tecla = 0;
            if (desafioBauEstaAtivo(&desafio_bau)) {
                desafioBauProcessarInput(&desafio_bau, &gb, &jogador, &score);
                desafioBauDesenharInterface(&desafio_bau);
            }
            else if (desafioBossEstaAtivo(&desafio_boss)) {
                desafioBossProcessarInput(&desafio_boss, &boss, &jogador, &score);
                desafioBossDesenharInterface(&desafio_boss);
            }
            else {
                processarInputJogador(&jogador, &gp);
            }

            gerenciadorProjetilAtualizar(&gp);
            characterGetPos(&jogador, &px, &py);
            
            if(!desafioBauEstaAtivo(&desafio_bau) && !desafioBossEstaAtivo(&desafio_boss)){
                gerenciadorInimigoAtualizar(&gi, px, py);
                if (boss.eh_final) {
                    bossFinalAtualizar(&boss, px, py); 
                    bossFinalVerificarColisaoTiro(&boss, &jogador); 
                } else {
                    bossAtualizar(&boss, px, py);
                }
            }
            
            if (!desafioBauEstaAtivo(&desafio_bau) && !desafioBossEstaAtivo(&desafio_boss)) {
                int bau_colidido = gerenciadorBauVerificarColisao(&gb, px, py);
                if (bau_colidido != -1) {
                    desafioBauAtivar(&desafio_bau, bau_colidido);
                }
            }

            if (!boss_spawned && gi.quantidade == 0) {
                boss_timer++;
                if (boss_timer >= 100) {
                    if(level < 4){
                        velocidade_final = velocidade_inicial - (level > 1 ? (level-1) * 1.1: 0);
                        boss_life_final = base_boss_life * (1 << (level-1));
                    }
                    else if(level < 6){
                        velocidade_final = 5;
                        boss_life_final = boss_life_final + 10;
                    }
                    else if(level < 8){
                        velocidade_final = 4;
                        boss_life_final = boss_life_final + 8;
                    }
                    else{
                        velocidade_final = 3;
                        boss_life_final = boss_life_final + 8;
                    }
                    char mensagem_boss[64];
                    sprintf(mensagem_boss, "*** %s ***", nomes_bosses[level]);
                    uiLimparAreaInput();                
                    uiMostrarFeedback(mensagem_boss, RED, 2000, MAXX / 2 - 15, MAXY / 2);
                    if(level == 10){
                        bossFinalIniciar(&boss, (MINX + MAXX) / 2 - 3, MINY + 1, 
                         100, 
                         7, 
                         sl);
                    }
                    else{
                        bossIniciar(&boss, (MINX + MAXX) / 2 - 3, MINY + 1, 
                               boss_life_final,velocidade_final, 
                               sl); 
                    }
                    boss_spawned = 1;
                }
            } else if (gi.quantidade > 0) {
                boss_timer = 0;
            }

            if (boss_spawned && boss.ativo) {
                if (!desafioBossEstaAtivo(&desafio_boss) && !boss.desafio_ativo) {
                    if (boss.vida <= 6 ) {
                        boss.desafio_ativo = 1;
                        desafioBossAtivar(&desafio_boss);
                        uiMostrarFeedback("*** DESAFIO LOGICO ATIVADO! ***", YELLOW, 1000, 
                                         MAXX / 2 - 15, MAXY / 2 - 2);
                    }
                }
            }

            processarColisaoJogadorInimigos(&jogador, &gi, px, py);
            processarColisaoJogadorBoss(&jogador, &boss, px, py, desafioBossEstaAtivo(&desafio_boss));
            processarColisaoProjeteis(&gp, &gi, &boss, &gb, &score, boss_spawned, 
                                     desafioBossEstaAtivo(&desafio_boss));

            if (boss_spawned && !boss.ativo) {
                int em_desafio_temp = 0;
                avancarProximoLevel(&level, &gi, &gp, &jogador, sl, &boss, &gb,
                                   &boss_spawned, &boss_timer, &em_desafio_temp,
                                   base_enemy_count, base_enemy_life, velocidade_inicial);
            }

            renderizarJogo(&jogador, &gp, &gi, &gb, &boss, boss_spawned, sl,level);

            gerenciadorProjetilCompactar(&gp);
            gerenciadorInimigoCompactar(&gi);
            gerenciadorBauCompactar(&gb);

            contador_frames++;
            if (contador_frames >= 20) {
                fps_atual = contador_frames;
                contador_frames = 0;
            }
            
            if (score > recorde_atual) {
                recorde_atual = score;
            }
            
            uiDesenharHUDSuperior(score, level, jogador.lives, gi.quantidade, 
                                 boss.ativo ? boss.vida : 0, gb.quantidade, fps_atual, recorde_atual);
            
            uiDesenharHUDInferior(px, py);
            screenUpdate();
        }
    }

    if (jogador.lives <= 0) {
        screenClear();
        screenGotoxy(MAXX / 2 - 10, MAXY / 2 - 2);
        screenSetColor(RED, DARKGRAY);
        screenSetBold();
        printf("GAME OVER");
        screenSetNormal();
        
        screenGotoxy(MAXX / 2 - 10, MAXY / 2);
        screenSetColor(YELLOW, DARKGRAY);
        printf("Score Final: %d", score);
        
        screenGotoxy(MAXX / 2 - 10, MAXY / 2 + 1);
        screenSetColor(WHITE, DARKGRAY);
        printf("Level Alcancado: %d", level);
        
        screenGotoxy(1, MAXY);
        screenUpdate();
        sleep(5);
    }
    else{
        exibirTelaFinal();
    }
    
    storageSalvarRecorde(recorde_atual);

    characterDestroy(&jogador);
    gerenciadorProjetilDestruir(&gp);
    gerenciadorInimigoDestruir(&gi);
    gerenciadorBauDestruir(&gb);
    
    logicaDestruir(sl);
    free(sl); 
    sl = NULL;
    
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    
}