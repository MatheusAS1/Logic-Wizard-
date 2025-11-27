#ifndef __UI_H__
#define __UI_H__


void uiLimparAreaDesafio();


void uiLimparAreaInput();


void uiDesenharHUDSuperior(int score, int level, int vidas, int inimigos, 
                           int boss_vida, int baus, int fps, int recorde, int history_mode);
void uiDesenharHUDInferior(int px, int py);

void uiMostrarFeedback(const char *mensagem, int cor, int tempo_ms, int x, int y);

#endif /* __UI_H__ */