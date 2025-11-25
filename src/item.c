#include "item.h"
#include "screen.h"
#include <stdlib.h>
#include <string.h>

void gerenciadorBauIniciar(GerenciadorBau *gb, int max_baus) {
    if (!gb) return;
    gb->baus = (Bau*)malloc(sizeof(Bau) * max_baus);
    gb->quantidade = 0;
    gb->max_baus = max_baus;
    
    for (int i = 0; i < max_baus; ++i) {
        gb->baus[i].ativo = 0;
    }
}

void gerenciadorBauDestruir(GerenciadorBau *gb) {
    if (!gb) return;
    free(gb->baus);
    gb->baus = NULL;
    gb->quantidade = 0;
    gb->max_baus = 0;
}

void bauSpawn(GerenciadorBau *gb, int x, int y, const char *expressao) {
    if (!gb || gb->quantidade >= gb->max_baus) return;
    
    Bau *b = &gb->baus[gb->quantidade];
    b->x = x;
    b->y = y;
    b->ativo = 1;
    
    if (expressao) {
        strncpy(b->expressao, expressao, 31);
        b->expressao[31] = '\0';
    } else {
        strcpy(b->expressao, "~p");
    }
    
    gb->quantidade++;
}

void gerenciadorBauDesenhar(const GerenciadorBau *gb) {
    if (!gb) return;
    
    for (int i = 0; i < gb->quantidade; ++i) {
        const Bau *b = &gb->baus[i];
        if (b->ativo) {
            screenGotoxy(b->x, b->y);
            screenSetColor(YELLOW, DARKGRAY);
            screenSetBold();
            printf("[BAU]");
            screenSetNormal();
        }
    }
}

void gerenciadorBauLimpar(const GerenciadorBau *gb) {
    if (!gb) return;
    
    for (int i = 0; i < gb->quantidade; ++i) {
        const Bau *b = &gb->baus[i];
        if (b->ativo) {
            screenGotoxy(b->x, b->y);
            printf("     ");
        }
    }
}

int gerenciadorBauVerificarColisao(const GerenciadorBau *gb, int px, int py) {
    if (!gb) return -1;
    
    for (int i = 0; i < gb->quantidade; ++i) {
        const Bau *b = &gb->baus[i];
        if (!b->ativo) continue;

        if (px < b->x + 5 && px + 8 > b->x && py == b->y) {
            return i;
        }
    }
    
    return -1;
}

void bauRemover(GerenciadorBau *gb, int index) {
    if (!gb || index < 0 || index >= gb->quantidade) return;
    gb->baus[index].ativo = 0;
}

void gerenciadorBauCompactar(GerenciadorBau *gb) {
    if (!gb) return;
    
    int write_idx = 0;
    for (int i = 0; i < gb->quantidade; ++i) {
        if (gb->baus[i].ativo) {
            if (i != write_idx) {
                gb->baus[write_idx] = gb->baus[i];
            }
            write_idx++;
        }
    }
    gb->quantidade = write_idx;
}