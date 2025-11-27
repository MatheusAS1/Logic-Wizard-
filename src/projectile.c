#include "projectile.h"
#include "screen.h"
#include "audio.h"
#include <string.h>

static int soundShootId = -1;

void gerenciadorProjetilIniciar(GerenciadorProjetil *gp)
{
    if (!gp) return;
    gp->quantidade_simples = 0;
    gp->quantidade_especial = 0;
    memset(gp->projeteis, 0, sizeof(gp->projeteis));
    
    soundShootId = audioLoadSound("assets/sounds/shoot.wav");
}

void gerenciadorProjetilDestruir(GerenciadorProjetil *gp)
{
    (void)gp;
}

void projetilCriar(GerenciadorProjetil *gp, int x, int y, int dx, int dy)
{
    if (!gp || gp->quantidade_simples >= MAX_PROJETIL_SIMPLES) return;

    int idx = gp->quantidade_simples;
    Projetil *p = &gp->projeteis[idx];
    p->x = x;
    p->y = y;
    p->dx = dx;
    p->dy = dy;
    p->ativo = 1;
    p->aparencia = "*";
    p->contador_frames = 0;
    p->velocidade = VELOCIDADE_PROJETIL; 
    p->dano = 1;

    gp->quantidade_simples++;
    
    if (soundShootId >= 0) {
        audioPlaySound(soundShootId, 30);
    }
}

void projetilCriarEspecial(GerenciadorProjetil *gp, int x, int y, int dx, int dy)
{
    if (!gp || gp->quantidade_especial >= MAX_PROJETIL_ESPECIAL) return;

    int idx = MAX_PROJETIL_SIMPLES + gp->quantidade_especial;
    Projetil *p = &gp->projeteis[idx];
    p->x = x;
    p->y = y;
    p->dx = dx;
    p->dy = dy;
    p->ativo = 1;
    p->aparencia = "@";
    p->contador_frames = 0;
    
    int vel = VELOCIDADE_PROJETIL + 1;
    if (vel < 1) vel = 1; 
    p->velocidade = vel;
    
    if (soundShootId >= 0) {
        audioPlaySound(soundShootId, 35);
    } 
    p->dano = 4;

    gp->quantidade_especial++;
}

void gerenciadorProjetilDesenhar(const GerenciadorProjetil *gp)
{
    if (!gp) return;

    for (int i = 0; i < gp->quantidade_simples; ++i) {
        const Projetil *p = &gp->projeteis[i];
        if (p->ativo) {
            screenGotoxy(p->x, p->y);
            screenSetColor(WHITE, DARKGRAY);
            printf("%s", p->aparencia);
        }
    }
    for (int i = 0; i < gp->quantidade_especial; ++i) {
        const Projetil *p = &gp->projeteis[MAX_PROJETIL_SIMPLES + i];
        if (p->ativo) {
            screenGotoxy(p->x, p->y);
            screenSetColor(YELLOW, DARKGRAY); 
            printf("%s", p->aparencia);
        }
    }
}

void gerenciadorProjetilLimpar(const GerenciadorProjetil *gp)
{
    if (!gp) return;

    for (int i = 0; i < gp->quantidade_simples; ++i) {
        const Projetil *p = &gp->projeteis[i];
        if (p->ativo) {
            screenGotoxy(p->x, p->y);
            printf(" ");
        }
    }
    for (int i = 0; i < gp->quantidade_especial; ++i) {
        const Projetil *p = &gp->projeteis[MAX_PROJETIL_SIMPLES + i];
        if (p->ativo) {
            screenGotoxy(p->x, p->y);
            printf(" ");
        }
    }
}

void gerenciadorProjetilAtualizar(GerenciadorProjetil *gp)
{
    if (!gp) return;

    for (int i = 0; i < gp->quantidade_simples; ++i) {
        Projetil *p = &gp->projeteis[i];
        if (!p->ativo) continue;
        p->contador_frames++;
        if (p->contador_frames >= p->velocidade) {
            p->x += p->dx;
            p->y += p->dy;
            p->contador_frames = 0;
            
            if (p->x < MINX + 1 || p->x > MAXX - 3 || p->y < MINY + 1 || p->y > MAXY - 1) {
                p->ativo = 0;
            }
        }
    }

    for (int i = 0; i < gp->quantidade_especial; ++i) {
        Projetil *p = &gp->projeteis[MAX_PROJETIL_SIMPLES + i];
        if (!p->ativo) continue;

        p->contador_frames++;
        if (p->contador_frames >= p->velocidade) {
            p->x += p->dx;
            p->y += p->dy;
            p->contador_frames = 0; 
            if (p->x < MINX + 1 || p->x > MAXX - 3 || p->y < MINY + 1 || p->y > MAXY - 1) {
                p->ativo = 0;
            }
        }
    }
}

void gerenciadorProjetilCompactar(GerenciadorProjetil *gp)
{
    if (!gp) return;

    int j = 0;
    for (int i = 0; i < gp->quantidade_simples; ++i) {
        if (gp->projeteis[i].ativo) { 
            if (i != j) {
                gp->projeteis[j] = gp->projeteis[i];
            }
            j++;
        }
    }
    gp->quantidade_simples = j;

    j = 0;
    for (int i = 0; i < gp->quantidade_especial; ++i) {
        int idx = MAX_PROJETIL_SIMPLES + i;
        if (gp->projeteis[idx].ativo) { 
            if (idx != MAX_PROJETIL_SIMPLES + j) {
                gp->projeteis[MAX_PROJETIL_SIMPLES + j] = gp->projeteis[idx];
            }
            j++;
        }
    }
    gp->quantidade_especial = j;
}