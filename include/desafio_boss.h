#ifndef __DESAFIO_BOSS_H__
#define __DESAFIO_BOSS_H__

#include "enemy.h"
#include "character.h"
#include "logic.h"

typedef struct {
    char resposta[64];
    int idx_resposta;
    int ativo;
} EstadoDesafioBoss;

void desafioBossIniciar(EstadoDesafioBoss *estado);
void desafioBossAtivar(EstadoDesafioBoss *estado);
void desafioBossDesativar(EstadoDesafioBoss *estado);
int desafioBossEstaAtivo(const EstadoDesafioBoss *estado);

int desafioBossProcessarInput(EstadoDesafioBoss *estado, Boss *boss, Character *jogador, int *score);

void desafioBossDesenharInterface(const EstadoDesafioBoss *estado);

#endif /* __DESAFIO_BOSS_H__ */