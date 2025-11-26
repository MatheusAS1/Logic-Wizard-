#include "desafio_bau.h"
#include "screen.h"
#include "keyboard.h"
#include "logic.h"
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h>


static void limparAreaTabela() {
    for (int i = 0; i < 14; i++) { 
        screenGotoxy(MAXX / 2 - 25, MAXY / 2 - 7 + i);
        printf("                                                  ");
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
    printf("                                      ");
}

int inputParaBool(char c) {
    if (c == 'V' || c == 'v' || c == '1') return 1;
    if (c == 'F' || c == 'f' || c == '0') return 0;
    return -1;
}

int obterResultadoEsperado(TipoDesafioBau tipo, int linha) {
    int p, q;

    if (tipo == DESAFIO_NEGACAO) {
        p = (linha == 0) ? 1 : 0;
        q = 0; 
    } else {
        p = (linha == 0 || linha == 1) ? 1 : 0;
        q = (linha == 0 || linha == 2) ? 1 : 0;
    }

    switch (tipo) {
        case DESAFIO_NEGACAO: 
            return !p;
            
        case DESAFIO_CONJUNCAO:     return p && q;       
        case DESAFIO_DISJUNCAO:     return p || q;         
        case DESAFIO_IMPLICACAO:    return (!p) || q;      
        case DESAFIO_BICONDICIONAL: return p == q;     
        default: return 0;
    }
}

int validarTodasRespostas(const EstadoDesafioBau *estado) {
    for (int i = 0; i < estado->total_linhas; i++) {
        int input = inputParaBool(estado->respostas[i][0]);
        int esperado = obterResultadoEsperado(estado->tipo, i);
        
        if (input != esperado) return 0; 
    }
    return 1; 
}

void desafioBauIniciar(EstadoDesafioBau *estado) {
    if (!estado) return;
    
    for(int i=0; i<4; i++) {
        memset(estado->respostas[i], 0, sizeof(estado->respostas[i]));
    }
    
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
    
    estado->tipo = rand() % 5;
    
    if (estado->tipo == DESAFIO_NEGACAO) {
        estado->total_linhas = 2;
    } else {
        estado->total_linhas = 4;
    }
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
            
            estado->respostas[estado->linha_atual][estado->idx_resposta_linha] = '\0';
            if (estado->linha_atual < estado->total_linhas - 1) {
                estado->linha_atual++;
                estado->idx_resposta_linha = 0;
            } 
            else { 
                if (validarTodasRespostas(estado)) {
                    jogador->lives++;
                    *score += 15; 
                    bauRemover(gb, estado->bau_index);
                    mostrarFeedback("*** CORRETO! +1 vida +15pts ***", GREEN, 1500);
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
                        for(int i=0; i<4; i++) memset(estado->respostas[i], 0, 2);
                    }
                }
            }
        }
        else if (tecla == 127 || tecla == 8) {
            if (estado->idx_resposta_linha > 0) {
                estado->idx_resposta_linha--;
                estado->respostas[estado->linha_atual][estado->idx_resposta_linha] = '\0';
            } else if (estado->linha_atual > 0) {
                estado->linha_atual--;
                estado->idx_resposta_linha = 1; 
                estado->respostas[estado->linha_atual][estado->idx_resposta_linha] = '\0';
            }
        }
        else if ((tecla == 'V' || tecla == 'v' || tecla == 'F' || tecla == 'f' ||
                 tecla == '1' || tecla == '0') && estado->idx_resposta_linha < 1) {
            
            estado->respostas[estado->linha_atual][estado->idx_resposta_linha++] = tecla;
            estado->respostas[estado->linha_atual][estado->idx_resposta_linha] = '\0';
        }
    }
    return 0; 
}

void desafioBauDesenharInterface(const EstadoDesafioBau *estado) {
    if (!estado || !estado->ativo) return;
    
    int start_y = MAXY / 2 - 6;
    int cx = MAXX / 2; 

    screenGotoxy(cx - 20, start_y);
    screenSetColor(YELLOW, DARKGRAY);
    screenSetBold();

    switch(estado->tipo) {
        case DESAFIO_NEGACAO:       printf("=== TABELA: NEGACAO (~p) ==="); break;
        case DESAFIO_CONJUNCAO:     printf("=== TABELA: CONJUNCAO (p^q) ==="); break;
        case DESAFIO_DISJUNCAO:     printf("=== TABELA: DISJUNCAO (pvq) ==="); break;
        case DESAFIO_IMPLICACAO:    printf("=== TABELA: IMPLICACAO (p->q) ==="); break;
        case DESAFIO_BICONDICIONAL: printf("=== TABELA: BICON. (p<->q) ==="); break;
    }
    screenSetNormal();
    
    start_y += 2;
    
    screenGotoxy(cx - 12, start_y);
    screenSetColor(WHITE, DARKGRAY);

    if (estado->tipo == DESAFIO_NEGACAO) {
        printf(" p | ~p ");
        screenGotoxy(cx - 12, ++start_y);
        printf("---|----");
    } else {
        char op[10];
        if (estado->tipo == DESAFIO_CONJUNCAO) strcpy(op, "p^q");
        else if (estado->tipo == DESAFIO_DISJUNCAO) strcpy(op, "pvq");
        else if (estado->tipo == DESAFIO_IMPLICACAO) strcpy(op, "p->q");
        else strcpy(op, "p<->q");

        printf(" p | q | %-5s", op);
        screenGotoxy(cx - 12, ++start_y);
        printf("---|---|-------");
    }

    char *vals_p[] = {"V", "V", "F", "F"};
    char *vals_q[] = {"V", "F", "V", "F"}; 

    for (int i = 0; i < estado->total_linhas; i++) {
        start_y++;
        screenGotoxy(cx - 12, start_y);
        
        if (i == estado->linha_atual) screenSetColor(YELLOW, DARKGRAY);
        else screenSetColor(WHITE, DARKGRAY);

        if (estado->tipo == DESAFIO_NEGACAO) {
            char *val_p = (i == 0) ? "V" : "F";
            printf(" %s | %s_", val_p, estado->respostas[i]);
        } else {
            printf(" %s | %s | %s_", vals_p[i], vals_q[i], estado->respostas[i]);
        }
    }
    
    start_y += 2;
    screenGotoxy(cx - 20, start_y);
    screenSetColor(LIGHTCYAN, DARKGRAY);
    printf("Digite V/F e ENTER para proxima linha");
    
    screenGotoxy(cx - 15, start_y + 1);
    screenSetColor(YELLOW, DARKGRAY);
    printf("Tentativa: %d/2", estado->tentativas + 1);
}