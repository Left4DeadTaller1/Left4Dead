#include "client_game.h"

ClientGame::ClientGame(TextureManager& textureManager, 
                        SoundManager& soundManager):
                        textureManager(textureManager),
                        soundManager(soundManager) {}  

    std::vector<player_t> players;
    std::vector<infected_t> infected;

void ClientGame::updatePlayers(std::vector<player_t>& players_){
    for (auto &newPlayer : players_){
        std::map<uint8_t, std::shared_ptr<ClientPlayer>>::iterator iter = players.find(newPlayer.idPlayer);
        if (iter != players.end()) {
            (iter->second)->updatePlayer(newPlayer);
        } else {
            std::map<state_t, GameTexture>& textures = textureManager.getTextures(SOLDIER1);
            std::map<state_t, std::shared_ptr<Sound>>& sounds = soundManager.getSounds(SOLDIER1);
            std::shared_ptr<ClientPlayer> newClientPlayer = std::make_shared<ClientPlayer>(textures,
                                                                            sounds,
                                                                            newPlayer);
            players.emplace(newPlayer.idPlayer, newClientPlayer);
        }
    }
}

void ClientGame::updateInfected(std::vector<infected_t>& zombies){
    for (auto &newInfected : zombies){
        std::map<uint8_t, std::shared_ptr<ClientInfected>>::iterator iter = infected.find(newInfected.idInfected);
        if (iter != infected.end()) {
            (iter->second)->updateInfected(newInfected);
        } else {
            if (newInfected.state != DEAD && newInfected.state != DYING){
                std::map<state_t, GameTexture>& textures = textureManager.getTextures(newInfected.typeInfected);
                std::map<state_t, std::shared_ptr<Sound>>& sounds = soundManager.getSounds(newInfected.typeInfected);
                std::shared_ptr<ClientInfected> newClientInfected = std::make_shared<ClientInfected>(textures,
                                                                                sounds,
                                                                                newInfected);
                infected.emplace(newInfected.idInfected, newClientInfected);
            }
        }
    }
    cleanDead(infected);
}

void ClientGame::cleanDead(std::map<uint8_t, std::shared_ptr<ClientInfected>>& infected) {
    for (auto it = infected.begin(); it != infected.end(); ) {
        if (it->second->isZombieDead()) {
            it = infected.erase(it);
        } else {
            ++it;
        }
    }
}

void ClientGame::updateLifeBar(std::vector<player_t>& players_){
    for (auto &newPlayer : players_){
        std::map<uint8_t, std::shared_ptr<LifeBar>>::iterator iter = barLife.find(newPlayer.idPlayer);
        if (iter != barLife.end()) {
            (iter->second)->updateLifeBar(newPlayer.health, newPlayer.x, 
                                        newPlayer.y, newPlayer.lookingTo);
        } else {
            GameTexture& texture = textureManager.getTexture("barras-vida");
            std::shared_ptr<LifeBar> newLifeBar = std::make_shared<LifeBar>(texture,
                                                                            newPlayer.health,
                                                                            newPlayer.x,
                                                                            newPlayer.y,
                                                                            newPlayer.lookingTo, 
                                                                            SOLDIER1);
            barLife.emplace(newPlayer.idPlayer, newLifeBar);
        }
    }
}


void ClientGame::updateGame(std::shared_ptr<gameStateDTO_t> newGame){
    updatePlayers(newGame->players);
    updateInfected(newGame->infected);
    updateLifeBar(newGame->players);
}

void ClientGame::drawPlayers(SDL2pp::Renderer& renderer, int it){                
    for (auto &player : players){
        (player.second)->draw(renderer, it);
    }
}

void ClientGame::drawInfected(SDL2pp::Renderer& renderer, int it){                
    for (auto &infec : infected){
        (infec.second)->draw(renderer, it);
    }
}

void ClientGame::updateSizeWindow(std::shared_ptr<ActionRender> action){
    uint32_t newWidth = action->getParam1();
    uint32_t newHeight = action->getParam2();
    for (auto &player : players){
        (player.second)->updateSizeWindow(newWidth, newHeight);
    }
    for (auto &infec : infected){
        (infec.second)->updateSizeWindow(newWidth, newHeight);
    }
    /*for (auto &lifeBar : lifeBar){
        (lifeBar.second)->updateSizeWindow(newWidth, newHeight);
    }*/
}