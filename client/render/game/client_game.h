#ifndef CLIENT_GAME_H
#define CLIENT_GAME_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <memory>
#include <map>
#include "client_game_state.h"
#include "mainwindow.h"
#include "renderer_config.h"
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
    MainWindow& windowQT;
    infoEndGameDTO_t infoEndGameDTO;
    uint32_t viewportWidth;
    uint32_t viewportHeight;

    //no tienen porque ser punteros cambiar!!!
    std::map<uint8_t, std::shared_ptr<ClientPlayer>> players;
    std::map<uint8_t, std::shared_ptr<ClientInfected>> infected;

    void updatePlayers(std::vector<player_t>& players);
    void updateInfected(std::vector<infected_t>& zombies);
    void cleanDead(void);
    std::string formatTime(int milliseconds);

    public:
    ClientGame(TextureManager& textureManager, 
                SoundManager& soundManager,
                MainWindow& windowQT);

    int updateGame(std::shared_ptr<gameStateDTO_t> newGame);
    void drawPlayers(SDL2pp::Renderer& renderer, int it);
    void drawInfected(SDL2pp::Renderer& renderer, int it);
    void drawGameTime(SDL2pp::Renderer& renderer, int gameTime);
    void drawEndGame(SDL2pp::Renderer& renderer);
    void updateSizeWindow(std::shared_ptr<ActionRender> action);
};

#endif