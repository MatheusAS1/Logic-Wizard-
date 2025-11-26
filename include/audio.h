#ifndef AUDIO_H
#define AUDIO_H

int audioInit(void);
void audioQuit(void);
int audioPlayMusic(const char *filepath, int loops);
void audioPauseMusic(void);
void audioResumeMusic(void);
void audioStopMusic(void);
void audioSetMusicVolume(int volume);
int audioIsMusicPlaying(void);
int audioIsMusicPaused(void);
int audioLoadSound(const char *filepath);
void audioPlaySound(int soundId, int volume);
void audioSetSoundVolume(int volume);

#endif // AUDIO_H
