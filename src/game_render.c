#include "game_render.h"

void renderizarJogo(Character *jogador, GerenciadorProjetil *gp, 
                    GerenciadorInimigo *gi, GerenciadorBau *gb,
                    Boss *boss, int boss_spawned, SistemaLogica *sl) {
    if (!jogador || !gp || !gi || !gb || !sl) return;
    
    characterDraw(jogador);
    gerenciadorProjetilDesenhar(gp);
    gerenciadorInimigoDesenhar(gi);
    gerenciadorBauDesenhar(gb);
    
    if (boss_spawned && boss && boss->ativo) {
        bossDesenhar(boss);
        if (boss->desafio_ativo) {
            bossDesenharEquivalencia(boss);
        }
    }

    logicaDesenharTabela(sl);
}