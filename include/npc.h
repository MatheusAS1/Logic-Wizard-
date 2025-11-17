#ifndef __NPC_H__
#define __NPC_H__

#include <stdio.h>

typedef struct {
    int x;
    int y;
    const char *nome;
    int foi_lido;
} NPC;

void npcIniciar(NPC *npc, int x, int y, const char *nome);
void npcDestruir(NPC *npc);

void npcDesenhar(const NPC *npc, int tipo);
void npcLimpar(const NPC *npc);

int npcEstaProximo(const NPC *npc, int jogador_x, int jogador_y, int distancia_maxima);

void npcMostrarDialogoDiego(int x, int y);
void npcMostrarDialogoGuilherme(int x, int y);
void npcLimparDialogo(int x, int y, int largura, int linhas);

void exibirTelaIntroducao();

#endif /* __NPC_H__ */
