#include "desafio_boss.h"
#include "screen.h"
#include "keyboard.h"
#include "ui.h"
#include <string.h>
#include <unistd.h>

void desafioBossIniciar(EstadoDesafioBoss *estado) {
    if (!estado) return;
    memset(estado->resposta, 0, sizeof(estado->resposta));
    estado->idx_resposta = 0;
    estado->ativo = 0;
}

void desafioBossAtivar(EstadoDesafioBoss *estado) {
    if (!estado) return;
    desafioBossIniciar(estado);
    estado->ativo = 1;
}

void desafioBossDesativar(EstadoDesafioBoss *estado) {
    if (!estado) return;
    estado->ativo = 0;
    uiLimparAreaInput();
}

int desafioBossEstaAtivo(const EstadoDesafioBoss *estado) {
    return estado ? estado->ativo : 0;
}

int desafioBossProcessarInput(EstadoDesafioBoss *estado, Boss *boss, 
                               Character *jogador, int *score) {
    if (!estado || !boss || !jogador || !score) return 0;
    
    int tecla = 0;
    
    while (keyhit()) {
        tecla = readch();
        
        if (tecla == 10 || tecla == 13) {
            estado->resposta[estado->idx_resposta] = '\0';
            
            if (logicaValidarResposta(&boss->equivalencia, estado->resposta)) {
                boss->ativo = 0;
                *score += 50;
                
                uiLimparAreaInput();
                uiMostrarFeedback("*** BOSS DERROTADO! +50pts ***", GREEN, 1500, MAXX / 2 - 10, MAXY / 2);
                if(boss->eh_final && boss->fase_2 == 0){
                    uiLimparAreaInput();
                    uiMostrarFeedback("*** EU ACHO QUE NÃO! -100pts ***", RED, 2000, MAXX / 2 - 10, MAXY / 2);
                    *score -= 100;
                    boss->ativo = 1;
                    boss->fase_2 = 1;
                    uiLimparAreaInput();
                    uiMostrarFeedback("*** EU ESTOU MAIS FORTE! +vida ***", RED, 2000, MAXX / 2 - 10, MAXY / 2);
                    boss->vida += 100;
                    boss->velocidade = 6;
                    boss->disparos = 1; 
                    uiLimparAreaInput();
                    uiMostrarFeedback("*** EU ESTOU MAIS RÁPIDO! + velocidade ***", RED, 2000, MAXX / 2 - 10, MAXY / 2);
                    uiLimparAreaInput();
                    uiMostrarFeedback("*** E VOCÊ CONTINUA FRACO! ***", RED, 2000, MAXX / 2 - 10, MAXY / 2);
                }
                else if(boss->fase_2 == 1){
                    uiMostrarFeedback("*** VOCÊ SALVOU NOSSA TERRA! +150pts ***", GREEN, 1500, MAXX / 2 - 10, MAXY / 2);
                }
                
            } else {
                jogador->lives--;
                
                uiLimparAreaInput();
                uiMostrarFeedback("*** ERRADO! -1 vida ***", RED, 1500, MAXX / 2 - 10, MAXY / 2);
            }
            
            boss->desafio_ativo = 0;
            bossLimparEquivalencia(boss);
            desafioBossDesativar(estado);
            return 1;
            
        } else if (tecla == 127 || tecla == 8) {
            if (estado->idx_resposta > 0) {
                estado->idx_resposta--;
                estado->resposta[estado->idx_resposta] = '\0';
            }
        } else if (tecla >= 32 && tecla < 127 && estado->idx_resposta < 63) {
            estado->resposta[estado->idx_resposta++] = tecla;
            estado->resposta[estado->idx_resposta] = '\0';
        }
    }
    
    return 0;
}

void desafioBossDesenharInterface(const EstadoDesafioBoss *estado) {
    if (!estado || !estado->ativo) return;
    
    screenGotoxy(MINX + 2, MAXY - 3);
    screenSetColor(YELLOW, DARKGRAY);
    screenSetBold();
    printf("DESAFIO DO BOSS! Digite a forma normal:");
    screenSetNormal();
    
    screenGotoxy(MINX + 2, MAXY - 2);
    screenSetColor(WHITE, DARKGRAY);
    printf("> %s_", estado->resposta);
}