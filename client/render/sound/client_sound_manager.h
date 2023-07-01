#ifndef CLIENT_SOUND_MANAGER_H
#define CLIENT_SOUND_MANAGER_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <memory>
#include <map>
#include "client_game_state.h"
#include "client_sound.h"

class SoundManager {
    private:
    std::map<state_t, std::shared_ptr<Sound>> soundsSoldier;
    std::map<typeEntity_t, std::string> translationTypeEntity;
    std::shared_ptr<Sound> music;

    void loadSounds();

    public:
    SoundManager();
    std::map<state_t, std::shared_ptr<Sound>>& getSounds(typeEntity_t type);
    void playMusic(void);
    void stopMusic(void);
    ~SoundManager();
};

#endif