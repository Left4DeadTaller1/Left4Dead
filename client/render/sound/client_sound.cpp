#include "client_sound.h"

using namespace SDL2pp;

Sound::Sound(const char* pathSound, int channel) : sound(nullptr), channel(channel) {
    sound = Mix_LoadWAV(pathSound);
    if (sound == nullptr) {
        //implem
    }
}

Sound::~Sound() {
    if (sound != nullptr){
        Mix_FreeChunk(sound);
    }
}

void Sound::play(int playMode) {
    channel = Mix_PlayChannel(-1, sound, playMode);
    if (channel == -1) {
        //implem
        return;
    }
}

void Sound::stop() {
    Mix_HaltChannel(channel);
}

