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
#include "logic.h"
#include "item.h"
#include "desafio_bau.h"
#include "game_input.h"
#include "collision.h"
#include "game_progression.h"
#include "game_render.h"
#include "ui.h"

void iniciarModoArcade()
{
    screenInit(1);
    keyboardInit();
    timerInit(50); 
    srand(time(NULL));

    Character jogador;
    GerenciadorProjetil gp;
    GerenciadorInimigo gi;
    GerenciadorBau gb;

    memset(&jogador, 0, sizeof(Character));
    memset(&gp, 0, sizeof(GerenciadorProjetil));
    memset(&gi, 0, sizeof(GerenciadorInimigo));
    memset(&gb, 0, sizeof(GerenciadorBau));
    
    EstadoDesafioBau desafio_bau;
    memset(&desafio_bau, 0, sizeof(EstadoDesafioBau));
    
    int tecla = 0;
    int contador_frames = 0;
    int fps_atual = 0;
    
    int base_enemy_count = 3;
    int base_enemy_life = 2;
    int level = 1;
    int score = 0;
    int velocidade_inicial = 10;
    int bordas_renovadas = 1;
    int history_mode = 0;
    int recorde_atual = storageCarregarRecorde();

    SistemaLogica *sl = (SistemaLogica*)malloc(sizeof(SistemaLogica));
    memset(sl, 0, sizeof(SistemaLogica));
    if (sl == NULL) {
        screenDestroy();
        printf("ERRO FATAL: Falha de memória (SistemaLogica).\n");
        exit(1); 
    }

    logicaIniciar(sl);
    desafioBauIniciar(&desafio_bau);
    
    gerenciadorProjetilIniciar(&gp);
    gerenciadorInimigoIniciar(&gi, base_enemy_count);
    gerenciadorBauIniciar(&gb, 8);

    characterInit(&jogador, 40, 12, "(-_-)/*");
    jogador.lives = 3;
    
    characterDraw(&jogador);
    screenUpdate();

    for (int i = 0; i < base_enemy_count; ++i) {
        int x = (rand() % (MAXX - MINX - 6)) + MINX + 2;
        int y = (rand() % (MAXY - MINY - 2)) + MINY + 1;
        inimigoSpawn(&gi, x, y, base_enemy_life, velocidade_inicial);
    }

    screenGotoxy(MAXX / 2 - 15, MAXY / 2);
    screenSetColor(CYAN, DARKGRAY);
    screenSetBold();
    printf("*** MODO EXTERMÍNIO ***");
    screenSetNormal();
    screenGotoxy(MAXX / 2 - 20, MAXY / 2 + 2);
    screenSetColor(WHITE, DARKGRAY);
    printf("Sobreviva o máximo possível!");
    screenUpdate();
    sleep(2);

    while (tecla != 27 && jogador.lives > 0)
    {
        if (timerTimeOver()) {
            int px, py;
            characterClear(&jogador);
            gerenciadorProjetilLimpar(&gp);
            gerenciadorInimigoLimpar(&gi);
            gerenciadorBauLimpar(&gb);

            if (!desafioBauEstaAtivo(&desafio_bau)) {
                uiLimparAreaDesafio();
                uiLimparAreaInput();
            }

            tecla = 0;
            if (desafioBauEstaAtivo(&desafio_bau)) {
                desafioBauProcessarInput(&desafio_bau, &gb, &jogador, &score);
                desafioBauDesenharInterface(&desafio_bau);
            }
            else {
                tecla = processarInputJogador(&jogador, &gp,2);
            }

            gerenciadorProjetilAtualizar(&gp);
            characterGetPos(&jogador, &px, &py);
            
            if(!desafioBauEstaAtivo(&desafio_bau)){
                gerenciadorInimigoAtualizar(&gi, px, py);
            }
            
            if (!desafioBauEstaAtivo(&desafio_bau)) {
                int bau_colidido = gerenciadorBauVerificarColisao(&gb, px, py);
                if (bau_colidido != -1) {
                    desafioBauAtivar(&desafio_bau, bau_colidido);
                }
            }

            if (gi.quantidade == 0) {
                level++;
                
                int novos_inimigos = base_enemy_count + (level / 2);  
                int vida_inimigos = base_enemy_life + (level / 3);     
                int velocidade = velocidade_inicial - (level / 4);    
                if (velocidade < 3) velocidade = 3;                    

                char msg[50];
                sprintf(msg, "*** NÍVEL %d ***", level);
                uiMostrarFeedback(msg, CYAN, 1000, MAXX / 2 - 10, MAXY / 2);
                
                gerenciadorInimigoIniciar(&gi, novos_inimigos);
                for (int i = 0; i < novos_inimigos; ++i) {
                    int x = (rand() % (MAXX - MINX - 6)) + MINX + 2;
                    int y = (rand() % (MAXY - MINY - 2)) + MINY + 1;
                    inimigoSpawn(&gi, x, y, vida_inimigos, velocidade);
                }
                
                if (level % 3 == 0 && gb.quantidade < 15) {
                    int x = (rand() % (MAXX - MINX - 6)) + MINX + 2;
                    int y = (rand() % (MAXY - MINY - 2)) + MINY + 1;
                    const char *expressoes[] = {"~p", "p|q", "p&q", "p->q", "p<->q"};
                    const char *expr_bau = expressoes[rand() % 5];
                    bauSpawn(&gb, x, y, expr_bau);
                }
            }

            processarColisaoJogadorInimigos(&jogador, &gi, px, py);
            processarColisaoProjeteis(&gp, &gi, NULL, &gb, &score, 0, 0);

            Boss boss_vazio;
            memset(&boss_vazio, 0, sizeof(Boss));
            renderizarJogo(&jogador, &gp, &gi, &gb, &boss_vazio, 0, sl, level,bordas_renovadas,history_mode,0);

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
                                 0, gb.quantidade, fps_atual, recorde_atual,history_mode);
            uiDesenharHUDInferior(px, py);
            screenUpdate();
        }
    }

    if (jogador.lives <= 0) {
        screenClear();
        screenGotoxy(MAXX / 2 - 10, MAXY / 2 - 3);
        screenSetColor(RED, DARKGRAY);
        screenSetBold();
        printf("GAME OVER");
        screenSetNormal();
        
        screenGotoxy(MAXX / 2 - 10, MAXY / 2 - 1);
        screenSetColor(YELLOW, DARKGRAY);
        printf("Score Final: %d", score);
        
        screenGotoxy(MAXX / 2 - 10, MAXY / 2);
        screenSetColor(CYAN, DARKGRAY);
        printf("Nível Alcançado: %d", level);
        
        if (score == recorde_atual && score > 0) {
            screenGotoxy(MAXX / 2 - 10, MAXY / 2 + 2);
            screenSetColor(GREEN, DARKGRAY);
            screenSetBold();
            printf("*** NOVO RECORDE! ***");
            screenSetNormal();
        }
        
        screenGotoxy(1, MAXY);
        screenUpdate();
        sleep(5);
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
