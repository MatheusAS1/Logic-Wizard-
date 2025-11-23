#include "game_progression.h"
#include "screen.h"
#include "item.h"
#include <stdlib.h>

void avancarProximoLevel(int *level, GerenciadorInimigo *gi, GerenciadorProjetil *gp,
                         Character *jogador, SistemaLogica *sl, Boss *boss, 
                         GerenciadorBau *gb, int *boss_spawned, int *boss_timer, int *em_desafio,
                         int base_enemy_count, int base_enemy_life, int velocidade_inicial) {
    if (!level || !gi || !gp || !jogador || !sl || !boss || !gb) return;
    
    gb->quantidade = 0;

    (*level)++;
    int new_enemy_count = base_enemy_count * (*level);

    gerenciadorInimigoDestruir(gi);
    gerenciadorInimigoIniciar(gi, new_enemy_count);
    gerenciadorProjetilIniciar(gp);

    jogador->lives = 3;

    for (int k = 0; k < new_enemy_count; ++k) {
        int x = (rand() % (MAXX - MINX - 6)) + MINX + 2;
        int y = (rand() % (MAXY - MINY - 2)) + MINY + 1;
        int delay_inimigo = velocidade_inicial - ((*level) / 4);

        if (delay_inimigo < 5) delay_inimigo = 5;

        inimigoSpawn(gi, x, y, base_enemy_life * (*level), delay_inimigo);
    }

    *boss_spawned = 0;
    *boss_timer = 0;
    boss->ativo = 0;
    *em_desafio = 0;
}