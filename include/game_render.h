#ifndef __GAME_RENDER_H__
#define __GAME_RENDER_H__

#include "character.h"
#include "projectile.h"
#include "enemy.h"
#include "item.h"
#include "logic.h"
#include "boss_final.h"

void renderizarJogo(Character *jogador, GerenciadorProjetil *gp, GerenciadorInimigo *gi, GerenciadorBau *gb,
                    Boss *boss, int boss_spawned, SistemaLogica *sl,int level);

#endif /* __GAME_RENDER_H__ */