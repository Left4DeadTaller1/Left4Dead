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
            std::map<state_t, GameTexture>& textures = textureManager.getTextures(newInfected.typeInfected);
            std::map<state_t, std::shared_ptr<Sound>>& sounds = soundManager.getSounds(newInfected.typeInfected);
            std::shared_ptr<ClientInfected> newClientInfected = std::make_shared<ClientInfected>(textures,
                                                                            sounds,
                                                                            newInfected);
            infected.emplace(newInfected.idInfected, newClientInfected);
        }
    } 
}

void ClientGame::updateGame(std::shared_ptr<gameStateDTO_t> newGame){
    updatePlayers(newGame->players);
    updateInfected(newGame->infected);
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