#include "collision.h"
#include <stdlib.h>

void processarColisaoJogadorInimigos(Character *jogador, GerenciadorInimigo *gi, int px, int py) {
    if (!jogador || !gi) return;
    for (int i = 0; i < gi->quantidade; ++i) {
        Inimigo *ini = &gi->inimigos[i];
        if (!ini->ativo) continue; 
        
        if (px < ini->x + 5 && px + 8 > ini->x && py == ini->y) {
            jogador->lives--;
            ini->ativo = 0; 
        }
    }
}

void processarColisaoJogadorBoss(Character *jogador, Boss *boss, int px, int py, int em_desafio) {
    if (!jogador || !boss || !boss->ativo || em_desafio) return;
    
    if (px < boss->x + 8 && px + 8 > boss->x && py == boss->y) {
        jogador->lives--;
    }
}

void processarColisaoProjeteis(GerenciadorProjetil *gp, GerenciadorInimigo *gi, 
                               Boss *boss, GerenciadorBau *gb, int *score, 
                               int boss_spawned, int em_desafio) {
    if (!gp || !gi || !gb || !score) return;

    for (int i = 0; i < gp->quantidade_simples; ++i) {
        Projetil *p = &gp->projeteis[i];
        if (!p->ativo) continue; 

        int acertou_inimigo = 0;
        for (int j = 0; j < gi->quantidade; ++j) {
            Inimigo *ini = &gi->inimigos[j];
            if (!ini->ativo) continue;

            if (p->y == ini->y && p->x >= ini->x && p->x < ini->x + 5) {
                ini->vida -= p->dano;
                p->ativo = 0; 
                acertou_inimigo = 1;

                if (ini->vida <= 0) {
                    if (rand() % 100 < 30) { 
                        bauSpawn(gb, ini->x, ini->y, "~p");
                    }
                    ini->ativo = 0;
                    (*score)++;
                }
                break; 
            }
        }

        if (acertou_inimigo || !p->ativo) continue;

        if (boss_spawned && boss && boss->ativo && !em_desafio) {
            if (p->y == boss->y && p->x >= boss->x && p->x < boss->x + 8) {
                boss->vida -= p->dano;
                p->ativo = 0; 
                if (boss->vida <= 0) {
                    boss->ativo = 0;
                    *score += 10;
                }
            }
        }
    }

    for (int i = 0; i < gp->quantidade_especial; ++i) {
        Projetil *p = &gp->projeteis[MAX_PROJETIL_SIMPLES + i];
        if (!p->ativo) continue;

        int acertou_inimigo = 0;
        for (int j = 0; j < gi->quantidade; ++j) {
            Inimigo *ini = &gi->inimigos[j];
            if (!ini->ativo) continue;

            if (p->y == ini->y && p->x >= ini->x && p->x < ini->x + 5) {
                ini->vida -= p->dano;
                p->ativo = 0;
                acertou_inimigo = 1;
                
                if (ini->vida <= 0) {
                    if (rand() % 100 < 30) {
                        bauSpawn(gb, ini->x, ini->y, "~p");
                    }
                    ini->ativo = 0;
                    (*score)++;
                }
                break; 
            }
        }

        if (acertou_inimigo || !p->ativo) continue;

        if (boss_spawned && boss && boss->ativo && !em_desafio) {
            if (p->y == boss->y && p->x >= boss->x && p->x < boss->x + 8) {
                boss->vida -= p->dano;
                p->ativo = 0;
                if (boss->vida <= 0) {
                    boss->ativo = 0;
                    *score += 10;
                }
            }
        }
    }
}