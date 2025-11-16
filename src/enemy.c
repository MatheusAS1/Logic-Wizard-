#include "enemy.h"
#include "screen.h"
#include <stdlib.h>

#define INIMIGO_VELOCIDADE 4000

typedef struct {
    int x;
    int y;
    int vida;
    int ativo;
    int contador_frames; 
    int velocidade;
} InimigoInterno;

void gerenciadorInimigoIniciar(GerenciadorInimigo *gi, int max_inimigos) {
    if (!gi) return;
    gi->inimigos = (Inimigo*)malloc(sizeof(InimigoInterno) * max_inimigos);
    gi->quantidade = 0;
    gi->max_inimigos = max_inimigos;
    for (int i = 0; i < max_inimigos; ++i) {
        ((InimigoInterno*)gi->inimigos)[i].ativo = 0;
        ((InimigoInterno*)gi->inimigos)[i].contador_frames = 0;
    }
}

void gerenciadorInimigoDestruir(GerenciadorInimigo *gi) {
    if (!gi) return;
    free(gi->inimigos);
    gi->inimigos = NULL;
    gi->quantidade = 0;
    gi->max_inimigos = 0;
}

void inimigoSpawn(GerenciadorInimigo *gi, int x, int y, int vida,int velocidade) {
    if (!gi || gi->quantidade >= gi->max_inimigos) return;
    InimigoInterno *ini = &((InimigoInterno*)gi->inimigos)[gi->quantidade];
    ini->x = x;
    ini->y = y;
    ini->vida = vida;
    ini->ativo = 1;
    ini->contador_frames = 0;
    ini->velocidade = velocidade;
    gi->quantidade++;
}

void gerenciadorInimigoDesenhar(const GerenciadorInimigo *gi) {
    if (!gi) return;
    for (int i = 0; i < gi->quantidade; ++i) {
        const InimigoInterno *ini = &((InimigoInterno*)gi->inimigos)[i];
        if (ini->ativo) {
            screenGotoxy(ini->x, ini->y);
            screenSetColor(YELLOW, DARKGRAY);
            printf("|*~*|");
        }
    }
}

void gerenciadorInimigoLimpar(const GerenciadorInimigo *gi) {
    if (!gi) return;
    for (int i = 0; i < gi->quantidade; ++i) {
        const InimigoInterno *ini = &((InimigoInterno*)gi->inimigos)[i];
        if (ini->ativo) {
            // Só limpa se não estiver na borda
            if (ini->x > MINX && ini->x + 4 < MAXX && ini->y > MINY && ini->y < MAXY) {
                screenGotoxy(ini->x, ini->y);
                printf("     ");
            }
        }
    }
}

void gerenciadorInimigoAtualizar(GerenciadorInimigo *gi, int px, int py) {
    if (!gi) return;
    for (int i = 0; i < gi->quantidade; ++i) {
        InimigoInterno *ini = &((InimigoInterno*)gi->inimigos)[i];
        if (!ini->ativo) continue;
        ini->contador_frames++;
        if (ini->contador_frames >= ini->velocidade) {
            if (ini->x < px) ini->x++;
            else if (ini->x > px) ini->x--;
            if (ini->y < py) ini->y++;
            else if (ini->y > py) ini->y--;
            ini->contador_frames = 0;
        }
    }
}

void gerenciadorInimigoCompactar(GerenciadorInimigo *gi) {
    if (!gi) return;
    int write_idx = 0;
    for (int i = 0; i < gi->quantidade; ++i) {
        InimigoInterno *inimigos = (InimigoInterno*)gi->inimigos;
        if (inimigos[i].ativo) { 
            if (i != write_idx) {
                inimigos[write_idx] = inimigos[i]; 
            }
            write_idx++; 
        }
    }
    gi->quantidade = write_idx; 
}

void bossIniciar(Boss *boss, int x, int y, int vida,int velocidade) {
    if (!boss) return;
    boss->x = x;
    boss->y = y;
    boss->vida = vida;
    boss->ativo = 1;
    boss->velocidade = velocidade;
    boss->contador_frames = 0;
}

void bossDesenhar(const Boss *boss) {
    if (!boss || !boss->ativo) return;
    screenGotoxy(boss->x, boss->y);
    screenSetColor(RED, DARKGRAY);
    printf("<(º#º)>.");
}

void bossLimpar(const Boss *boss) {
    if (!boss || !boss->ativo) return;
    screenGotoxy(boss->x, boss->y);
    printf("        "); 
}

void bossAtualizar(Boss *boss, int px, int py) {
    if (!boss || !boss->ativo) return;
    boss->contador_frames++;
    if (boss->contador_frames >= boss->velocidade) {
        if (boss->x < px) boss->x++;
        else if (boss->x > px) boss->x--;
        if (boss->y < py) boss->y++;
        else if (boss->y > py) boss->y--;
        boss->contador_frames = 0;
    }
}
