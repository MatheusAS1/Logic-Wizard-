#include "storage.h"
#include <stdio.h>

#define ARQUIVO_RECORDE "recorde.txt"

int storageCarregarRecorde() {
    FILE *f = fopen(ARQUIVO_RECORDE, "r");
    int recorde = 0;
    
    if (f) {
        if (fscanf(f, "%d", &recorde) != 1) {
            recorde = 0; 
        }
        fclose(f);
    }
    
    return recorde;
}

void storageSalvarRecorde(int novo_recorde) {
    FILE *f = fopen(ARQUIVO_RECORDE, "w");
    if (f) {
        fprintf(f, "%d", novo_recorde);
        fclose(f);
    }
}