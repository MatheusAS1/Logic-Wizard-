#include "projectile.h"
#include "screen.h"
#include <string.h>

void projectileManagerInit(ProjectileManager *pm)
{
    if (!pm) return;
    pm->count = 0;
    memset(pm->projectiles, 0, sizeof(pm->projectiles));
}

void projectileManagerDestroy(ProjectileManager *pm)
{
    (void)pm;
}

void projectileCreate(ProjectileManager *pm, int x, int y, int dx, int dy)
{
    if (!pm || pm->count >= MAX_PROJECTILES) return;
    
    Projectile *p = &pm->projectiles[pm->count];
    p->x = x;
    p->y = y;
    p->dx = dx;
    p->dy = dy;
    p->active = 1;
    p->appearance = "*";
    p->frame_counter = 0;
    
    pm->count++;
}

void projectileManagerDraw(const ProjectileManager *pm)
{
    if (!pm) return;
    
    for (int i = 0; i < pm->count; ++i) {
        const Projectile *p = &pm->projectiles[i];
        if (p->active) {
            screenGotoxy(p->x, p->y);
            screenSetColor(WHITE, DARKGRAY);
            printf("%s", p->appearance);
        }
    }
}

void projectileManagerClear(const ProjectileManager *pm)
{
    if (!pm) return;
    
    for (int i = 0; i < pm->count; ++i) {
        const Projectile *p = &pm->projectiles[i];
        if (p->active) {
            screenGotoxy(p->x, p->y);
            printf(" ");
        }
    }
}

void projectileManagerUpdate(ProjectileManager *pm)
{
    if (!pm) return;
    
    for (int i = 0; i < pm->count; ++i) {
        Projectile *p = &pm->projectiles[i];
        if (!p->active) continue;
        
        p->frame_counter++;
        
        if (p->frame_counter >= PROJECTILE_SPEED) {
            p->x += p->dx;
            p->y += p->dy;
            p->frame_counter = 0;
        }
        
        /* deactivate if out of bounds (with some margin for edge safety) */
        if (p->x < MINX + 1 || p->x > MAXX - 3 || p->y < MINY + 1 || p->y > MAXY - 1) {
            p->active = 0;
        }
    }
}

void projectileManagerCompact(ProjectileManager *pm)
{
    if (!pm) return;
    
    int j = 0;
    for (int i = 0; i < pm->count; ++i) {
        if (pm->projectiles[i].active) {
            if (i != j) {
                pm->projectiles[j] = pm->projectiles[i];
            }
            j++;
        }
    }
    pm->count = j;
}
