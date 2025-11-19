#include "ui.h"
#include "screen.h"
#include <unistd.h>

void uiLimparAreaDesafio() {
    for (int i = 0; i < 12; i++) {
        screenGotoxy(MAXX / 2 - 25, MAXY / 2 - 6 + i);
        printf("                                                              ");
    }
}

void uiLimparAreaInput() {
    screenGotoxy(MINX + 2, MAXY - 3);
    printf("                                                         ");
    screenGotoxy(MINX + 2, MAXY - 2);
    printf("                                                         ");
}

void uiDesenharHUDSuperior(int score, int level, int vidas, int inimigos, 
                           int boss_vida, int baus, int fps) {
    screenGotoxy(3, 1);
    screenSetColor(GREEN, DARKGRAY);
    printf("Score: %d | Level: %d | Vidas: %d | Inimigos: %d | Boss: %d | Baus: %d | FPS: %d", 
           score, level, vidas, inimigos, boss_vida, baus, fps);
}

void uiDesenharHUDInferior(int px, int py) {
    screenGotoxy(3, MAXY + 1);
    screenSetColor(YELLOW, DARKGRAY);
    printf("Pos: (%d,%d) | WASD=Mover | V=Atirar | F=Especial | ESC=Sair", px, py);
}

void uiMostrarFeedback(const char *mensagem, int cor, int tempo_ms, int x, int y) {
    screenGotoxy(x, y);
    screenSetColor(cor, DARKGRAY);
    screenSetBold();
    printf("%s", mensagem);
    screenSetNormal();
    screenUpdate();
    usleep(tempo_ms * 1000);

    screenGotoxy(x, y);
    for (int i = 0; mensagem[i]; i++) {
        printf(" ");
    }
}