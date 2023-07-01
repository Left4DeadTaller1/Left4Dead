#include "client_game.h"

using namespace SDL2pp;

ClientGame::ClientGame(TextureManager& textureManager, 
                        SoundManager& soundManager,
                        MainWindow& windowQT):
                        textureManager(textureManager),
                        soundManager(soundManager),
                        windowQT(windowQT) {
    RendererConfig& config = RendererConfig::getInstance();
    std::map<std::string, int>& dimensionsWindows = config.getDimensionsWindows();

    viewportWidth = dimensionsWindows["WINDOW_WIDTH"] + 2 * dimensionsWindows["IMAGE_BORDER_PADDING"];
    viewportHeight = dimensionsWindows["WINDOW_HEIGHT"];
}  

void ClientGame::updatePlayers(std::vector<player_t>& players_){
    std::set<int> idsPlayers;
    for (auto &newPlayer : players_){
        std::map<uint8_t, ClientPlayer>::iterator iter = players.find(newPlayer.idPlayer);
        if (iter != players.end()) {
            (iter->second).updatePlayer(newPlayer);
        } else {
            bool isMyWindow = false;
            if (newPlayer.nickname == windowQT.getNamePlayer()){
                isMyWindow = true;
            }
            std::map<state_t, GameTexture>& textures = textureManager.getTextures(newPlayer.typePlayer);
            std::map<TypeWeapon_t, GameTexture>& texturesWeapon = textureManager.getTexturesWeapon();
            std::map<state_t, std::shared_ptr<Sound>>& sounds = soundManager.getSounds(SOLDIER1);
            GameTexture& textureLifeBar = textureManager.getTextureLifeBar();
            players.emplace(newPlayer.idPlayer, ClientPlayer(textures,
                                                            sounds,
                                                            texturesWeapon,
                                                            isMyWindow,
                                                            newPlayer,
                                                            textureLifeBar));
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
        std::map<uint8_t, ClientInfected>::iterator iter = infected.find(newInfected.idInfected);
        if (iter != infected.end()) {
            (iter->second).updateInfected(newInfected);
        } else {
            if (newInfected.state != DEAD && newInfected.state != DYING){
                std::map<state_t, GameTexture>& textures = textureManager.getTextures(newInfected.typeInfected);
                std::map<state_t, std::shared_ptr<Sound>>& sounds = soundManager.getSounds(newInfected.typeInfected);
                GameTexture& textureLifeBar = textureManager.getTextureLifeBar();
                infected.emplace(newInfected.idInfected, ClientInfected(textures,
                                                                        sounds,
                                                                        newInfected,
                                                                        textureLifeBar));
            }
        }
    }
}

void ClientGame::cleanDead(void) {
    for (auto it = infected.begin(); it != infected.end(); ) {
        if ((it->second).isZombieDead()) {
            it = infected.erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = players.begin(); it != players.end(); ) {
        if ((it->second).isPlayerDead()) {
            it = players.erase(it);
        } else {
            ++it;
        }
    }
}


void ClientGame::drawEndGame(SDL2pp::Renderer& renderer){
    Font font(DATA_PATH "/client/render/resources/font/Roboto-MediumItalic.ttf", 24);

    GameTexture& papiro = textureManager.getTexture("papiro");
    GameTexture& gameOver = textureManager.getTexture("game over");

    Rect dstRect1(viewportWidth / 4,
        viewportHeight / 4,
        viewportWidth / 2, 
        viewportHeight / 2);

    SDL_RenderCopyEx(renderer.Get(), papiro.texture.Get(), nullptr, &dstRect1, 0, nullptr, SDL_FLIP_NONE);

    Rect dstRect2((3 / 8) * viewportWidth,
    (3 / 8) * viewportHeight,
    (1 / 8) * viewportWidth, 
    (1 / 8) * viewportHeight);

    SDL_RenderCopyEx(renderer.Get(), gameOver.texture.Get(), nullptr, &dstRect2, 0, nullptr, SDL_FLIP_NONE);

    std::string timeText = "Game Time: " + formatTime(infoEndGameDTO.gameTime);
    Surface textSurface1(font.RenderText_Solid(timeText.c_str(), SDL_Color{ 0, 0, 0}));
    Texture textTexture1(renderer, textSurface1);
    Rect textRect1(((float)3 / 8) * viewportWidth, ((float)4 / 8) * viewportHeight, textSurface1.GetWidth(), textSurface1.GetHeight());
    renderer.Copy(textTexture1, NullOpt, textRect1);

    std::string zombiesText = "Number Of Zombies Killed: " + std::to_string(infoEndGameDTO.numberOfZombiesKilled);
    Surface textSurface2(font.RenderText_Solid(zombiesText.c_str(), SDL_Color{ 0, 0, 0}));
    Texture textTexture2(renderer, textSurface2);
    Rect textRect2(((float)3 / 8) * viewportWidth, ((float)4 / 8) * viewportHeight + 30, textSurface2.GetWidth(), textSurface2.GetHeight());
    renderer.Copy(textTexture2, NullOpt, textRect2);    
}

int ClientGame::updateGame(std::shared_ptr<gameStateDTO_t> newGame){
    cleanDead();
    if (newGame->endGame == false){
        updatePlayers(newGame->players);
        updateInfected(newGame->infected);
        return 0;
    }
    infoEndGameDTO = newGame->infoEndGameDTO;
    return 1;
}

void ClientGame::drawPlayers(SDL2pp::Renderer& renderer, int it){                
    for (auto &player : players){
        (player.second).draw(renderer, it);
    }
}

void ClientGame::drawInfected(SDL2pp::Renderer& renderer, int it){                
    for (auto &infec : infected){
        (infec.second).draw(renderer, it);
    }
}

void ClientGame::updateSizeWindow(std::shared_ptr<ActionRender> action){
    uint32_t newWidth = action->getParam1();
    uint32_t newHeight = action->getParam2();
    for (auto &player : players){
        (player.second).updateSizeWindow(newWidth, newHeight);
    }
    for (auto &infec : infected){
        (infec.second).updateSizeWindow(newWidth, newHeight);
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
