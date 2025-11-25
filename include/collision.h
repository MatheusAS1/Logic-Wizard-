#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "character.h"
#include "enemy.h"
#include "projectile.h"
#include "item.h"

void processarColisaoJogadorInimigos(Character *jogador, GerenciadorInimigo *gi, int px, int py);

void processarColisaoJogadorBoss(Character *jogador, Boss *boss, int px, int py, int em_desafio);

void processarColisaoProjeteis(GerenciadorProjetil *gp, GerenciadorInimigo *gi, Boss *boss, GerenciadorBau *gb, int *score, 
                               int boss_spawned, int em_desafio);

#endif /* __COLLISION_H__ */