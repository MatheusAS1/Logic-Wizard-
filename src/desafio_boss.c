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
                uiMostrarFeedback("*** BOSS DERROTADO! ***", GREEN, 3000, MAXX / 2 - 10, MAXY / 2);
                if(boss->eh_final && boss->fase_2 == 0){
                    uiLimparAreaInput();
                    uiMostrarFeedback("*** EU ACHO QUE NÃO! ***", RED, 4000, MAXX / 2 - 10, MAXY / 2);
                    *score -= 100;
                    boss->ativo = 1;
                    boss->fase_2 = 1;
                    uiLimparAreaInput();
                    uiMostrarFeedback("*** EU ESTOU MAIS FORTE! +vida ***", RED, 4000, MAXX / 2 - 10, MAXY / 2);
                    boss->vida += 100;
                    boss->velocidade = 6;
                    boss->disparos = 1; 
                    uiLimparAreaInput();
                    uiMostrarFeedback("*** EU ESTOU MAIS RÁPIDO! + velocidade ***", RED, 4000, MAXX / 2 - 10, MAXY / 2);
                    uiLimparAreaInput();
                    uiMostrarFeedback("*** E VOCÊ CONTINUA FRACO! ***", RED, 4000, MAXX / 2 - 10, MAXY / 2);
                }
                else if(boss->fase_2 == 1){
                    uiMostrarFeedback("*** VOCÊ SALVOU NOSSA TERRA!***", GREEN, 3000, MAXX / 2 - 10, MAXY / 2);
                }
                else if(boss->variante == 1){
                    uiMostrarFeedback("*** NÚCLEO CORROMPIDO: QUEM É VOCÊ?! ***", RED, 4000, MAXX / 2 - 15, MAXY / 2);
                    uiMostrarFeedback("*** NÚCLEO CORROMPIDO: AQUELES DOIS DEVEM TER TE ENVIADO ***", RED, 4000, MAXX / 2 - 25, MAXY / 2);
                    uiMostrarFeedback("*** NÚCLEO CORROMPIDO: ERRO O SEU, VAI MORRER ANTES DE CHEGAR ATÉ MIM! ***", RED, 4000, MAXX / 2 - 34, MAXY / 2);

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
    
    uiLimparAreaInput();
    screenGotoxy(MINX + 2, MAXY - 3);
    screenSetColor(YELLOW, DARKGRAY);
    screenSetBold();
    printf("DESAFIO DO BOSS! Digite a sua equivalência:");
    screenSetNormal();
    
    screenGotoxy(MINX + 2, MAXY - 2);
    screenSetColor(WHITE, DARKGRAY);
    printf("> %s_", estado->resposta);
}