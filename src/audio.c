#include "audio.h"
#include <stdio.h>

// Global variable to track if audio is initialized
static int audioInitialized = 0;

int audio_init() {
    // Try different audio drivers and configurations for Windows compatibility
    
    // First attempt: Try with DirectSound driver (often more compatible on Windows)
    SDL_setenv("SDL_AUDIODRIVER", "directsound", 1);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) >= 0) {
        printf("Audio initialized with DirectSound driver\n");
        audioInitialized = 1;
        return 1;
    }
    
    // Second attempt: Try with WinMM driver (fallback for older systems)
    SDL_setenv("SDL_AUDIODRIVER", "winmm", 1);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) >= 0) {
        printf("Audio initialized with WinMM driver\n");
        audioInitialized = 1;
        return 1;
    }
    
    // Third attempt: Try with smaller buffer and different sample rate
    SDL_setenv("SDL_AUDIODRIVER", "directsound", 1);
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) >= 0) {
        printf("Audio initialized with reduced settings\n");
        audioInitialized = 1;
        return 1;
    }
    
    // Fourth attempt: Allow SDL to choose the driver
    SDL_setenv("SDL_AUDIODRIVER", "", 1);  // Clear driver preference
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) >= 0) {
        printf("Audio initialized with default driver\n");
        audioInitialized = 1;
        return 1;
    }
    
    // Final attempt: Minimal audio setup
    if (Mix_OpenAudio(22050, AUDIO_S16SYS, 1, 512) >= 0) {
        printf("Audio initialized with minimal settings (mono)\n");
        audioInitialized = 1;
        return 1;
    }
    
    // If all attempts fail, print error but continue without audio
    printf("WARNING: SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    printf("Continuing without audio...\n");
    audioInitialized = 0;
    return 0;  // Return 0 instead of -1 to indicate audio is disabled but game can continue
}

Mix_Chunk* audio_load_sound(const char* filename) {
    Mix_Chunk *sound = Mix_LoadWAV(filename);
    if (!sound) {
        printf("Failed to load sound effect filename = %s ! SDL_mixer Error: %s\n", filename, Mix_GetError());
        return NULL;
    }
    return sound;
}

void audio_play_sound(Mix_Chunk *sound) {
    if (sound != NULL) {  // Only play if sound is loaded
        Mix_PlayChannel(-1, sound, 0);
    }
}

void audio_free_sound(Mix_Chunk *sound) {
    if (sound != NULL) {  // Only free if sound is loaded
        Mix_FreeChunk(sound);
    }
}

void audio_cleanup(void) {
    if (audioInitialized) {
        Mix_CloseAudio();
        audioInitialized = 0;
    }
}