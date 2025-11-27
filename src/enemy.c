#include "enemy.h"
#include "logic.h"
#include "screen.h"
#include <stdlib.h>
#include <string.h>

#define INIMIGO_VELOCIDADE 4000

void gerenciadorInimigoIniciar(GerenciadorInimigo *gi, int max_inimigos) {
    if (!gi) return;
    gi->inimigos = (Inimigo*)malloc(sizeof(Inimigo) * max_inimigos);
    gi->quantidade = 0;
    gi->max_inimigos = max_inimigos;
    for (int i = 0; i < max_inimigos; ++i) {
        gi->inimigos[i].ativo = 0;
        gi->inimigos[i].contador_frames = 0;
    }
}

void gerenciadorInimigoDestruir(GerenciadorInimigo *gi) {
    if (!gi) return;
    free(gi->inimigos);
    gi->inimigos = NULL;
    gi->quantidade = 0;
    gi->max_inimigos = 0;
}

void inimigoSpawn(GerenciadorInimigo *gi, int x, int y, int vida, int velocidade) {
    if (!gi || gi->quantidade >= gi->max_inimigos) return;
    
    Inimigo *ini = &gi->inimigos[gi->quantidade];
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
        const Inimigo *ini = &gi->inimigos[i];
        if (ini->ativo) {
            screenGotoxy(ini->x, ini->y);
            screenSetColor(MAGENTA, DARKGRAY);
            printf("|*~*|");
        }
    }
}

void gerenciadorInimigoLimpar(const GerenciadorInimigo *gi) {
    if (!gi) return;
    for (int i = 0; i < gi->quantidade; ++i) {
        const Inimigo *ini = &gi->inimigos[i];
        if (ini->ativo) {
            if (ini->x > MINX && ini->x + 4 < MAXX && ini->y > MINY && ini->y < MAXY) {
                screenGotoxy(ini->x, ini->y);
                printf("     ");
                screenGotoxy(ini->x - 1, ini->y - 1);
                printf("          ");
            }
        }
    }
}

void gerenciadorInimigoAtualizar(GerenciadorInimigo *gi, int px, int py) {
    if (!gi) return;
    for (int i = 0; i < gi->quantidade; ++i) {
        Inimigo *ini = &gi->inimigos[i];
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
        if (gi->inimigos[i].ativo) { 
            if (i != write_idx) {
                gi->inimigos[write_idx] = gi->inimigos[i]; 
            }
            write_idx++; 
        }
    }
    gi->quantidade = write_idx; 
}

Inimigo* inimigoGetByIndex(GerenciadorInimigo *gi, int index) {
    if (!gi || index < 0 || index >= gi->quantidade) return NULL;
    return &gi->inimigos[index];
}

int inimigoEncontrarMaisProximo(const GerenciadorInimigo *gi, int px, int py) {
    if (!gi) return -1;
    
    int menor_dist = 9999;
    int index_mais_proximo = -1;
    
    for (int i = 0; i < gi->quantidade; ++i) {
        const Inimigo *ini = &gi->inimigos[i];
        if (!ini->ativo) continue;
        
        int dist_x = abs(ini->x - px);
        int dist_y = abs(ini->y - py);
        int dist = dist_x + dist_y;
        
        if (dist < menor_dist) {
            menor_dist = dist;
            index_mais_proximo = i;
        }
    }
    
    return index_mais_proximo;
}


void bossIniciar(Boss *boss, int x, int y, int vida, int velocidade, int variante, SistemaLogica *sl) {
    if (!boss) return;
    boss->x = x;
    boss->y = y;
    boss->vida = vida;
    boss->vida_maxima = vida;
    boss->ativo = 1;
    boss->velocidade = velocidade;
    boss->contador_frames = 0;
    boss->desafio_ativo = 0;
    boss->variante = variante; 
    
    if (sl) {
        boss->equivalencia = logicaGetEquivalenciaAleatoria(sl);
    }
}

void bossDesenhar(const Boss *boss) {
    if (!boss || !boss->ativo) return;
    
    screenGotoxy(boss->x, boss->y);
    switch (boss->variante) {
        case 1:
            screenSetColor(LIGHTRED, DARKGRAY);
            printf("<(o_o)>");
            break;
        case 2: 
            screenSetColor(CYAN, DARKGRAY);
            printf("[ Ò_Ó ]");
            break;
        case 3: 
            screenSetColor(YELLOW, DARKGRAY);
            printf("/X..X\\");
            break;
        case 4: 
            screenSetColor(MAGENTA, DARKGRAY);
            printf("{[#_#]}");
            break;
        case 5: 
            screenSetColor(WHITE, DARKGRAY);
            printf("~(ºoº)~");
            break;
        case 6: 
            screenSetColor(GREEN, DARKGRAY);
            printf("<$##$>");
            break;
        case 7: 
            screenSetColor(BLUE, DARKGRAY);
            printf("\\^v^v^/");
            break;
        case 8: 
            screenSetColor(LIGHTRED, DARKGRAY);
            printf("<<@_@>>");
            break;
        case 9: 
            screenSetColor(RED, DARKGRAY);
            screenSetBold();
            printf("-(!_!)-");
            screenSetNormal();
            break;
        default: 
            screenSetColor(RED, DARKGRAY);
            printf("<(º#º)>");
            break;
    }
}

void bossLimpar(const Boss *boss) {
    if (!boss || !boss->ativo) return;
    screenGotoxy(boss->x, boss->y);
    printf("         "); 
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

void bossDesenharEquivalencia(const Boss *boss) {
    if (!boss || !boss->ativo || !boss->desafio_ativo) return;
    if(boss->y > 3){
        screenGotoxy(boss->x - 2, boss->y - 1);
    } else {
        screenGotoxy(boss->x - 2, boss->y + 1);
    }
    screenSetColor(boss->equivalencia.cor, DARKGRAY);
    screenSetBold();
    printf("[%s]", boss->equivalencia.forma_equivalente);
    screenSetNormal();
}

void bossLimparEquivalencia(const Boss *boss) {
    if (!boss) return;
    
    screenGotoxy(boss->x - 2, boss->y - 1);
    printf("                    ");
    screenGotoxy(boss->x - 2, boss->y + 1);
    printf("                    ");
}