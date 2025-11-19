

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <stdio.h>

typedef struct {
    int x;
    int y;
    const char *appearance;
    int dir_x; 
    int dir_y;
    int lives;
} Character;

void characterInit(Character *c, int x, int y, const char *appearance);

void characterDestroy(Character *c);

void characterDraw(const Character *c);
void characterClear(const Character *c);

void characterMove(Character *c, int dx, int dy);

void characterSetPos(Character *c, int x, int y);
void characterGetPos(const Character *c, int *x, int *y);

void characterSetDir(Character *c, int dx, int dy);
void characterGetDir(const Character *c, int *dx, int *dy);

#endif /* __CHARACTER_H__ */
