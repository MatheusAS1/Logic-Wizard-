#ifndef __ITEM_H__
#define __ITEM_H__

#include <stdio.h>

typedef struct {
    int x;
    int y;
    int ativo;
    char expressao[32];
} Bau;

typedef struct {
    Bau *baus;
    int quantidade;
    int max_baus;
} GerenciadorBau;

void gerenciadorBauIniciar(GerenciadorBau *gb, int max_baus);

void gerenciadorBauDestruir(GerenciadorBau *gb);

void bauSpawn(GerenciadorBau *gb, int x, int y, const char *expressao);

void gerenciadorBauDesenhar(const GerenciadorBau *gb);

void gerenciadorBauLimpar(const GerenciadorBau *gb);

int gerenciadorBauVerificarColisao(const GerenciadorBau *gb, int px, int py);

void bauRemover(GerenciadorBau *gb, int index);

void gerenciadorBauCompactar(GerenciadorBau *gb);

#endif /* __ITEM_H__ */