#include "logic.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

void logicaIniciar(SistemaLogica *sl) {
    if (!sl) return;
    
    sl->total_equivalencias = EQUIV_TOTAL_TYPES;
    
    strcpy(sl->equivalencias[EQUIV_COMUTATIVA_OR].forma_normal, "PvQ");
    strcpy(sl->equivalencias[EQUIV_COMUTATIVA_OR].forma_equivalente, "QvP");
    sl->equivalencias[EQUIV_COMUTATIVA_OR].tipo = EQUIV_COMUTATIVA_OR;
    sl->equivalencias[EQUIV_COMUTATIVA_OR].cor = GREEN;
    strcpy(sl->equivalencias[EQUIV_COMUTATIVA_OR].nome, "Comut. OR");

    strcpy(sl->equivalencias[EQUIV_COMUTATIVA_BICON].forma_normal, "P<->Q");
    strcpy(sl->equivalencias[EQUIV_COMUTATIVA_BICON].forma_equivalente, "Q<->P");
    sl->equivalencias[EQUIV_COMUTATIVA_BICON].tipo = EQUIV_COMUTATIVA_BICON;
    sl->equivalencias[EQUIV_COMUTATIVA_BICON].cor = BLUE;
    strcpy(sl->equivalencias[EQUIV_COMUTATIVA_BICON].nome, "Comut. <->");

    strcpy(sl->equivalencias[EQUIV_IMPLICACAO].forma_normal, "P->Q");
    strcpy(sl->equivalencias[EQUIV_IMPLICACAO].forma_equivalente, "~PvQ");
    sl->equivalencias[EQUIV_IMPLICACAO].tipo = EQUIV_IMPLICACAO;
    sl->equivalencias[EQUIV_IMPLICACAO].cor = RED;
    strcpy(sl->equivalencias[EQUIV_IMPLICACAO].nome, "Def. Implic.");

    strcpy(sl->equivalencias[EQUIV_CONTRAPOSITIVA].forma_normal, "P->Q");
    strcpy(sl->equivalencias[EQUIV_CONTRAPOSITIVA].forma_equivalente, "~Q->~P");
    sl->equivalencias[EQUIV_CONTRAPOSITIVA].tipo = EQUIV_CONTRAPOSITIVA;
    sl->equivalencias[EQUIV_CONTRAPOSITIVA].cor = MAGENTA;
    strcpy(sl->equivalencias[EQUIV_CONTRAPOSITIVA].nome, "Contrapositiva");

    strcpy(sl->equivalencias[EQUIV_IDEMPOTENTE].forma_normal, "P");
    strcpy(sl->equivalencias[EQUIV_IDEMPOTENTE].forma_equivalente, "P^P");
    sl->equivalencias[EQUIV_IDEMPOTENTE].tipo = EQUIV_IDEMPOTENTE;
    sl->equivalencias[EQUIV_IDEMPOTENTE].cor = YELLOW;
    strcpy(sl->equivalencias[EQUIV_IDEMPOTENTE].nome, "Idempotente");

    strcpy(sl->equivalencias[EQUIV_ABSORCAO].forma_normal, "P");
    strcpy(sl->equivalencias[EQUIV_ABSORCAO].forma_equivalente, "P^(PvQ)");
    sl->equivalencias[EQUIV_ABSORCAO].tipo = EQUIV_ABSORCAO;
    sl->equivalencias[EQUIV_ABSORCAO].cor = CYAN;
    strcpy(sl->equivalencias[EQUIV_ABSORCAO].nome, "Absorcao");

    strcpy(sl->equivalencias[EQUIV_DISTRIBUTIVA].forma_normal, "P^(QvS)");
    strcpy(sl->equivalencias[EQUIV_DISTRIBUTIVA].forma_equivalente, "(P^Q)v(P^S)");
    sl->equivalencias[EQUIV_DISTRIBUTIVA].tipo = EQUIV_DISTRIBUTIVA;
    sl->equivalencias[EQUIV_DISTRIBUTIVA].cor = LIGHTGRAY;
    strcpy(sl->equivalencias[EQUIV_DISTRIBUTIVA].nome, "Distributiva");

    strcpy(sl->equivalencias[EQUIV_DEFINICAO_BICON].forma_normal, "P<->Q");
    strcpy(sl->equivalencias[EQUIV_DEFINICAO_BICON].forma_equivalente, "(P->Q)^(Q->P)");
    sl->equivalencias[EQUIV_DEFINICAO_BICON].tipo = EQUIV_DEFINICAO_BICON;
    sl->equivalencias[EQUIV_DEFINICAO_BICON].cor = BROWN;
    strcpy(sl->equivalencias[EQUIV_DEFINICAO_BICON].nome, "Def. Bicon.");

    strcpy(sl->equivalencias[EQUIV_COMUTATIVA_AND].forma_normal, "P^Q");
    strcpy(sl->equivalencias[EQUIV_COMUTATIVA_AND].forma_equivalente, "Q^P");
    sl->equivalencias[EQUIV_COMUTATIVA_AND].tipo = EQUIV_COMUTATIVA_AND;
    sl->equivalencias[EQUIV_COMUTATIVA_AND].cor = GREEN;
    strcpy(sl->equivalencias[EQUIV_COMUTATIVA_AND].nome, "Comut. AND");

    strcpy(sl->equivalencias[EQUIV_ASSOCIATIVA].forma_normal, "P^(Q^S)");
    strcpy(sl->equivalencias[EQUIV_ASSOCIATIVA].forma_equivalente, "(P^Q)^S");
    sl->equivalencias[EQUIV_ASSOCIATIVA].tipo = EQUIV_ASSOCIATIVA;
    sl->equivalencias[EQUIV_ASSOCIATIVA].cor = BLUE;
    strcpy(sl->equivalencias[EQUIV_ASSOCIATIVA].nome, "Associativa");

    srand(time(NULL));
}

void logicaDestruir(SistemaLogica *sl) {
    (void)sl;
}

void logicaDesenharTabela(const SistemaLogica *sl) {
    if (!sl) return;

    int start_x = MAXX + 200;
    int start_y = 3;
    
    screenGotoxy(start_x+30, start_y);
    screenSetColor(YELLOW, DARKGRAY);
    screenSetBold();
    printf("=== GUIA DE EQUIVALENCIAS ===");
    screenSetNormal();
    
    start_y += 2;
    
    screenGotoxy(start_x, start_y);
    screenSetColor(WHITE, DARKGRAY);
    printf("Cor          | Inimigo  -> Resposta");
    
    start_y++;
    screenGotoxy(start_x, start_y);
    printf("--------------------------------------");
    start_y++;
    
    for (int i = 0; i < sl->total_equivalencias; i++) {
        screenGotoxy(start_x, start_y + i);
        
        screenSetColor(sl->equivalencias[i].cor, DARKGRAY);
        printf("%-12s", sl->equivalencias[i].nome);
        
        screenSetColor(WHITE, DARKGRAY);
        printf(" | ");
        screenSetColor(sl->equivalencias[i].cor, DARKGRAY);
        printf("%s", sl->equivalencias[i].forma_equivalente);
        screenSetColor(WHITE, DARKGRAY);
        printf(" -> ");
        screenSetColor(LIGHTGREEN, DARKGRAY);
        printf("%s", sl->equivalencias[i].forma_normal);
    }
}

void logicaApagarTabela(const SistemaLogica *sl) {
    if (!sl) return;

    int start_x = MAXX + 10;
    int start_y = 3;
    int total_linhas = 4 + sl->total_equivalencias + 2 + 3;
    char borracha[] = "                                                            ";

    screenSetColor(WHITE, DARKGRAY);

    for (int i = 0; i < total_linhas; i++) {
        screenGotoxy(start_x, start_y + i);
        printf("%s", borracha);
    }
}

Equivalencia logicaGetEquivalenciaAleatoria(const SistemaLogica *sl) {
    if (!sl || sl->total_equivalencias == 0) {
        Equivalencia vazia = {0};
        return vazia;
    }
    
    int idx = rand() % sl->total_equivalencias;
    return sl->equivalencias[idx];
}

screenColor logicaGetCor(TipoEquivalencia tipo) {
    switch(tipo) {
        case EQUIV_COMUTATIVA_OR:
            return GREEN;
        case EQUIV_COMUTATIVA_BICON:
            return BLUE;
        default:
            return WHITE;
    }
}

void logicaNormalizarString(char *str) {
    if (!str) return;
    
    int j = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            str[j++] = toupper(str[i]);
        }
    }
    str[j] = '\0';
}




int logicaCompararExpressoes(const char *expr1, const char *expr2) {
    if (!expr1 || !expr2) return 0;
    
    char temp1[64], temp2[64];
    strncpy(temp1, expr1, 63);
    strncpy(temp2, expr2, 63);
    temp1[63] = '\0';
    temp2[63] = '\0';
    
    logicaNormalizarString(temp1);
    logicaNormalizarString(temp2);
    
    return strcmp(temp1, temp2) == 0;
}

int logicaValidarResposta(const Equivalencia *equiv, const char *resposta_jogador) {
    
    if (!equiv || !resposta_jogador) return 0;
    if(*resposta_jogador == 'k' || *resposta_jogador == 'K'){
        return 1;
    }
    if (!logicaValidarCaracteresRecursivo(resposta_jogador, 0)) {
        return 0;
    }
    
    return logicaCompararExpressoes(equiv->forma_normal, resposta_jogador);
}

int logicaValidarRespostaInimigo(const void *inimigo, const char *resposta_jogador) {
    if (!inimigo || !resposta_jogador) return 0;

    typedef struct {
        int x, y, vida, ativo, contador_frames, velocidade;
        Equivalencia equivalencia;
    } InimigoInterno;
    
    const InimigoInterno *ini_interno = (const InimigoInterno*)inimigo;
    
    if (!logicaValidarCaracteresRecursivo(resposta_jogador, 0)) {
        return 0;
    }
    
    return logicaCompararExpressoes(ini_interno->equivalencia.forma_normal, resposta_jogador);
}

int logicaValidarCaracteresRecursivo(const char *str, int index) {
    if (str[index] == '\0') {
        return 1;
    }
    
    char c = toupper(str[index]);
    int valido = (c == 'P' || c == 'Q' || c == 'V' || 
                  c == '<' || c == '-' || c == '>' || 
                  c == '^' || c == '~' || c == '(' || c == ')' ||
                  c == 'S' || 
                  c == ' ' || c == '\t' || c == '\n');
    
    if (!valido) {
        return 0;
    }
    
    return logicaValidarCaracteresRecursivo(str, index + 1);
}

int logicaContarVariaveisRecursivo(const char *str, int index) {
    if (str[index] == '\0') {
        return 0;
    }
    
    char c = toupper(str[index]);
    int eh_variavel = (c == 'P' || c == 'Q') ? 1 : 0;
    
    return eh_variavel + logicaContarVariaveisRecursivo(str, index + 1);
}

void logicaInverterStringRecursivo(char *str, int inicio, int fim) {
    if (inicio >= fim) {
        return;
    }
    
    char temp = str[inicio];
    str[inicio] = str[fim];
    str[fim] = temp;
    
    logicaInverterStringRecursivo(str, inicio + 1, fim - 1);
}
