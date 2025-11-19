#include "desafio_bau.h"
#include "screen.h"
#include "keyboard.h"
#include "logic.h"
#include <string.h>
#include <unistd.h>

static void limparAreaTabela() {
    for (int i = 0; i < 12; i++) {
        screenGotoxy(MAXX / 2 - 25, MAXY / 2 - 6 + i);
        printf("                                                              ");
    }
}

static void mostrarFeedback(const char *mensagem, screenColor cor, int tempo_ms) {
    limparAreaTabela();
    
    screenGotoxy(MAXX / 2 - 15, MAXY / 2);
    screenSetColor(cor, DARKGRAY);
    screenSetBold();
    printf("%s", mensagem);
    screenSetNormal();
    screenUpdate();
    usleep(tempo_ms * 1000);
    
    screenGotoxy(MAXX / 2 - 20, MAXY / 2);
    printf("                                          ");
}

  int validarTabelaVerdade(const char *linha1, const char *linha2) {
    if ((linha1[0] != 'F' && linha1[0] != 'f') && (linha1[0] != '0')) {
        return 0;
    }
    if ((linha2[0] != 'V' && linha2[0] != 'v') && (linha2[0] != '1')) {
        return 0;
    }
    
    return 1;
}

void desafioBauIniciar(EstadoDesafioBau *estado) {
    if (!estado) return;
    
    memset(estado->resposta_linha1, 0, sizeof(estado->resposta_linha1));
    memset(estado->resposta_linha2, 0, sizeof(estado->resposta_linha2));
    estado->idx_resposta_linha = 0;
    estado->linha_atual = 0;
    estado->tentativas = 0;
    estado->bau_index = -1;
    estado->ativo = 0;
}

void desafioBauAtivar(EstadoDesafioBau *estado, int bau_index) {
    if (!estado) return;
    
    desafioBauIniciar(estado);
    estado->bau_index = bau_index;
    estado->ativo = 1;
}

void desafioBauDesativar(EstadoDesafioBau *estado) {
    if (!estado) return;
    
    estado->ativo = 0;
    estado->bau_index = -1;
    limparAreaTabela();
}

int desafioBauEstaAtivo(const EstadoDesafioBau *estado) {
    return estado ? estado->ativo : 0;
}

int desafioBauProcessarInput(EstadoDesafioBau *estado, GerenciadorBau *gb, 
                             Character *jogador, int *score) {
    if (!estado || !gb || !jogador || !score) return 0;
    
    int tecla = 0;
    
    while (keyhit()) {
        tecla = readch();

        if (tecla == 10 || tecla == 13) {
            if (estado->linha_atual == 0) {
                estado->resposta_linha1[estado->idx_resposta_linha] = '\0';
                estado->linha_atual = 1;
                estado->idx_resposta_linha = 0;
            } else {
                estado->resposta_linha2[estado->idx_resposta_linha] = '\0';
                
                if (validarTabelaVerdade(estado->resposta_linha1, estado->resposta_linha2)) {
                    jogador->lives++;
                    *score += 10;
                    bauRemover(gb, estado->bau_index);
                    
                    mostrarFeedback("*** CORRETO! +1 vida +10pts ***", GREEN, 1500);
                    
                    desafioBauDesativar(estado);
                    
                } else {
                    estado->tentativas++;
                    
                    if (estado->tentativas >= 2) {
                        bauRemover(gb, estado->bau_index);
                        
                        mostrarFeedback("*** BAU PERDIDO! ***", RED, 1500);
                        
                        desafioBauDesativar(estado);
                        return 1; 
                        
                    } else {
                        char msg[64];
                        snprintf(msg, sizeof(msg), "*** ERRADO! Tentativa %d/2 ***", estado->tentativas);
                        mostrarFeedback(msg, YELLOW, 1000);
                        
                        estado->linha_atual = 0;
                        estado->idx_resposta_linha = 0;
                        memset(estado->resposta_linha1, 0, sizeof(estado->resposta_linha1));
                        memset(estado->resposta_linha2, 0, sizeof(estado->resposta_linha2));
                    }
                }
            }
        }
        else if (tecla == 127 || tecla == 8) {
            if (estado->idx_resposta_linha > 0) {
                estado->idx_resposta_linha--;
                if (estado->linha_atual == 0) {
                    estado->resposta_linha1[estado->idx_resposta_linha] = '\0';
                } else {
                    estado->resposta_linha2[estado->idx_resposta_linha] = '\0';
                }
            }
        }
        else if ((tecla == 'V' || tecla == 'v' || tecla == 'F' || tecla == 'f' ||
                 tecla == '1' || tecla == '0') && estado->idx_resposta_linha < 1) {
            if (estado->linha_atual == 0) {
                estado->resposta_linha1[estado->idx_resposta_linha++] = tecla;
                estado->resposta_linha1[estado->idx_resposta_linha] = '\0';
            } else {
                estado->resposta_linha2[estado->idx_resposta_linha++] = tecla;
                estado->resposta_linha2[estado->idx_resposta_linha] = '\0';
            }
        }
    }
    
    return 0; 
}

void desafioBauDesenharInterface(const EstadoDesafioBau *estado) {
    if (!estado || !estado->ativo) return;
    
    int start_y = MAXY / 2 - 4;

    screenGotoxy(MAXX / 2 - 20, start_y);
    screenSetColor(YELLOW, DARKGRAY);
    screenSetBold();
    printf("=== TABELA VERDADE: ~p ===");
    screenSetNormal();
    
    start_y += 2;
    
    screenGotoxy(MAXX / 2 - 10, start_y);
    screenSetColor(WHITE, DARKGRAY);
    printf("p  | ~p");
    start_y++;
    screenGotoxy(MAXX / 2 - 10, start_y);
    printf("---------");
    start_y++;
    
    screenGotoxy(MAXX / 2 - 10, start_y);
    printf("V  | %s", estado->linha_atual == 0 ? estado->resposta_linha1 : 
                     (estado->resposta_linha1[0] ? estado->resposta_linha1 : "_"));
    if (estado->linha_atual == 0) printf("_");
    
    start_y++;

    screenGotoxy(MAXX / 2 - 10, start_y);
    printf("F  | %s", estado->linha_atual == 1 ? estado->resposta_linha2 : 
                     (estado->resposta_linha2[0] ? estado->resposta_linha2 : "_"));
    if (estado->linha_atual == 1) printf("_");
    
    start_y += 2;

    screenGotoxy(MAXX / 2 - 20, start_y);
    screenSetColor(LIGHTCYAN, DARKGRAY);
    printf("Digite V/F ou 1/0 e pressione ENTER");
    
    start_y++;
    screenGotoxy(MAXX / 2 - 15, start_y);
    screenSetColor(YELLOW, DARKGRAY);
    printf("Tentativa: %d/2", estado->tentativas + 1);
}