#include "client_render.h"

using namespace SDL2pp;
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_HEIGHT 150
#define GAME_WIDTH 1500
#define IMAGE_WIDTH 150
#define IMAGE_HEIGHT 150

ClientRenderer::ClientRenderer(Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender, 
                    Queue<std::shared_ptr<ActionClient>>& qEventsToRender, 
                    Window& window_):
                    qServerToRender(qServerToRender),
                    qEventsToRender(qEventsToRender),
                    window(window_),
                    renderer(window_, -1, SDL_RENDERER_ACCELERATED),
                    textureManager(renderer),
                    previousGameStateDTO(NULL){}

void ClientRenderer::renderLifeBar(player_t& currentPlayer){
    GameTexture& texture = textureManager.getBackgroundTexture("barras-vida");

    SDL_Rect srcRect;
    srcRect.x = (texture.width / texture.n)* ((100 - currentPlayer.health) / 10);
    srcRect.y = 0;
    srcRect.w = texture.width / texture.n;
    srcRect.h = texture.height;

    SDL_Rect dstRect;
    dstRect.x = ((currentPlayer.x * WINDOW_WIDTH) / GAME_WIDTH) + 30;
    dstRect.y = (WINDOW_HEIGHT - currentPlayer.y - GAME_HEIGHT) + 30;
    dstRect.w = 20;
    dstRect.h = 50;

    SDL_RenderCopyEx(renderer.Get(), texture.texture.Get(), &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
}

#define PI 3.14

void ClientRenderer::drawPlayer(player_t& previousPlayer, 
                                player_t& currentPlayer){

    std::cout << "previousPlayer.x: " << (int)previousPlayer.x << "\n";
    std::cout << "previousPlayer.y: " << (int)previousPlayer.y << "\n";
    std::cout << "currentPlayer.x: " << (int)currentPlayer.x << "\n";
    std::cout << "currentPlayer.y: " << (int)currentPlayer.y << "\n";

    renderLifeBar(currentPlayer);

    float angle = atan2(currentPlayer.y - previousPlayer.y, currentPlayer.x - previousPlayer.x) * 180.0 / PI;
    
    GameTexture& texture = textureManager.getTexture(SOLDIER1, currentPlayer.state);

    SDL_Rect srcRect;
    srcRect.x = (texture.width / texture.n)* (previousPlayer.x % texture.n);
    srcRect.y = 0;
    srcRect.w = texture.width / texture.n;
    srcRect.h = texture.height;

    SDL_Rect dstRect;
    dstRect.x = (currentPlayer.x * WINDOW_WIDTH) / GAME_WIDTH;
    dstRect.y = WINDOW_HEIGHT - currentPlayer.y - GAME_HEIGHT;
    dstRect.w = IMAGE_WIDTH;
    dstRect.h = IMAGE_HEIGHT;

    if (currentPlayer.lookingTo == 0) {
        SDL_RenderCopyEx(renderer.Get(), texture.texture.Get(), &srcRect, &dstRect, 0, nullptr, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_RenderCopyEx(renderer.Get(), texture.texture.Get(), &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
    }
    //SDL_RenderCopyEx(renderer.Get(), texture.texture.Get(), &srcRect, &dstRect, angle, nullptr, SDL_FLIP_NONE);
}


void drawInfected(infected_t& previousInfected, 
            infected_t& currentInfected){
                return;
            }

void ClientRenderer::drawBackground(Texture& background){
    renderer.Copy(background);
}

int ClientRenderer::render(){
    renderer.Clear();

    drawBackground(textureManager.getBackgroundTexture("background-war1-pale-war").texture);

    renderer.Present();

    previousGameStateDTO = qServerToRender.pop();

    while(true){
        std::shared_ptr<gameStateDTO_t> gameStateDTO = qServerToRender.pop();

        std::cout << "amountEntities: " << (gameStateDTO->players).size() << "\n";
        for (auto &currentPlayer : gameStateDTO->players) {
            std::map<uint8_t, player_t>::iterator iter = (previousGameStateDTO->players).find(currentPlayer.first);
            if (iter != previousGameStateDTO->players.end()) {
                std::cout << "idPlayer: " << (int)(currentPlayer.second.idPlayer) << "\n";
                std::cout << "state: " << (int)(currentPlayer.second.state) << "\n";
                std::cout << "x: " << (int)(currentPlayer.second.x) << "\n";
                std::cout << "y: " << (int)(currentPlayer.second.y) << "\n";
                std::cout << "lookingTo: " << (int)(currentPlayer.second.lookingTo) << "\n";
                std::cout << "health: " << (int)(currentPlayer.second.health) << "\n";
            } else {
                std::cout << "no encontro al player\n";
            }
        }

        renderer.Clear();

        drawBackground(textureManager.getBackgroundTexture("background-war1-pale-war").texture);

        for (auto &currentPlayer : gameStateDTO->players){
            std::map<uint8_t, player_t>::iterator iter = (previousGameStateDTO->players).find(currentPlayer.first);
            if (iter != previousGameStateDTO->players.end()) {
                std::cout << "encontro al player\n";
                drawPlayer(iter->second, currentPlayer.second);
            } else {
                std::cout << "no encontro al player\n";
                drawPlayer(currentPlayer.second, currentPlayer.second);
            }
        }
        /*for (auto &currentInfected : gameStateDTO.infected){
            std::map<uint8_t, infected_t>::iterator iter = (previousGameStateDTO->infected).find(currentInfected.first);
            if (iter != previousGameStateDTO->infected.end()) {
                //drawInfected(iter.second, currentInfected.second);
            } else {
                //drawInfected(currentInfected.second, currentInfected.second);
            }
        }*/
        renderer.Present();
        previousGameStateDTO = gameStateDTO;
    }

	return 0;
}

