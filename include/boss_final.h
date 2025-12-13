#ifndef __BOSS_FINAL_H__
#define __BOSS_FINAL_H__

#include "enemy.h"
#include "character.h" 

void bossFinalIniciar(Boss *boss, int x, int y, int vida, int velocidade, SistemaLogica *sl);

void bossFinalAtualizar(Boss *boss, int px, int py,int modo);

void bossFinalDesenhar(const Boss *boss);

void bossFinalLimpar(const Boss *boss);

void bossFinalVerificarColisaoTiro(Boss *boss, Character *jogador);

#endif