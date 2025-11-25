#ifndef __DESAFIO_BAU_H__
#define __DESAFIO_BAU_H__

#include "item.h"
#include "character.h"


typedef struct {
    char resposta_linha1[8];
    char resposta_linha2[8];
    int idx_resposta_linha;
    int linha_atual;        
    int tentativas;        
    int bau_index;         
    int ativo;              
} EstadoDesafioBau;

void desafioBauIniciar(EstadoDesafioBau *estado);

int desafioBauProcessarInput(EstadoDesafioBau *estado, GerenciadorBau *gb, Character *jogador, int *score);

void desafioBauDesenharInterface(const EstadoDesafioBau *estado);

void desafioBauAtivar(EstadoDesafioBau *estado, int bau_index);

void desafioBauDesativar(EstadoDesafioBau *estado);

int desafioBauEstaAtivo(const EstadoDesafioBau *estado);

#endif /* __DESAFIO_BAU_H__ */