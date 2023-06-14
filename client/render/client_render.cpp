#include "client_render.h"

using namespace SDL2pp;
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_HEIGHT 150
#define GAME_WIDTH 1500
#define IMAGE_WIDTH 150
#define IMAGE_HEIGHT 150
#define IMAGE_BORDER_PADDING 40
#define MAX_HEALTH 100
#define LIFE_LEVELS 10

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
    srcRect.x = (texture.width / texture.n)* ((MAX_HEALTH - currentPlayer.health) / LIFE_LEVELS);
    srcRect.y = 0;
    srcRect.w = texture.width / texture.n;
    srcRect.h = texture.height;

    SDL_Rect dstRect;
    if (currentPlayer.lookingTo == 0) {
        dstRect.x = ((currentPlayer.x * WINDOW_WIDTH) / GAME_WIDTH) + 100;
    } else {
        dstRect.x = ((currentPlayer.x * WINDOW_WIDTH) / GAME_WIDTH) + 30;
    }
    dstRect.y = (WINDOW_HEIGHT - currentPlayer.y - GAME_HEIGHT) + 30;
    dstRect.w = 20;
    dstRect.h = 50;

    if (currentPlayer.lookingTo == 0) {
        SDL_RenderCopyEx(renderer.Get(), texture.texture.Get(), &srcRect, &dstRect, 0, nullptr, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_RenderCopyEx(renderer.Get(), texture.texture.Get(), &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
    }
}

void ClientRenderer::drawInfected(infected_t& previousPlayer, 
                                infected_t& currentPlayer){
    
    GameTexture& texture = textureManager.getTexture(currentPlayer.typeInfected, currentPlayer.state);

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
}

#define PI 3.14

void ClientRenderer::drawPlayer(player_t& previousPlayer, 
                                player_t& currentPlayer){

    renderLifeBar(currentPlayer);
    
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
}


void drawInfected(infected_t& previousInfected, 
            infected_t& currentInfected){
                return;
            }

void ClientRenderer::drawBackground(Texture& background){
    renderer.Copy(background);
}

void  ClientRenderer::drawPlayers(std::map<uint8_t, player_t>& players){
    for (auto &currentPlayer : players){
        std::map<uint8_t, player_t>::iterator iter = (previousGameStateDTO->players).find(currentPlayer.first);
        if (iter != previousGameStateDTO->players.end()) {
            drawPlayer(iter->second, currentPlayer.second);
        } else {
            drawPlayer(currentPlayer.second, currentPlayer.second);
        }
    }   
}

void  ClientRenderer::drawInfected(std::map<uint8_t, infected_t>& infected){
    for (auto &currentInfected : infected){
        std::map<uint8_t, infected_t>::iterator iter = (previousGameStateDTO->infected).find(currentInfected.first);
        if (iter != previousGameStateDTO->infected.end()) {
            drawInfected(iter->second, currentInfected.second);
        } else {
            drawInfected(currentInfected.second, currentInfected.second);
        }
    }
}

void  ClientRenderer::drawInicio(void) {
    renderer.Clear();
    drawBackground(textureManager.getBackgroundTexture("background-war1-pale-war").texture);
    renderer.Present();
}

int ClientRenderer::looprender(void){
    drawInicio();
    previousGameStateDTO = qServerToRender.pop();

    while(true){

        std::shared_ptr<gameStateDTO_t> gameStateDTO = qServerToRender.pop();

        /*for (auto &currentPlayer : gameStateDTO->players) {
            std::cout << "PLAYER\n";
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
        }*/
        /*for (auto &currentPlayer : gameStateDTO->infected) {
            std::cout << "ZOMBI\n";
            std::map<uint8_t, infected_t>::iterator iter = (previousGameStateDTO->infected).find(currentPlayer.first);
            if (iter != previousGameStateDTO->infected.end()) {
                std::cout << "idPlayer: " << (int)(currentPlayer.second.idInfected) << "\n";
                std::cout << "state: " << (int)(currentPlayer.second.state) << "\n";
                std::cout << "x: " << (int)(currentPlayer.second.x) << "\n";
                std::cout << "y: " << (int)(currentPlayer.second.y) << "\n";
                std::cout << "lookingTo: " << (int)(currentPlayer.second.lookingTo) << "\n";
                std::cout << "health: " << (int)(currentPlayer.second.health) << "\n";
                std::cout << "type: " << (int)(currentPlayer.second.typeInfected) << "\n";
            } else {
                std::cout << "no encontro al player\n";
            }
        }*/

        renderer.Clear();

        drawBackground(textureManager.getBackgroundTexture("background-war1-pale-war").texture);

        SDL_Rect viewport;
        viewport.x = -IMAGE_BORDER_PADDING;
        viewport.y = 0;
        viewport.w = WINDOW_WIDTH + IMAGE_BORDER_PADDING;
        viewport.h = WINDOW_HEIGHT;

        //SDL_RenderSetLogicalSize(renderer.Get(), viewport.w, viewport.h);
        SDL_RenderSetViewport(renderer.Get(), &viewport);

        drawPlayers(gameStateDTO->players);
        drawInfected(gameStateDTO->infected);

        renderer.Present();
        SDL_RenderSetLogicalSize(renderer.Get(), WINDOW_WIDTH, WINDOW_HEIGHT);
        SDL_RenderSetViewport(renderer.Get(), nullptr);

        previousGameStateDTO = gameStateDTO;
    }

	return 0;
}


