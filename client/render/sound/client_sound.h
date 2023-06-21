#ifndef CLIENT_SOUND_H
#define CLIENT_SOUND_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <memory>
#include <map>
#include "client_game_state.h"

class Sound {
    private:
    Mix_Chunk* sound;
    int channel;

    public:
    Sound(const char* pathSound, int channel);

    void play(int playMode);

    void stop();

    ~Sound();
};

#endif