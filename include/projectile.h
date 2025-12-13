#ifndef __PROJETIL_H__
#define __PROJETIL_H__

#include <stdio.h>

typedef struct {
    int x;
    int y;
    int dx;       
    int dy;        
    int ativo;    
    const char *aparencia; 
    int contador_frames; 
    int velocidade;
    int dano;
} Projetil;


#define MAX_PROJETIL_SIMPLES 10
#define MAX_PROJETIL_ESPECIAL 8
#define VELOCIDADE_PROJETIL 1

typedef struct {
    Projetil projeteis[MAX_PROJETIL_SIMPLES + MAX_PROJETIL_ESPECIAL];
    int quantidade_simples;
    int quantidade_especial; 
} GerenciadorProjetil;


void gerenciadorProjetilIniciar(GerenciadorProjetil *gp);
void gerenciadorProjetilDestruir(GerenciadorProjetil *gp);

void projetilCriar(GerenciadorProjetil *gp, int x, int y, int dx, int dy,int modo);
void projetilCriarEspecial(GerenciadorProjetil *gp, int x, int y, int dx, int dy,int modo);

void gerenciadorProjetilDesenhar(const GerenciadorProjetil *gp);

void gerenciadorProjetilLimpar(const GerenciadorProjetil *gp);
void gerenciadorProjetilAtualizar(GerenciadorProjetil *gp);

void gerenciadorProjetilCompactar(GerenciadorProjetil *gp);

#endif /* __PROJECTILE_H__ */
