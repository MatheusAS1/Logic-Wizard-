#include "npc.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "character.h"
#include <stdlib.h>
#include <unistd.h>

void npcIniciar(NPC *npc, int x, int y, const char *nome) {
    if (!npc) return;
    npc->x = x;
    npc->y = y;
    npc->nome = nome;
    npc->foi_lido = 0;
}

void npcDestruir(NPC *npc) {
    (void)npc;
}

void npcDesenhar(const NPC *npc, int tipo) {
    if (!npc) return;
    
    if (tipo == 0) {
        screenSetColor(MAGENTA, DARKGRAY);
        screenGotoxy(npc->x, npc->y);
        printf("    _*_    ");
        screenGotoxy(npc->x, npc->y + 1);
        printf("   {o.o}   ");
        screenGotoxy(npc->x, npc->y + 2);
        printf("   /|X|\\   ");
        screenGotoxy(npc->x, npc->y + 3);
        printf("    / \\    ");
        screenGotoxy(npc->x - 2, npc->y + 4);
        screenSetColor(LIGHTMAGENTA, DARKGRAY);
        printf("%s", npc->nome);
    } else {
        screenSetColor(CYAN, DARKGRAY);
        screenGotoxy(npc->x, npc->y);
        printf("    _^_    ");
        screenGotoxy(npc->x, npc->y + 1);
        printf("   (^.^)   ");
        screenGotoxy(npc->x, npc->y + 2);
        printf("   <|#|>   ");
        screenGotoxy(npc->x, npc->y + 3);
        printf("    / \\    ");
        screenGotoxy(npc->x - 5, npc->y + 4);
        screenSetColor(LIGHTCYAN, DARKGRAY);
        printf("%s", npc->nome);
    }
}

void npcLimpar(const NPC *npc) {
    if (!npc) return;
    for (int i = 0; i < 5; i++) {
        screenGotoxy(npc->x - 5, npc->y + i);
        printf("                    ");
    }
}

int npcEstaProximo(const NPC *npc, int jogador_x, int jogador_y, int distancia_maxima) {
    if (!npc) return 0;
    int dist = abs(jogador_x - npc->x) + abs(jogador_y - npc->y);
    return dist <= distancia_maxima;
}

void npcMostrarDialogoDiego(int x, int y) {
    screenSetColor(LIGHTMAGENTA, DARKGRAY);
    screenGotoxy(x, y);
    printf("┌────────────────────────────────────────────────────────────┐");
    screenGotoxy(x, y + 1);
    printf("│ Diego: Saude, jovem aprendiz!                              │");
    screenGotoxy(x, y + 2);
    printf("│        Use W, A, S, D para se mover pelo campo.            │");
    screenGotoxy(x, y + 3);
    printf("│        Pressione V para lancar um feitico basico!          │");
    screenGotoxy(x, y + 4);
    printf("└────────────────────────────────────────────────────────────┘");
    screenGotoxy(x, y + 5);
    screenSetColor(YELLOW, DARKGRAY);
    printf("                      [Pressione ENTER]");
}

void npcMostrarDialogoGuilherme(int x, int y) {
    screenSetColor(LIGHTCYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf("┌────────────────────────────────────────────────────────────┐");
    screenGotoxy(x, y + 1);
    printf("│ Guilherme: E nao se esqueca!                               │");
    screenGotoxy(x, y + 2);
    printf("│            Pressione F para ataque especial em 4 dir.!     │");
    screenGotoxy(x, y + 3);
    printf("│            Derrote todos os inimigos e enfrente o Boss!    │");
    screenGotoxy(x, y + 4);
    printf("└────────────────────────────────────────────────────────────┘");
    screenGotoxy(x, y + 5);
    screenSetColor(YELLOW, DARKGRAY);
    printf("                      [Pressione ENTER]");
}

void npcLimparDialogo(int x, int y, int largura, int linhas) {
    for (int i = 0; i < linhas; i++) {
        screenGotoxy(x, y + i);
        for (int j = 0; j < largura; j++) {
            printf(" ");
        }
    }
}

void exibirTelaIntroducao() {
    screenClear();
    screenInit(1);
    keyboardInit();
    timerInit(100);
    
    NPC diego, guilherme;
    Character jogador;
    
    npcIniciar(&diego, 15, 12, "  Mago Diego");
    npcIniciar(&guilherme, 70, 12, "Mago Guilherme");
    characterInit(&jogador, 45, 22, "(-_-)/*");
    
    int mostrar_dialogo_diego = 0;
    int mostrar_dialogo_guilherme = 0;
    int tecla = 0;
    
    int titulo_x = (MAXX / 2) - 16;
    screenGotoxy(titulo_x, 5);
    screenSetColor(YELLOW, DARKGRAY);
    screenSetBold();
    printf("=== BEM-VINDO AO LOGIC WIZARD ===");
    screenSetNormal();
    
    int instrucao_x = (MAXX / 2) - 25;
    screenGotoxy(instrucao_x, 7);
    screenSetColor(WHITE, DARKGRAY);
    printf("Aproxime-se dos magos para receber instrucoes!");
    
    while (!diego.foi_lido || !guilherme.foi_lido) {
        if (timerTimeOver()) {
            characterClear(&jogador);
            
            tecla = 0;
            while (keyhit()) {
                tecla = readch();
            }
            
            if (tecla == 'w' || tecla == 'W') {
                characterMove(&jogador, 0, -1);
            } else if (tecla == 's' || tecla == 'S') {
                characterMove(&jogador, 0, 1);
            } else if (tecla == 'a' || tecla == 'A') {
                characterMove(&jogador, -1, 0);
            } else if (tecla == 'd' || tecla == 'D') {
                characterMove(&jogador, 1, 0);
            }
            
            int px, py;
            characterGetPos(&jogador, &px, &py);
            
            if (npcEstaProximo(&diego, px, py, 15) && !diego.foi_lido) {
                if (!mostrar_dialogo_diego) {
                    mostrar_dialogo_diego = 1;
                    npcMostrarDialogoDiego(3, 19);
                }
                
                if (tecla == 10 || tecla == 13) {
                    diego.foi_lido = 1;
                    npcLimparDialogo(3, 19, 65, 6);
                    mostrar_dialogo_diego = 0;
                }
            } else if (!npcEstaProximo(&diego, px, py, 15) && mostrar_dialogo_diego && !diego.foi_lido) {
                npcLimparDialogo(3, 19, 65, 6);
                mostrar_dialogo_diego = 0;
            }
            
            if (npcEstaProximo(&guilherme, px, py, 15) && !guilherme.foi_lido) {
                if (!mostrar_dialogo_guilherme) {
                    mostrar_dialogo_guilherme = 1;
                    npcMostrarDialogoGuilherme(32, 19);
                }
                
                if (tecla == 10 || tecla == 13) {
                    guilherme.foi_lido = 1;
                    npcLimparDialogo(32, 19, 65, 6);
                    mostrar_dialogo_guilherme = 0;
                }
            } else if (!npcEstaProximo(&guilherme, px, py, 15) && mostrar_dialogo_guilherme && !guilherme.foi_lido) {
                npcLimparDialogo(32, 19, 65, 6);
                mostrar_dialogo_guilherme = 0;
            }
            
            npcDesenhar(&diego, 0);
            npcDesenhar(&guilherme, 1);
            characterDraw(&jogador);
            
            int status_x = (MAXX / 2) - 15;
            screenGotoxy(status_x, 27);
            screenSetColor(WHITE, DARKGRAY);
            printf("Diego: %s | Guilherme: %s", 
                   diego.foi_lido ? "OK" : "--", 
                   guilherme.foi_lido ? "OK" : "--");
            
            screenUpdate();
        }
    }
    
    screenClear();
    screenInit(1);
    int msg_x = (MAXX / 2) - 10;
    screenGotoxy(msg_x, 15);
    screenSetColor(YELLOW, DARKGRAY);
    screenSetBold();
    printf("Preparando a batalha");
    screenSetNormal();
    
    for (int i = 0; i < 3; i++) {
        printf(".");
        screenUpdate();
        sleep(1);
    }
    
    screenUpdate();
    sleep(1);
    
    npcDestruir(&diego);
    npcDestruir(&guilherme);
    characterDestroy(&jogador);
    keyboardDestroy();
    timerDestroy();
}
