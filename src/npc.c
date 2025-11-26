#include "npc.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "character.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

void npcMostrarDialogoGuilhermeFinal(int x, int y) {
    screenSetColor(LIGHTCYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf("┌────────────────────────────────────────────────────────────┐");
    screenGotoxy(x, y + 1);
    printf("│ Guilherme: jovem mestre!                                   │");
    screenGotoxy(x, y + 2);
    printf("│            Sempre soube que conseguiria, Parabéns!         │");
    screenGotoxy(x, y + 3);
    printf("│        Receba minha benção e todo conhecimento de Lógica   │");
    screenGotoxy(x, y + 4);
    printf("└────────────────────────────────────────────────────────────┘");
    screenGotoxy(x, y + 5);
    screenSetColor(YELLOW, DARKGRAY);
    printf("                      [Pressione ENTER]");
}

void npcMostrarDialogoDiegoFinal(int x, int y) {
    screenSetColor(LIGHTMAGENTA, DARKGRAY);
    screenGotoxy(x, y);
    printf("┌────────────────────────────────────────────────────────────┐");
    screenGotoxy(x, y + 1);
    printf("│ Diego: Saude, jovem mestre!                                │");
    screenGotoxy(x, y + 2);
    printf("│        Você derrotou o núcleo corrompido!                  │");
    screenGotoxy(x, y + 3);
    printf("│        Receba minha benção e todo o conhecimento de PIF!   │");
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

void exibirNarrativaHistoria() {
    screenInit(1);
    keyboardInit();
    timerInit(100);
    
    const char *titulos[6] = {
        "O INICIO DA JORNADA",
        "A AMEACA DO SISTEMA CORROMPIDO",
        "O CAOS DIGITAL",
        "OS MESTRES LEGENDARIOS",
        "A PROFECIA",
        "SUA MISSAO"
    };
    
    const char *telas[6][10] = {
        {
            "Ha muito tempo, em uma galaxia nao tao",
            "distante...",
            NULL
        },
        {
            "A paz reinava no vasto Ciberverso, um reino digital onde linhas de",
            "codigo dancavam em perfeita harmonia e algoritmos mantinham o",
            "equilibrio de todas as aplicacoes.",
            "",
            "Contudo, das sombras binarias emergiu uma ameaca sombria:",
            "o Nucleo Corrompido, uma entidade criada a partir de falhas",
            "acumuladas, negligencia humana e bugs esquecidos.",
            NULL
        },
        {
            "A contaminacao espalhou-se como um virus ancestral. Programas antes",
            "pacificos tornaram-se instaveis, interfaces quebraram e modulos",
            "inteiros passaram a agir de forma imprevisivel. O caos digital",
            "estava instalado.",
            "",
            "Diante desse cenario, o Conselho dos Desenvolvedores convocou dois",
            "mestres legendarios:",
            NULL
        },
        {
            "Diego, o Mago do Codigo, capaz de manipular estruturas e linguagens",
            "com simples movimentos de suas maos, transformando caos em elegancia.",
            "",
            "Guilherme, o Mago da Logica, guardiao das regras, mestre dos fluxos",
            "e decisoes, cuja mente era considerada um dos mais poderosos",
            "processadores vivos.",
            "",
            "Mas mesmo com todo seu poder, os dois magos sabiam que nao poderiam",
            "enfrentar o Nucleo Corrompido sozinhos.",
            NULL
        },
        {
            "Por isso, recorreram a uma antiga profecia, que falava sobre a",
            "chegada de um(a) jovem aprendiz vindo do mundo real, dotado de",
            "coragem, curiosidade e um espirito capaz de aprender rapidamente.",
            "",
            "E assim voce foi convocado...",
            NULL
        },
        {
            "Transportado para dentro do Ciberverso, sua missao e clara: usar",
            "ferramentas sagradas do desenvolvimento, enfrentar criaturas feitas",
            "de erros fatais, restaurar trechos de codigo destruidos e eliminar",
            "os temidos bugs que ameacam devorar toda a galaxia digital.",
            "",
            "O destino do sistema — e talvez de todo o universo conectado —",
            "esta agora em suas maos.",
            "",
            "A batalha pela estabilidade acaba de comecar...",
            NULL
        }
    };
    
    int pular = 0;
    
    for (int tela = 0; tela < 6 && !pular; tela++) {
        screenClear();
        
        int titulo_x = (MAXX / 2) - (strlen(titulos[tela]) / 2);
        screenGotoxy(titulo_x, 5);
        screenSetColor(YELLOW, DARKGRAY);
        screenSetBold();
        printf("%s", titulos[tela]);
        screenSetNormal();
        
        screenGotoxy(titulo_x - 5, 6);
        screenSetColor(YELLOW, DARKGRAY);
        for (int i = 0; i < strlen(titulos[tela]) + 10; i++) {
            printf("=");
        }
        
        int linha_inicial = 9;
        int linha_atual = linha_inicial;
        
        for (int i = 0; telas[tela][i] != NULL; i++) {
            int x = (MAXX / 2) - (strlen(telas[tela][i]) / 2);
            screenGotoxy(x, linha_atual);
            
            if (strlen(telas[tela][i]) == 0) {
                screenSetColor(WHITE, DARKGRAY);
            } else if (tela == 0) {
                screenSetColor(CYAN, DARKGRAY);
            } else {
                screenSetColor(WHITE, DARKGRAY);
            }
            
            printf("%s", telas[tela][i]);
            screenSetNormal();
            linha_atual++;
        }
        
        screenGotoxy((MAXX / 2) - 25, MAXY - 3);
        screenSetColor(YELLOW, DARKGRAY);
        printf("[ENTER: Continuar | ESPACO: Pular historia]");
        
        screenUpdate();
        
        while (1) {
            if (keyhit()) {
                int tecla = readch();
                if (tecla == 10 || tecla == 13) {
                    break;
                } else if (tecla == ' ' || tecla == 32) {
                    pular = 1;
                    break;
                }
            }
        }
    }
    
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
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

void exibirTelaFinal() {
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
    
    int titulo_x = (MAXX / 2) - 22;
    screenGotoxy(titulo_x, 5);
    screenSetColor(YELLOW, DARKGRAY);
    screenSetBold();
    printf("=== OBRIGADO POR JOGAR LOGIC WIZARD! ===");
    screenSetNormal();
    
    int instrucao_x = (MAXX / 2) - 13;
    screenGotoxy(instrucao_x, 7);
    screenSetColor(WHITE, DARKGRAY);
    printf("Aproxime-se dos magos!");
    
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
                    npcMostrarDialogoDiegoFinal(3, 19);
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
                    npcMostrarDialogoGuilhermeFinal(32, 19);
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
    printf("Salvando seu progresso...");
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
