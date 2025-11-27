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
#include "arcade_mode.h"
#include "npc.h"
#include "menu.h" 
#include "creditos.h"
#include "audio.h"

int main()
{
    if (audioInit() != 0) {
        fprintf(stderr, "Aviso: Sistema de áudio não disponível. O jogo continuará sem música.\n");
    } else {
        audioSetMusicVolume(20);
        
        if (audioPlayMusic("assets/music/menu_music.ogg", -1) != 0) {
            audioPlayMusic("assets/music/menu_music.mp3", -1);
        }
    }

    int opcao = 0; 
    while (opcao != 5) {
        opcao = exibirMenuPrincipal(); 
        
        switch(opcao) {
            case 1:
                int final = iniciarModoHistoria(); 
                if(final == 1){
                    exibirCreditos();
                }
                break;
            case 2:
                iniciarModoArcade();
                break;
            case 3:
                exibirTelaIntroducao();
                break;
            case 4:
                exibirCreditos();
                break;
            case 5:
                break;
        }
    }
    
    audioQuit();
    
    screenClear();
    printf("Obrigado por jogar Logic Wizard!\n");
    
    return 0;
}