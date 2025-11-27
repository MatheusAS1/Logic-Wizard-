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
    int new_enemy_count = (int)(base_enemy_count * (*level-1) * 0.5) + 1;

    gerenciadorInimigoDestruir(gi);
    gerenciadorInimigoIniciar(gi, new_enemy_count);
    gerenciadorProjetilIniciar(gp);

    for (int k = 0; k < new_enemy_count; ++k) {
        int x, y;
        int tentativas = 0;
        int posicao_valida = 0;
        int distancia_minima = 10;

        do {
            x = (rand() % (MAXX - MINX - 6)) + MINX + 2;
            y = (rand() % (MAXY - MINY - 2)) + MINY + 1;

            int dx = abs(x - jogador->x);
            int dy = abs(y - jogador->y);
            
            if ((dx * dx) + (dy * dy) >= (distancia_minima * distancia_minima)) {
                posicao_valida = 1;
            }

            tentativas++;
        } while (!posicao_valida && tentativas < 50);

        int delay_inimigo = velocidade_inicial - ((*level) / 4);
        if (delay_inimigo < 6) delay_inimigo = 6; 

        inimigoSpawn(gi, x, y, base_enemy_life * (*level), delay_inimigo);
    }

    *boss_spawned = 0;
    *boss_timer = 0;
    boss->ativo = 0;
    *em_desafio = 0;
}