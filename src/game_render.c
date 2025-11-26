#include "game_render.h"

void renderizarJogo(Character *jogador, GerenciadorProjetil *gp, 
                    GerenciadorInimigo *gi, GerenciadorBau *gb,
                    Boss *boss, int boss_spawned, SistemaLogica *sl,int level) {
    if (!jogador || !gp || !gi || !gb || !sl) return;
    
    characterDraw(jogador);
    gerenciadorProjetilDesenhar(gp);
    gerenciadorInimigoDesenhar(gi);
    gerenciadorBauDesenhar(gb);
    if (boss_spawned && boss && boss->ativo) {
        if (boss->eh_final) {
            bossFinalDesenhar(boss); 
        } else {
            bossDesenhar(boss);      
        }
        if (boss->desafio_ativo) {
            bossDesenharEquivalencia(boss);
        }
    }
    if(level < 5){
        logicaDesenharTabela(sl);
    }
    else{
        logicaApagarTabela(sl);
    }
}