#include "boss_final.h"
#include "screen.h"
#include <stdlib.h>
#include <string.h>

#define TIRO_VELOCIDADE 1 

void bossFinalIniciar(Boss *boss, int x, int y, int vida, int velocidade, SistemaLogica *sl) {

    bossIniciar(boss, x, y, vida, velocidade, 0,sl);
    

    boss->eh_final = 1;
    boss->timer_tiro = 0;
    boss->fase_2 = 0;
    boss->disparos = 0;
    

    for (int i = 0; i < 40; i++) {
        boss->tiros[i].ativo = 0;
    }
}

void disparar4Direcoes(Boss *boss) {
    int dirs[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    
    int criados = 0;
    for (int i = 0; i < 40; i++) {
        if (!boss->tiros[i].ativo) {
            boss->tiros[i].x = boss->x + 3; 
            boss->tiros[i].y = boss->y;
            boss->tiros[i].dx = dirs[criados][0];
            boss->tiros[i].dy = dirs[criados][1];
            boss->tiros[i].ativo = 1;
            
            criados++;
            if (criados >= 4) break; 
        }
    }
}

void bossFinalAtualizar(Boss *boss, int px, int py) {
    if (!boss || !boss->ativo) return;

    boss->contador_frames++;
    if (boss->contador_frames >= boss->velocidade) {
        if (boss->x < px) boss->x++;
        else if (boss->x > px) boss->x--;
        
        if (boss->y < py) boss->y++;
        else if (boss->y > py) boss->y--;
        
        boss->contador_frames = 0;
    }


    boss->timer_tiro++;
    if ((boss->timer_tiro >= 30 + (rand() % 20))&& boss->disparos ==1) { 
        disparar4Direcoes(boss);
        boss->timer_tiro = 0;
    }

 
    for (int i = 0; i < 40; i++) {
        if (boss->tiros[i].ativo) {
            boss->tiros[i].x += boss->tiros[i].dx * 2; 
            boss->tiros[i].y += boss->tiros[i].dy * 1;

            if (boss->tiros[i].x <= MINX || boss->tiros[i].x >= MAXX ||
                boss->tiros[i].y <= MINY || boss->tiros[i].y >= MAXY) {
                boss->tiros[i].ativo = 0;
            }
        }
    }
}

void bossFinalDesenhar(const Boss *boss) {
    if (!boss || !boss->ativo) return;

    screenGotoxy(boss->x, boss->y);
    screenSetColor(RED, BLACK); 
    screenSetBold();
    printf("/(Ò_Ó)\\"); 
    screenSetNormal();

    screenSetColor(YELLOW, DARKGRAY);
    for (int i = 0; i < 40; i++) {
        if (boss->tiros[i].ativo) {
            screenGotoxy(boss->tiros[i].x, boss->tiros[i].y);
            printf("*"); 
        }
    }
}

void bossFinalLimpar(const Boss *boss) {
    if (!boss) return;
    
    if (boss->ativo) {
        screenGotoxy(boss->x, boss->y);
        printf("       "); 
    }

    for (int i = 0; i < 40; i++) {
        if (boss->tiros[i].ativo) {
            screenGotoxy(boss->tiros[i].x, boss->tiros[i].y);
            printf(" ");
        }
    }
}

void bossFinalVerificarColisaoTiro(Boss *boss, Character *jogador) {
    if (!boss || !boss->ativo || !jogador) return;

    for (int i = 0; i < 40; i++) {
        if (boss->tiros[i].ativo) {
            if (boss->tiros[i].x == jogador->x && boss->tiros[i].y == jogador->y) {
                jogador->lives--;
                boss->tiros[i].ativo = 0; 
                
                screenSetColor(RED, YELLOW);
                screenGotoxy(jogador->x, jogador->y);
                printf("X");
            }
        }
    }
}