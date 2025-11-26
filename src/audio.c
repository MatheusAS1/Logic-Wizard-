#include "audio.h"
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

static Mix_Music *currentMusic = NULL;

#define MAX_SOUNDS 8
static Mix_Chunk *sounds[MAX_SOUNDS] = {NULL};
static int soundCount = 0;

int audioInit(void) {
    SDL_SetHint(SDL_HINT_AUDIO_RESAMPLING_MODE, "1");
    
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        return -1;
    }
    
    if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 16384) < 0) {
        SDL_Quit();
        return -1;
    }
    
    Mix_AllocateChannels(8);
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    
    return 0;
}

void audioQuit(void) {
    if (currentMusic != NULL) {
        Mix_HaltMusic();
        Mix_FreeMusic(currentMusic);
        currentMusic = NULL;
    }
    
    for (int i = 0; i < MAX_SOUNDS; i++) {
        if (sounds[i] != NULL) {
            Mix_FreeChunk(sounds[i]);
            sounds[i] = NULL;
        }
    }
    
    Mix_Quit();
}

int audioPlayMusic(const char *filepath, int loops) {
    if (currentMusic != NULL) {
        Mix_HaltMusic();
        Mix_FreeMusic(currentMusic);
        currentMusic = NULL;
    }
    
    currentMusic = Mix_LoadMUS(filepath);
    if (currentMusic == NULL) {
        return -1;
    }
   
    if (Mix_FadeInMusic(currentMusic, loops, 500) < 0) {
        Mix_FreeMusic(currentMusic);
        currentMusic = NULL;
        return -1;
    }
    
    return 0;
}

void audioPauseMusic(void) {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }
}

void audioResumeMusic(void) {
    if (Mix_PausedMusic()) {
        Mix_ResumeMusic();
    }
}

void audioStopMusic(void) {
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }
}

void audioSetMusicVolume(int volume) {
    if (volume < 0) volume = 0;
    if (volume > 128) volume = 128;
    
    Mix_VolumeMusic(volume);
}

int audioIsMusicPlaying(void) {
    return Mix_PlayingMusic() && !Mix_PausedMusic();
}


int audioIsMusicPaused(void) {
    return Mix_PausedMusic();
}


int audioLoadSound(const char *filepath) {
    if (soundCount >= MAX_SOUNDS) {
        return -1;
    }
    
    Mix_Chunk *sound = Mix_LoadWAV(filepath);
    if (sound == NULL) {
        return -1;
    }
    
    sounds[soundCount] = sound;
    return soundCount++;
}

void audioPlaySound(int soundId, int volume) {
    if (soundId < 0 || soundId >= soundCount || sounds[soundId] == NULL) {
        return;
    }
    
    if (volume >= 0) {
        if (volume > 128) volume = 128;
        Mix_VolumeChunk(sounds[soundId], volume);
    }
    
    Mix_PlayChannel(-1, sounds[soundId], 0);
}

void audioSetSoundVolume(int volume) {
    if (volume < 0) volume = 0;
    if (volume > 128) volume = 128;
    
    for (int i = 0; i < soundCount; i++) {
        if (sounds[i] != NULL) {
            Mix_VolumeChunk(sounds[i], volume);
        }
    }
}
