#include "client_game.h"

using namespace SDL2pp;

ClientGame::ClientGame(TextureManager& textureManager, 
                        SoundManager& soundManager,
                        MainWindow& windowQT):
                        textureManager(textureManager),
                        soundManager(soundManager),
                        windowQT(windowQT) {}  

void ClientGame::updatePlayers(std::vector<player_t>& players_){
    std::set<int> idsPlayers;
    for (auto &newPlayer : players_){
        std::map<uint8_t, std::shared_ptr<ClientPlayer>>::iterator iter = players.find(newPlayer.idPlayer);
        if (iter != players.end()) {
            (iter->second)->updatePlayer(newPlayer);
        } else {
            bool isMyWindow = false;
            if (newPlayer.nickname == windowQT.getNamePlayer()){
                isMyWindow = true;
            }
            std::map<state_t, GameTexture>& textures = textureManager.getTextures(SOLDIER1);
            std::map<TypeWeapon_t, GameTexture>& texturesWeapon = textureManager.getTexturesWeapon();
            std::map<state_t, std::shared_ptr<Sound>>& sounds = soundManager.getSounds(SOLDIER1);
            GameTexture& textureLifeBar = textureManager.getTextureLifeBar();
            std::shared_ptr<ClientPlayer> newClientPlayer = std::make_shared<ClientPlayer>(textures,
                                                                            sounds,
                                                                            texturesWeapon,
                                                                            isMyWindow,
                                                                            newPlayer,
                                                                            textureLifeBar);
            players.emplace(newPlayer.idPlayer, newClientPlayer);
        }
        idsPlayers.insert(newPlayer.idPlayer);
    }
    auto it = players.begin();
    while (it != players.end()) {
        int player_id = it->first;
        if (idsPlayers.find(player_id) == idsPlayers.end()) {
            it = players.erase(it);
        } else {
            ++it;
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
                GameTexture& textureLifeBar = textureManager.getTextureLifeBar();
                std::shared_ptr<ClientInfected> newClientInfected = std::make_shared<ClientInfected>(textures,
                                                                                sounds,
                                                                                newInfected,
                                                                                textureLifeBar);
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

void ClientGame::updateSizeWindow(std::shared_ptr<ActionRender> action){
    uint32_t newWidth = action->getParam1();
    uint32_t newHeight = action->getParam2();
    for (auto &player : players){
        (player.second)->updateSizeWindow(newWidth, newHeight);
    }
    for (auto &infec : infected){
        (infec.second)->updateSizeWindow(newWidth, newHeight);
    }
}

std::string ClientGame::formatTime(int milliseconds) {
    int seconds = milliseconds / 1000;
    int minutes = seconds / 60;
    int hours = minutes / 60;

    std::string time = std::to_string(hours) + ":" +
                                std::to_string(minutes % 60) + ":" +
                                std::to_string(seconds % 60);

    return time;
}

void ClientGame::drawGameTime(Renderer& renderer, int gameTime) {
    Font font(DATA_PATH "/client/render/resources/font/Roboto-MediumItalic.ttf", 24);

    std::string timeText = "Game Time: " + formatTime(gameTime);

    Surface textSurface(font.RenderText_Solid(timeText.c_str(), SDL_Color{ 0, 0, 0}));
    Texture textTexture(renderer, textSurface);

    Rect textRect(50, 10, textSurface.GetWidth(), textSurface.GetHeight());

    renderer.Copy(textTexture, NullOpt, textRect);
}
