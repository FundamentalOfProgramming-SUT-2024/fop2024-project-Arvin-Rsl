#ifndef SONG_H
#define SONG_H

////  library : Songs!  ////

// Arvin Rasulzadeh
// 403110422

#include <ncurses.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include <unistd.h>
void play_soundtrack(const char *);
void stop_soundtrack();
void choose_soundtrack(int);
void init_audio();

// Function to initialize SDL for audio playback
void init_audio(){
    if (SDL_Init(SDL_INIT_AUDIO) < 0){
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }
}

// Function to play a soundtrack
void play_soundtrack(const char *filename){
    Mix_Music *music = Mix_LoadMUS(filename);
    if (music == NULL) {
        fprintf(stderr, "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

    if (Mix_PlayMusic(music, -1) < 0){
        fprintf(stderr, "Failed to play music! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }
}

// Function to stop the soundtrack
void stop_soundtrack(){
    Mix_HaltMusic();
    Mix_CloseAudio();
    SDL_Quit();
}

// Example function where user selects the soundtrack
void choose_soundtrack(int choice){
    char *soundtracks[] = {
                           "/home/arvin_rsl/Desktop/FOP_Project/songs/Firerose-8-bitDungeon.mp3",  // Regular room song1
                           "/home/arvin_rsl/Desktop/FOP_Project/songs/GoleYakh.mp3",  // Regular room song2
                           "/home/arvin_rsl/Desktop/FOP_Project/songs/GTA.mp3",  // Regular room song3
                           "/home/arvin_rsl/Desktop/FOP_Project/songs/DungeonEmperorsTomb-IntoTheCrypt.mp3", // Enchant room 
                           "/home/arvin_rsl/Desktop/FOP_Project/songs/DarkestDungeon.mp3", // Nightmare room
                           "/home/arvin_rsl/Desktop/FOP_Project/songs/FinalFantasy7-VictoryFanfare.mp3"  // Victory song !
    };

    // Play the chosen soundtrack
    play_soundtrack(soundtracks[choice - 1]);
}

#endif