#ifndef __INIMIGO_H__
#define __INIMIGO_H__

#include <stdio.h>

typedef struct {
    int x;
    int y;
    int vida;
    int ativo; 
    int velocidade;
} Inimigo;

typedef struct {
    Inimigo *inimigos;
    int quantidade;
    int max_inimigos;
} GerenciadorInimigo;

typedef struct {
    int x;
    int y;
    int vida;
    int ativo;
    int velocidade;
    int contador_frames;
} Boss;

void gerenciadorInimigoIniciar(GerenciadorInimigo *gi, int max_inimigos);
void gerenciadorInimigoDestruir(GerenciadorInimigo *gi);

void inimigoSpawn(GerenciadorInimigo *gi, int x, int y, int vida, int velocidade);
void gerenciadorInimigoDesenhar(const GerenciadorInimigo *gi);
void gerenciadorInimigoLimpar(const GerenciadorInimigo *gi);
void gerenciadorInimigoAtualizar(GerenciadorInimigo *gi, int px, int py);
void gerenciadorInimigoCompactar(GerenciadorInimigo *gi);

void bossIniciar(Boss *boss, int x, int y, int vida, int velocidade);
void bossDesenhar(const Boss *boss);
void bossLimpar(const Boss *boss);
void bossAtualizar(Boss *boss, int px, int py);

#endif
