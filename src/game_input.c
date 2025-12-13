#include "game_input.h"
#include "keyboard.h"
#include "screen.h"

int processarInputJogador(Character *jogador, GerenciadorProjetil *gp,int modo) {
    if (!jogador || !gp) return 0;
    
    int tecla = 0;
    
    while (keyhit()) {
        tecla = readch();
    }
    
    if (tecla) {
        if (tecla == 'w' || tecla == 'W') {
            characterMove(jogador, 0, -1);
            characterSetDir(jogador, 0, -1);
        } else if (tecla == 's' || tecla == 'S') {
            characterMove(jogador, 0, 1);
            characterSetDir(jogador, 0, 1);
        } else if (tecla == 'a' || tecla == 'A') {
            characterMove(jogador, -1, 0);
            characterSetDir(jogador, -1, 0);
        } else if (tecla == 'd' || tecla == 'D') {
            characterMove(jogador, 1, 0);
            characterSetDir(jogador, 1, 0);
        }
        
        if (tecla == 'v' || tecla == 'V') {
            int px_temp, py_temp, dir_x, dir_y;
            characterGetPos(jogador, &px_temp, &py_temp);
            characterGetDir(jogador, &dir_x, &dir_y);
            int spawn_x = px_temp + (dir_x * 7);
            int spawn_y = py_temp + (dir_y * 2);
            projetilCriar(gp, spawn_x, spawn_y, dir_x, dir_y,modo);
        }
        
        if (tecla == 'F' || tecla == 'f') {
            int px_temp, py_temp;
            characterGetPos(jogador, &px_temp, &py_temp);

            if (py_temp - 2 > MINY + 1)
                projetilCriarEspecial(gp, px_temp, py_temp - 2, 0, -1,modo);
            if (py_temp + 2 < MAXY - 1)
                projetilCriarEspecial(gp, px_temp, py_temp + 2, 0, 1,modo);
            if (px_temp - 2 > MINX + 1)
                projetilCriarEspecial(gp, px_temp - 2, py_temp, -1, 0,modo);
            if (px_temp + 9 < MAXX - 3)
                projetilCriarEspecial(gp, px_temp + 9, py_temp, 1, 0,modo);
        }
        
    }
    return tecla;
}