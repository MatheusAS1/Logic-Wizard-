#include <stdio.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "character.h"
#include "projectile.h"

int main()
{
    Character player;
    ProjectileManager pm;
    int ch = 0;
    
    int frame_count = 0;
    int current_fps = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);
    projectileManagerInit(&pm);

    characterInit(&player, 40, 12, "(-_-)/*");
    characterDraw(&player);
    screenUpdate();

    while (ch != 27)
    {
        if (keyhit())
        {
            ch = readch();

            characterClear(&player);
            projectileManagerClear(&pm);

            if (ch == 'w') {
                characterMove(&player, 0, -1);
                characterSetDir(&player, 0, -1);
            } else if (ch == 's') {
                characterMove(&player, 0, 1);
                characterSetDir(&player, 0, 1);
            } else if (ch == 'a') {
                characterMove(&player, -1, 0);
                characterSetDir(&player, -1, 0);
            } else if (ch == 'd') {
                characterMove(&player, 1, 0);
                characterSetDir(&player, 1, 0);
            }

            if (ch == 'v') {
                int px, py, dir_x, dir_y;
                characterGetPos(&player, &px, &py);
                characterGetDir(&player, &dir_x, &dir_y);
                
                int spawn_x = px + (dir_x * 7);  
                int spawn_y = py + (dir_y * 2);  
                
                projectileCreate(&pm, spawn_x, spawn_y, dir_x, dir_y);
            }

            characterDraw(&player);
            projectileManagerDraw(&pm);

            int px, py;
            characterGetPos(&player, &px, &py);
            screenGotoxy(5, MAXY + 1);
            screenSetColor(YELLOW, DARKGRAY);
            printf("Pos: (%d,%d)  Tecla: %d  ", px, py, ch);

            screenUpdate();
        }

        projectileManagerClear(&pm);
        projectileManagerUpdate(&pm);
        projectileManagerDraw(&pm);
        projectileManagerCompact(&pm);
        
        frame_count++;
        if (frame_count >= 20) {  
            current_fps = frame_count;
            frame_count = 0;
        }
        
        screenGotoxy(70, 1);
        screenSetColor(GREEN, DARKGRAY);
        printf("FPS: %d  ", current_fps);
        
        screenUpdate();

        timerTimeOver();
    }

    characterDestroy(&player);
    projectileManagerDestroy(&pm);
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    return 0;
}
