#include "creditos.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <stdio.h>
#include <string.h>

void exibirCreditos() {
    screenClear();
    screenInit(1);
    keyboardInit();
    
    int x = MAXX / 2 - 10;
    int y = MAXY / 2 - 2;
    
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x-5, y);     printf("=== CRÉDITOS ===");
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(x - 5, y + 2); printf("Desenvolvido por:");
    screenGotoxy(x - 5, y + 3); printf("Allysson Fellype");
    screenGotoxy(x - 5, y + 4); printf("Fernando Marinho");
    screenGotoxy(x - 5, y + 5); printf("Lucas Chaves");
    screenGotoxy(x - 5, y + 6); printf("Matheus Andrade");
    
    screenGotoxy(x - 5, y + 8); printf("Los Macacos Studio - 2025"); 
    
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(x - 5, y + 10); printf("[Pressione ENTER para voltar]");
    screenUpdate();
    
    int tecla = 0;
    while (tecla != 10 && tecla != 13) {
        if (keyhit()) tecla = readch();
    }
}