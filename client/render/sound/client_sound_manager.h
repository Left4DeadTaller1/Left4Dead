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
    std::map<std::string, std::shared_ptr<Sound>> sounds;
    std::map<typeEntity_t, std::string> translationTypeEntity;
    std::map<state_t, std::string> translationState;

    void loadSounds();

    void loadTranslations(void);

    public:
    SoundManager();

    void playSound(const std::string& nameSound, int playMode);

    void playSound(typeEntity_t typeEntity, state_t state, int playMode);

    void stopSound(typeEntity_t typeEntity, state_t state);

    ~SoundManager();
};

#endif