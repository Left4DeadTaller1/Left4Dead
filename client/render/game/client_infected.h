#ifndef CLIENT_INFECTED_H
#define CLIENT_INFECTED_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <memory>
#include <map>
#include "client_game_state.h"
#include "renderer_config.h"
#include "client_texture_manager.h"
#include "client_sound_manager.h"
#include "client_lifeBar.h"

class ClientInfected {
    private:
    state_t previousState;
    state_t currentState;
    int x;
    int y;
    int lookingTo;
    bool isDead;
    int counterDeath;
    LifeBar lifeBar;
    std::map<state_t, GameTexture>& texturesInfected;
    std::map<state_t, std::shared_ptr<Sound>>& sounds;

    uint32_t width;
    uint32_t height;
    uint32_t viewportWidth;
    uint32_t viewportHeight;
    uint32_t gameWidth;
    uint32_t gameHeight;

    GameTexture& getTextureInfected(state_t state);

    void playSound(state_t state, int playMode);

    void stopSound(state_t state);

    public:
    ClientInfected(std::map<state_t, GameTexture>& textures,
                    std::map<state_t, std::shared_ptr<Sound>>& sounds,
                    infected_t& currentInfected,
                    GameTexture& textureLifeBar);

    void draw(SDL2pp::Renderer& renderer, int it);

    bool isZombieDead(void);

    void updateInfected(infected_t& newCurrentInfected);

    void updateSizeWindow(uint32_t newWidth, uint32_t newHeight);
};

#endif