#ifndef __GAME_PROGRESSION_H__
#define __GAME_PROGRESSION_H__

#include "character.h"
#include "enemy.h"
#include "projectile.h"
#include "logic.h"

void avancarProximoLevel(int *level, GerenciadorInimigo *gi, GerenciadorProjetil *gp, Character *jogador, SistemaLogica *sl, Boss *boss, 
                         int *boss_spawned, int *boss_timer, int *em_desafio, int base_enemy_count, int base_enemy_life, int velocidade_inicial);

#endif /* __GAME_PROGRESSION_H__ */