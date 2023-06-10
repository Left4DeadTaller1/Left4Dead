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

    GameTexture& texture = textureManager.getTexture(SOLDIER1, currentPlayer.state);
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
    std::cout << "entra al render\n";
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
                drawPlayer(iter->second, currentPlayer.second);
            } else {
                drawPlayer(currentPlayer.second, currentPlayer.second);
            }
        }
        for (auto &currentInfected : gameStateDTO->infected){
            std::map<uint8_t, infected_t>::iterator iter = (previousGameStateDTO->infected).find(currentInfected.first);
            if (iter != previousGameStateDTO->infected.end()) {
                //drawInfected(iter->second, currentInfected.second);
            } else {
                //drawInfected(currentInfected.second, currentInfected.second);
            }
        }
        renderer.Present();
        previousGameStateDTO = gameStateDTO;
    }

	return 0;
}

//void ClientRenderer::handlerMove(int speed)

    //en que casos voy a querer hacer algo diferente?? cuando es running, cuando en moving
    /*switch (currentPlayer->state) {
        case WALKING:
            break;
        case IDLE:
            break;
        case RUNNING:
            break;
        case RELOADING:
            break;
        case SHOOTING:
            break;
        case IDLE:
            break;
        case DEAD:
            break;
        case HURT:
            break;                   
    }*/

    /*SDL_Rect srcRect;
    srcRect.x = (texture->width / 7) * (previousPlayer->x % 7);
    srcRect.y = 0;
    srcRect.w = texture->width / 7;
    srcRect.h = texture->height;

    SDL_Rect dstRect;
    dstRect.x = currentPlayer->x;
    dstRect.y = currentPlayer->y;
    dstRect.w = 150;
    dstRect.h = 150;

    float angle = 45.0;  // Ángulo de rotación en grados

    SDL_RenderCopyEx(renderer, texture->texture, &srcRect, &dstRect, angle, nullptr, SDL_FLIP_NONE);*/
