#include "menu.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "audio.h"
#include <stdio.h>
#include <string.h>

#define OP_JOGAR 1
#define OP_TUTORIAL 2
#define OP_CREDITOS 3
#define OP_SAIR 4

void desenharTitulo(int x, int y) {
    screenSetColor(MAGENTA, DARKGRAY);
    screenGotoxy(x, y);     printf(" _               _        __      ___                  _ ");
    screenGotoxy(x, y + 1); printf("| |    ___   __ _(_) ___  \\ \\    / (_)______ _ _ __ __| |");
    screenGotoxy(x, y + 2); printf("| |   / _ \\ / _` | |/ __|  \\ \\/\\/ /| |_  / _` | '__/ _` |");
    screenGotoxy(x, y + 3); printf("| |__| (_) | (_| | | (__    \\    / | |/ / (_| | | | (_| |");
    screenGotoxy(x, y + 4); printf("|_____\\___/ \\__, |_|\\___|    \\/\\/  |_/___\\__,_|_|  \\__,_|");
    screenGotoxy(x, y + 5); printf("            |___/                                        ");
}

void desenharOpcao(int x, int y, const char* texto, int selecionado) {
    screenGotoxy(x, y);
    
    if (selecionado) {
        screenSetColor(YELLOW, DARKGRAY);
        screenSetBold();
        printf("  %s  <-", texto);
        screenSetNormal();
    } else {
        screenSetColor(WHITE, DARKGRAY);
        printf("  %s    ", texto); 
    }
}

int exibirMenuPrincipal() {
    screenInit(1);
    keyboardInit();
    timerInit(100); 

    int opcaoSelecionada = 1;
    int tecla = 0;
    int rodando = 1;

    int centroX = MAXX / 2;
    int tituloX = centroX - 30; 
    int tituloY = 4;
    
    int menuX = centroX - 5; 
    int menuY = 12;

    screenClear();

    desenharTitulo(tituloX, tituloY);

    while (rodando) {
        if (timerTimeOver()) {
            
            tecla = 0;
            if (keyhit()) {
                tecla = readch();
            }

            if (tecla == 'w' || tecla == 'W') {
                opcaoSelecionada--;
                if (opcaoSelecionada < 1) opcaoSelecionada = 4;
            } 
            else if (tecla == 's' || tecla == 'S') {
                opcaoSelecionada++;
                if (opcaoSelecionada > 4) opcaoSelecionada = 1;
            }
            else if (tecla == 10 || tecla == 13) { 
                rodando = 0; 
            }

            desenharOpcao(menuX, menuY,     "MODO HISTÓRIA", (opcaoSelecionada == OP_JOGAR));
            desenharOpcao(menuX, menuY + 2, "TUTORIAL ", (opcaoSelecionada == OP_TUTORIAL));
            desenharOpcao(menuX, menuY + 4, "CREDITOS ", (opcaoSelecionada == OP_CREDITOS));
            desenharOpcao(menuX, menuY + 6, "SAIR     ", (opcaoSelecionada == OP_SAIR));

            screenGotoxy(centroX - 15, MAXY - 2);
            screenSetColor(LIGHTGRAY, DARKGRAY);
            printf("[W/S] Navegar  [ENTER] Selecionar");

            screenUpdate();
        }
    }

    screenClear();


    return opcaoSelecionada;
}