#ifndef CLIENT_PLAYER_H
#define CLIENT_PLAYER_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <memory>
#include <map>
#include "client_game_state.h"
#include "renderer_config.h"
#include "client_texture_manager.h"
#include "client_sound_manager.h"

#define ENTITY_LOOKING_LEFT 0
#define ENTITY_LOOKING_RIGHT 1

class ClientPlayer {
    private:
    state_t previousState;
    state_t currentState;
    int x;
    int y;
    int lookingTo;
    bool comingEndDeath;
    std::map<state_t, GameTexture>& texturesPlayer;
    std::map<state_t, std::shared_ptr<Sound>>& sounds;

    uint32_t width;
    uint32_t height;
    uint32_t viewportWidth;
    uint32_t viewportHeight;
    uint32_t gameWidth;
    uint32_t gameHeight;

    GameTexture& getTexturePlayer(state_t state);

    void playSound(state_t state, int playMode);

    void stopSound(state_t state);

    public:
    ClientPlayer(std::map<state_t, GameTexture>& textures,
                    std::map<state_t, std::shared_ptr<Sound>>& sounds,
                    player_t& currentPlayer);

    void draw(SDL2pp::Renderer& renderer, int it);

    void updatePlayer(player_t& newCurrentPlayer);
};

#endif