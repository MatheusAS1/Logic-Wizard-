#ifndef __INIMIGO_H__
#define __INIMIGO_H__

#include <stdio.h>
#include "logic.h"

typedef struct {
    int x, y;
    int dx, dy; 
    int ativo;
} ProjetilBoss;

typedef struct {
    int x;
    int y;
    int vida;
    int ativo;
    int contador_frames;
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
    int vida_maxima; 
    int ativo;
    int velocidade;
    int contador_frames;
    int desafio_ativo;
    Equivalencia equivalencia;
    
    int eh_final;          
    int timer_tiro;
    int fase_2;  
    int disparos;    
    ProjetilBoss tiros[40]; 
} Boss;

void gerenciadorInimigoIniciar(GerenciadorInimigo *gi, int max_inimigos);
void gerenciadorInimigoDestruir(GerenciadorInimigo *gi);
void inimigoSpawn(GerenciadorInimigo *gi, int x, int y, int vida, int velocidade);
void gerenciadorInimigoDesenhar(const GerenciadorInimigo *gi);
void gerenciadorInimigoLimpar(const GerenciadorInimigo *gi);
void gerenciadorInimigoAtualizar(GerenciadorInimigo *gi, int px, int py);
void gerenciadorInimigoCompactar(GerenciadorInimigo *gi);
void bossIniciar(Boss *boss, int x, int y, int vida, int velocidade, SistemaLogica *sl);
void bossDesenhar(const Boss *boss);
void bossLimpar(const Boss *boss);
void bossAtualizar(Boss *boss, int px, int py);
void bossDesenharEquivalencia(const Boss *boss);
void bossLimparEquivalencia(const Boss *boss);
Inimigo* inimigoGetByIndex(GerenciadorInimigo *gi, int index);
int inimigoEncontrarMaisProximo(const GerenciadorInimigo *gi, int px, int py);

#endif /* __ENEMY_H__ */