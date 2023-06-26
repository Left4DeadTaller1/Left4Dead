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
#include "client_lifeBar.h"
#include "client_texture_manager.h"
#include "client_sound_manager.h"
#include "action_render.h"

class ClientGame {
    private:
    TextureManager& textureManager;
    SoundManager& soundManager;
    //no tienen porque ser punteros cambiar!!!
    std::map<uint8_t, std::shared_ptr<ClientPlayer>> players;
    std::map<uint8_t, std::shared_ptr<ClientInfected>> infected;
    std::map<uint8_t, std::shared_ptr<LifeBar>> barLife;

    void updatePlayers(std::vector<player_t>& players);

    void updateInfected(std::vector<infected_t>& zombies);

    void updateLifeBar(std::vector<player_t>& players_);

    void cleanDead(std::map<uint8_t, std::shared_ptr<ClientInfected>>& infected);

    public:
    ClientGame(TextureManager& textureManager, SoundManager& soundManager);

    void updateGame(std::shared_ptr<gameStateDTO_t> newGame);

    void drawPlayers(SDL2pp::Renderer& renderer, int it);

    void drawInfected(SDL2pp::Renderer& renderer, int it);

    void updateSizeWindow(std::shared_ptr<ActionRender> action);

};

#endif