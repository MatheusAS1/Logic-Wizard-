#ifndef __LOGIC_H__
#define __LOGIC_H__

#include "screen.h"

typedef enum {
    EQUIV_COMUTATIVA_OR,   
    EQUIV_COMUTATIVA_BICON,   
    EQUIV_IMPLICACAO,      
    EQUIV_CONTRAPOSITIVA,
    EQUIV_IDEMPOTENTE,     
    EQUIV_ABSORCAO,       
    EQUIV_DISTRIBUTIVA,
    EQUIV_DEFINICAO_BICON,     
    EQUIV_COMUTATIVA_AND, 
    EQUIV_ASSOCIATIVA,
    EQUIV_TOTAL_TYPES 
} TipoEquivalencia;

typedef struct {
    char forma_normal[64];      
    char forma_equivalente[64]; 
    TipoEquivalencia tipo;
    screenColor cor;
    char nome[32];
} Equivalencia;

typedef struct {
    Equivalencia equivalencias[EQUIV_TOTAL_TYPES];
    int total_equivalencias;
} SistemaLogica;

void logicaIniciar(SistemaLogica *sl);
void logicaDestruir(SistemaLogica *sl);
void logicaDesenharTabela(const SistemaLogica *sl);
Equivalencia logicaGetEquivalenciaAleatoria(const SistemaLogica *sl);
screenColor logicaGetCor(TipoEquivalencia tipo);
int logicaValidarResposta(const Equivalencia *equiv, const char *resposta_jogador);
int logicaValidarRespostaInimigo(const void *inimigo, const char *resposta_jogador);
void logicaNormalizarString(char *str);
int logicaCompararExpressoes(const char *expr1, const char *expr2);
int logicaValidarCaracteresRecursivo(const char *str, int index);
int logicaContarVariaveisRecursivo(const char *str, int index);
void logicaInverterStringRecursivo(char *str, int inicio, int fim);

#endif /* __LOGIC_H__ */