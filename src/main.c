#include <stdio.h>
#include <stdlib.h> // Adicionado para rand()
#include <unistd.h> // Adicionado para a função sleep()
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "character.h"
#include "projectile.h"
#include "enemy.h"

int main()
{
    Character jogador;
    GerenciadorProjetil gp;
    GerenciadorInimigo gi;
    Boss boss;
    int tecla = 0;
    
    int contador_frames = 0;
    int fps_atual = 0;
    int base_enemy_count = 2; 
    int base_enemy_life = 2;  
    int base_boss_life = 10;  
    int level = 1;          
    int boss_spawned = 0;
    int boss_timer = 0;
    int score = 0;
    int velocidade_inicial = 10; 

    screenInit(1);
    keyboardInit();
    timerInit(50);
    gerenciadorProjetilIniciar(&gp);
    gerenciadorInimigoIniciar(&gi, base_enemy_count * level);

    characterInit(&jogador, 40, 12, "(-_-)/*");
    jogador.lives = 3; 
    characterDraw(&jogador);
    screenUpdate();

    for (int i = 0; i < base_enemy_count * level; ++i) {
        int x = (rand() % (MAXX - MINX - 6)) + MINX + 2; 
        int y = (rand() % (MAXY - MINY - 2)) + MINY + 1;
        inimigoSpawn(&gi, x, y, base_enemy_life * level, velocidade_inicial - (level > 1 ? level-1 : 0));
    }

    while (tecla != 27 && jogador.lives > 0)
    {
        if (timerTimeOver()) {

        int px, py; 


        characterClear(&jogador);
        gerenciadorProjetilLimpar(&gp);
        gerenciadorInimigoLimpar(&gi);
        bossLimpar(&boss);


        tecla = 0;
        while (keyhit()) {
            tecla = readch();
        }

        if (tecla) { 
            if (tecla == 'w') {
                characterMove(&jogador, 0, -1);
                characterSetDir(&jogador, 0, -1);
            } else if (tecla == 's') {
                characterMove(&jogador, 0, 1);
                characterSetDir(&jogador, 0, 1);
            } else if (tecla == 'a') {
                characterMove(&jogador, -1, 0);
                characterSetDir(&jogador, -1, 0);
            } else if (tecla == 'd') {
                characterMove(&jogador, 1, 0);
                characterSetDir(&jogador, 1, 0);
            }

            if (tecla == 'v') {
                int px, py, dir_x, dir_y;
                characterGetPos(&jogador, &px, &py);
                characterGetDir(&jogador, &dir_x, &dir_y);
                
                int spawn_x = px + (dir_x * 7);  
                int spawn_y = py + (dir_y * 2);  
                
                projetilCriar(&gp, spawn_x, spawn_y, dir_x, dir_y);
            }

            if (tecla == 'F' || tecla == 'f') {
                int px, py;
                characterGetPos(&jogador, &px, &py);

                if (py - 2 > MINY + 1)
                    projetilCriarEspecial(&gp, px, py - 2, 0, -1);

                if (py + 2 < MAXY - 1)
                    projetilCriarEspecial(&gp, px, py + 2, 0, 1);

                if (px - 2 > MINX + 1)
                    projetilCriarEspecial(&gp, px - 2, py, -1, 0);

                if (px + 9 < MAXX - 3)
                    projetilCriarEspecial(&gp, px + 9, py, 1, 0);
            }
        }

        gerenciadorProjetilAtualizar(&gp);

        characterGetPos(&jogador, &px, &py);
        gerenciadorInimigoAtualizar(&gi, px, py);

        if (!boss_spawned && gi.quantidade == 0) {
            boss_timer++;
            if (boss_timer >= 100) {
                bossIniciar(&boss, (MINX + MAXX) / 2 - 3, MINY + 1, base_boss_life * (1 << (level-1)), velocidade_inicial - (level > 1 ? (level-1) * 2 : 0)); // Boss escala velocidade mais rápido
                boss_spawned = 1;
            }
        } else if (gi.quantidade > 0) {
            boss_timer = 0;
        }

        if (boss_spawned && boss.ativo) {
            bossAtualizar(&boss, px, py);
        }

        for (int i = 0; i < gi.quantidade; ++i) {
            Inimigo *ini = &gi.inimigos[i];
            if (!ini->ativo) continue;
            if (px < ini->x + 5 && px + 8 > ini->x && py == ini->y) {
                jogador.lives--;
                ini->ativo = 0; 
            }
        }

        if (boss_spawned && boss.ativo) {
            if (px < boss.x + 8 && px + 8 > boss.x && py == boss.y) {
                jogador.lives = 0; 
            }
        }

        for (int i = 0; i < gp.quantidade_simples; ++i) {
            Projetil *p = &gp.projeteis[i];
            if (!p->ativo) continue;

            for (int j = 0; j < gi.quantidade; ++j) {
                Inimigo *ini = &gi.inimigos[j];
                if (!ini->ativo) continue;
                if (p->y == ini->y && p->x >= ini->x && p->x < ini->x + 5) {
                    ini->vida -= p->dano;
                    p->ativo = 0; 
                    if (ini->vida <= 0) { ini->ativo = 0; score++; }
                    break; 
                }
            }

            if (boss_spawned && boss.ativo) {
                if (p->y == boss.y && p->x >= boss.x && p->x < boss.x + 8) {
                    boss.vida -= p->dano;
                    p->ativo = 0;
                    if (boss.vida <= 0) {
                        boss.ativo = 0;
                        score += 10; 
                    }
                }
            }
        }

        for (int i = 0; i < gp.quantidade_especial; ++i) {
            Projetil *p = &gp.projeteis[MAX_PROJETIL_SIMPLES + i];
            if (!p->ativo) continue;
            for (int j = 0; j < gi.quantidade; ++j) {
                Inimigo *ini = &gi.inimigos[j];
                if (!ini->ativo) continue;
                if (p->y == ini->y && p->x >= ini->x && p->x < ini->x + 5) {
                    ini->vida -= p->dano;
                    p->ativo = 0; 
                    if (ini->vida <= 0) { ini->ativo = 0; score++; }
                    break;
                }
            }
            if (boss_spawned && boss.ativo) {
                if (p->y == boss.y && p->x >= boss.x && p->x < boss.x + 8) {
                    boss.vida -= p->dano;
                    p->ativo = 0;
                    if (boss.vida <= 0) {
                        boss.ativo = 0;
                        score += 10; 
                    }
                }
            }
        }
        if (boss_spawned && !boss.ativo) {
            level++;
            int new_enemy_count = base_enemy_count * level;


            gerenciadorInimigoDestruir(&gi);
            gerenciadorInimigoIniciar(&gi, new_enemy_count);

            gerenciadorProjetilIniciar(&gp);

            jogador.lives = 3;

            for (int k = 0; k < new_enemy_count; ++k) {
                int x = (rand() % (MAXX - MINX - 6)) + MINX + 2;
                int y = (rand() % (MAXY - MINY - 2)) + MINY + 1;
                inimigoSpawn(&gi, x, y, base_enemy_life * level, velocidade_inicial - (level > 1 ? level-1 : 0));
            }

            boss_spawned = 0;
            boss_timer = 0;
            boss.ativo = 0;
        }

        characterDraw(&jogador);
        gerenciadorProjetilDesenhar(&gp);
        gerenciadorInimigoDesenhar(&gi);
        if (boss_spawned && boss.ativo) bossDesenhar(&boss);

        gerenciadorProjetilCompactar(&gp);
        gerenciadorInimigoCompactar(&gi);
        
        contador_frames++;
        if (contador_frames >= 20) {  
            fps_atual = contador_frames;
            contador_frames = 0;
        }
        
        screenGotoxy(70, 1);
        screenSetColor(GREEN, DARKGRAY);
        printf("Score: %d | Level: %d | Vidas: %d | Inimigos: %d | Boss Vida: %d | FPS: %d", score, level, jogador.lives, gi.quantidade, boss.ativo ? boss.vida : 0, fps_atual);
        
        characterGetPos(&jogador, &px, &py);
        screenGotoxy(5, MAXY + 1);
        screenSetColor(YELLOW, DARKGRAY);
        printf("Pos: (%d,%d)  Tecla: %c (%d) ", px, py, (tecla > 31 && tecla < 127) ? tecla : '?', tecla);
        screenUpdate();

        }
    }

    if (jogador.lives <= 0) {
        screenClear();
        screenGotoxy(MAXX / 2 - 5, MAXY / 2);
        screenSetColor(RED, DARKGRAY);
        printf("GAME OVER");
        screenGotoxy(1, MAXY); 
        screenUpdate();
        sleep(3); 
    }

    characterDestroy(&jogador);
    gerenciadorProjetilDestruir(&gp);
    gerenciadorInimigoDestruir(&gi);
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    return 0;
}
