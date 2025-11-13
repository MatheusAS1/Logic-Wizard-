#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include <stdio.h>

typedef struct {
    int x;
    int y;
    int dx;       
    int dy;        
    int active;    
    const char *appearance; 
    int frame_counter; 
} Projectile;


#define MAX_PROJECTILES 5


#define PROJECTILE_SPEED 500

typedef struct {
    Projectile projectiles[MAX_PROJECTILES];
    int count; 
} ProjectileManager;


void projectileManagerInit(ProjectileManager *pm);
void projectileManagerDestroy(ProjectileManager *pm);

void projectileCreate(ProjectileManager *pm, int x, int y, int dx, int dy);
void projectileManagerDraw(const ProjectileManager *pm);

void projectileManagerClear(const ProjectileManager *pm);
void projectileManagerUpdate(ProjectileManager *pm);

void projectileManagerCompact(ProjectileManager *pm);

#endif
