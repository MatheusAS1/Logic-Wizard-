#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
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

int main()
{
    Character jogador;
    GerenciadorProjetil gp;
    GerenciadorInimigo gi;
    GerenciadorBau gb;
    Boss boss;
    SistemaLogica sl;
    EstadoDesafioBau desafio_bau;
    EstadoDesafioBoss desafio_boss;
    int tecla = 0;
    
    int contador_frames = 0;
    int fps_atual = 0;
    int base_enemy_count = 2;
    int base_enemy_life = 2;
    int base_boss_life = 10;
    int level = 1;
    int boss_spawned = 0;
    int boss_timer = 0;
    int score = 0;
    int velocidade_inicial = 10;

    exibirTelaIntroducao();
    
    screenInit(1);
    keyboardInit();
    timerInit(50);
    
    srand(time(NULL));
    
    logicaIniciar(&sl);
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
                    velocidade_inicial - (level > 1 ? level-1 : 0), &sl);
    }

    while (tecla != 27 && jogador.lives > 0)
    {
        if (timerTimeOver()) {
            int px, py;

            characterClear(&jogador);
            gerenciadorProjetilLimpar(&gp);
            gerenciadorInimigoLimpar(&gi);
            gerenciadorBauLimpar(&gb);
            bossLimpar(&boss);
            
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
            gerenciadorInimigoAtualizar(&gi, px, py);

            if (!desafioBauEstaAtivo(&desafio_bau) && !desafioBossEstaAtivo(&desafio_boss)) {
                int bau_colidido = gerenciadorBauVerificarColisao(&gb, px, py);
                if (bau_colidido != -1) {
                    desafioBauAtivar(&desafio_bau, bau_colidido);
                }
            }

            if (!boss_spawned && gi.quantidade == 0) {
                boss_timer++;
                if (boss_timer >= 100) {
                    bossIniciar(&boss, (MINX + MAXX) / 2 - 3, MINY + 1, 
                               base_boss_life * (1 << (level-1)), 
                               velocidade_inicial - (level > 1 ? (level-1) * 2 : 0), 
                               &sl);
                    boss_spawned = 1;
                }
            } else if (gi.quantidade > 0) {
                boss_timer = 0;
            }

            if (boss_spawned && boss.ativo) {
                bossAtualizar(&boss, px, py);

                if (!desafioBossEstaAtivo(&desafio_boss) && !boss.desafio_ativo) {
                    if (boss.vida <= boss.vida_maxima / 2) {
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
                avancarProximoLevel(&level, &gi, &gp, &jogador, &sl, &boss, 
                                   &boss_spawned, &boss_timer, &em_desafio_temp,
                                   base_enemy_count, base_enemy_life, velocidade_inicial);
            }

            renderizarJogo(&jogador, &gp, &gi, &gb, &boss, boss_spawned, &sl);

            gerenciadorProjetilCompactar(&gp);
            gerenciadorInimigoCompactar(&gi);
            gerenciadorBauCompactar(&gb);

            contador_frames++;
            if (contador_frames >= 20) {
                fps_atual = contador_frames;
                contador_frames = 0;
            }

            uiDesenharHUDSuperior(score, level, jogador.lives, gi.quantidade, 
                                 boss.ativo ? boss.vida : 0, gb.quantidade, fps_atual);
            
            characterGetPos(&jogador, &px, &py);
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

    characterDestroy(&jogador);
    gerenciadorProjetilDestruir(&gp);
    gerenciadorInimigoDestruir(&gi);
    gerenciadorBauDestruir(&gb);
    logicaDestruir(&sl);
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    
    return 0;
}