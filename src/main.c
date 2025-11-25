#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "storage.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "history_mode.h"
#include "npc.h"
#include "menu.h" 
#include "creditos.h"





int main()
{

    int opcao = 0; 
    
    while (opcao != 4) {
        opcao = exibirMenuPrincipal(); 
        
        switch(opcao) {
            case 1:
                iniciarModoHistoria(); 
                break;
            case 2:
                exibirTelaIntroducao();
                break;
            case 3:
                exibirCreditos();
                break;
            case 4:
                break;
        }
    }
    
    screenClear();
    printf("Obrigado por jogar Logic Wizard!\n");
    
    return 0;
}