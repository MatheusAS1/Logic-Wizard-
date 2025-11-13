#include "character.h"
#include "screen.h"
#include <string.h>

void characterInit(Character *c, int x, int y, const char *appearance)
{
    if (!c) return;
    c->x = x;
    c->y = y;
    c->appearance = appearance ? appearance : "@";
    c->dir_x = 0;
    c->dir_y = -1; 
}
 
void characterDestroy(Character *c)
{
    (void)c;
}

void characterDraw(const Character *c)
{
    if (!c) return;
    screenGotoxy(c->x, c->y);
    screenSetColor(CYAN, DARKGRAY);
    printf("%s", c->appearance);
}

void characterClear(const Character *c)
{
    if (!c) return;
    size_t len = strlen(c->appearance);
    screenGotoxy(c->x, c->y);
    for (size_t i = 0; i < len; ++i) putchar(' ');
}

void characterMove(Character *c, int dx, int dy)
{
    if (!c) return;
    int nx = c->x + dx;
    int ny = c->y + dy;

    if (nx < MINX + 1) nx = MINX + 1;
    if (nx+8 > MAXX - 1) nx = MAXX - 8; 
    if (ny < MINY + 1) ny = MINY + 1;
    if (ny > MAXY - 1) ny = MAXY - 1;

    c->x = nx;
    c->y = ny;
}

void characterSetPos(Character *c, int x, int y)
{
    if (!c) return;
    c->x = x;
    c->y = y;
}

void characterGetPos(const Character *c, int *x, int *y)
{
    if (!c) return;
    if (x) *x = c->x;
    if (y) *y = c->y;
}

void characterSetDir(Character *c, int dx, int dy)
{
    if (!c) return;
    c->dir_x = dx;
    c->dir_y = dy;
}

void characterGetDir(const Character *c, int *dx, int *dy)
{
    if (!c) return;
    if (dx) *dx = c->dir_x;
    if (dy) *dy = c->dir_y;
}
