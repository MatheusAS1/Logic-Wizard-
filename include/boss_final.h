#ifndef __BOSS_FINAL_H__
#define __BOSS_FINAL_H__

#include "enemy.h"
#include "character.h" // Para saber onde o jogador está (se quiséssemos tiro teleguiado, mas faremos aleatório 4 dir)

// Inicializa o Boss com status de Final Boss
void bossFinalIniciar(Boss *boss, int x, int y, int vida, int velocidade, SistemaLogica *sl);

// Atualiza movimento e lógica de tiro
void bossFinalAtualizar(Boss *boss, int px, int py);

// Desenha o Boss com aparência "Malvada" e seus tiros
void bossFinalDesenhar(const Boss *boss);

// Limpa os rastros do Boss e dos tiros
void bossFinalLimpar(const Boss *boss);

// Verifica se os tiros acertaram o jogador
void bossFinalVerificarColisaoTiro(Boss *boss, Character *jogador);

#endif