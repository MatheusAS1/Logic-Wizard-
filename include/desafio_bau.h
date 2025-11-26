#ifndef DESAFIO_BAU_H
#define DESAFIO_BAU_H

#include "character.h"
#include "item.h"


typedef enum {
    DESAFIO_NEGACAO,      
    DESAFIO_CONJUNCAO,      
    DESAFIO_DISJUNCAO,      
    DESAFIO_IMPLICACAO,    
    DESAFIO_BICONDICIONAL   
} TipoDesafioBau;

typedef struct {
    int ativo;
    int bau_index;
    int tentativas;
    
    TipoDesafioBau tipo;    
    int linha_atual;        
    int total_linhas;      
    char respostas[4][2];    
    int idx_resposta_linha; 
    
} EstadoDesafioBau;

void desafioBauIniciar(EstadoDesafioBau *estado);
void desafioBauAtivar(EstadoDesafioBau *estado, int bau_index);
void desafioBauDesativar(EstadoDesafioBau *estado);
int desafioBauEstaAtivo(const EstadoDesafioBau *estado);

int desafioBauProcessarInput(EstadoDesafioBau *estado, GerenciadorBau *gb, 
                             Character *jogador, int *score);

void desafioBauDesenharInterface(const EstadoDesafioBau *estado);

#endif