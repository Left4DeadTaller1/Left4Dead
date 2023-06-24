#ifndef CLIENT_GAME_H
#define CLIENT_GAME_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <memory>
#include <map>
#include "client_game_state.h"
#include "client_player.h"
#include "client_infected.h"
#include "client_texture_manager.h"
#include "client_sound_manager.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_HEIGHT 150
#define GAME_WIDTH 1500

//entity
#define ENTITY_WIDTH WINDOW_WIDTH / 6
#define ENTITY_HEIGHT WINDOW_HEIGHT / 4
#define ENTITY_LOOKING_LEFT 0
#define ENTITY_LOOKING_RIGHT 1

//size viewport
#define IMAGE_BORDER_PADDING 40
#define VIEWPORT_X_INITIAL - IMAGE_BORDER_PADDING
#define VIEWPORT_WIDTH WINDOW_WIDTH + 2 * IMAGE_BORDER_PADDING
#define VIEWPORT_HEIGHT WINDOW_HEIGHT

//render life bar
#define LIFE_BAR_WIDTH 20
#define LIFE_BAR_HEIGHT 50
#define MAX_HEALTH 100
#define LIFE_LEVELS 10
#define DIST_X_LIFE_BAR_TO_ENTITY_LOOKING_LEFT 100
#define DIST_X_LIFE_BAR_TO_ENTITY_LOOKING_RIGHT 30
#define DIST_Y_LIFE_BAR_TO_ENTITY 30

class ClientGame {
    private:
    TextureManager& textureManager;
    SoundManager& soundManager;
    std::map<uint8_t, std::shared_ptr<ClientPlayer>> players;
    std::map<uint8_t, std::shared_ptr<ClientInfected>> infected;
    //barra de vida?

    void updatePlayers(std::vector<player_t>& players);

    void updateInfected(std::vector<infected_t>& zombies);

    public:
    ClientGame(TextureManager& textureManager, SoundManager& soundManager);

    void updateGame(std::shared_ptr<gameStateDTO_t> newGame);

    void drawPlayers(SDL2pp::Renderer& renderer, int it);

    void drawInfected(SDL2pp::Renderer& renderer, int it);

};

#endif