#include "client_render.h"

using namespace SDL2pp;

ClientRenderer::ClientRenderer(Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender, 
                    Queue<std::shared_ptr<ActionClient>>& qEventsToRender, 
                    Window& window_):
                    qServerToRender(qServerToRender),
                    qEventsToRender(qEventsToRender),
                    window(window_),
                    renderer(window_, -1, SDL_RENDERER_ACCELERATED),
                    textureManager(renderer),
                    previousGameStateDTO(NULL){}

void ClientRenderer::drawPlayer(player_t& previousPlayer, 
                                player_t& currentPlayer){
    
    std::cout << "previousPlayer.x: " << (int)previousPlayer.x << "\n";
    std::cout << "currentPlayer.x: " << (int)previousPlayer.x << "\n";
    std::cout << "currentPlayer.y: " << (int)previousPlayer.x << "\n";

    //ver de tener los mismo state para no tener problemas 
    GameTexture& texture = textureManager.getTexture(SOLDIER1, currentPlayer.state);

    std::cout << "texture.width: " << (int)texture.width << "\n";
    std::cout << "texture.height: " << (int)texture.height << "\n";
    std::cout << "texture.n: " << (int)texture.n << "\n";

    renderer.Copy(
        texture.texture,
        Rect((texture.width / texture.n)* (previousPlayer.x % texture.n), 0, 
            texture.width / texture.n, texture.height),
        Rect(currentPlayer.x, currentPlayer.y, 150, 150)
    );

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

/*

#define PI 3.14

void ClientRenderer::drawPlayer(player_t& previousPlayer, 
                                player_t& currentPlayer){
    
    //ver de tener los mismo state para no tener problemas 
    GameTexture& texture = textureManager.getTexture(SOLDIER1, currentPlayer.state);

    SDL_Rect srcRect;
    srcRect.x = (texture.width / texture.n) * (previousPlayer.x % texture.n);
    srcRect.y = 0;
    srcRect.w = texture.width / texture.n;
    srcRect.h = texture.height;

    SDL_Rect dstRect;
    dstRect.x = currentPlayer.x;
    dstRect.y = currentPlayer.y;
    dstRect.w = 150;
    dstRect.h = 150;

    float angle = atan2(currentPlayer.y - previousPlayer.y, currentPlayer.x - previousPlayer.x) * 180.0 / PI;

    SDL_RenderCopyEx(renderer, texture.texture, &srcRect, &dstRect, angle, nullptr, SDL_FLIP_NONE);
}

*/
