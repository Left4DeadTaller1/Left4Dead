/*#ifndef CLIENT_PLAYER_H
#define CLIENT_PLAYER_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <memory>
#include <map>
#include "client_game_state.h"
#include "../client_render.h"

class ClientPlayer {
    private:
    player_t& previousPlayer;
    player_t& currentPlayer;
    TextureManager& textureManager;

    public:
    ClientPlayer(TextureManager& textureManager);

    void draw(SDL2pp::Renderer& renderer);

    void updatePlayer(player_t& newCurrentPlayer);

    ~ClientPlayer();
};

#endif*/