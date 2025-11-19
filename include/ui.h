#ifndef __UI_H__
#define __UI_H__

/**
 * Limpa a área central onde aparecem desafios
 */
void uiLimparAreaDesafio();

/**
 * Limpa a área de input inferior (boss)
 */
void uiLimparAreaInput();

/**
 * Desenha o HUD superior com informações do jogo
 */
void uiDesenharHUDSuperior(int score, int level, int vidas, int inimigos, 
                           int boss_vida, int baus, int fps);

/**
 * Desenha o HUD inferior com controles
 */
void uiDesenharHUDInferior(int px, int py);

/**
 * Mostra mensagem de feedback temporária
 */
void uiMostrarFeedback(const char *mensagem, int cor, int tempo_ms, int x, int y);

#endif /* __UI_H__ */