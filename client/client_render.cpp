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

void ClientRenderer::drawPlayer(std::shared_ptr<entity_t> previousPlayer, 
                                std::shared_ptr<entity_t> currentPlayer){

    std::shared_ptr<GameTexture> texture;
    switch (currentPlayer->state) {
        case WALKING:
            //definir direccion en base a previousPlayer->x y currentPlayer->x
            texture = textureManager.getTexture("soldier1-walk");
            //despues definir para cada textura en cuanto se divide cada una
            renderer.Copy(
                texture->texture,
                Rect((texture->width / 7 )* (previousPlayer->x % 7), 0, texture->width / 7, texture->height),
                Rect(currentPlayer->x, currentPlayer->y, 150, 150)
            );
            break;
        case IDLE:
            texture = textureManager.getTexture("soldier1-idle");
            renderer.Copy(
                texture->texture,
                Rect((texture->width / 7 )* (previousPlayer->x % 7), 0, texture->width / 7, texture->height),
                Rect(currentPlayer->x, currentPlayer->y, 150, 150)
            );
            break;
        /*case RUNNING:
            std::shared_ptr<GameTexture> texture = textureManager.getTexture("soldier1-run");
            break;
        case RELOADING:
            std::shared_ptr<GameTexture> texture = textureManager.getTexture("soldier1-recharge");
            break;
        case SHOOTING:
            std::shared_ptr<GameTexture> texture = textureManager.getTexture("soldier1-shot1");
            break;
        case IDLE:
            std::shared_ptr<GameTexture> texture = textureManager.getTexture("soldier1-idle");
            break;
        case DEAD:
            std::shared_ptr<GameTexture> texture = textureManager.getTexture("soldier1-dead");
            break;
        case HURT:
            std::shared_ptr<GameTexture> texture = textureManager.getTexture("soldier1-hurt");
            break;*/                    
    }
}

void ClientRenderer::drawBackground(Texture& background){
    renderer.Copy(background);
}


std::shared_ptr<entity_t> ClientRenderer::findPlayer(int idPlayer){
    for (auto &player : *(previousGameStateDTO->entities)){
        if(player->idEntity == idPlayer){
            return player;
        }
    }
}

int ClientRenderer::render(){
    renderer.Clear();

    drawBackground(textureManager.getTexture("background-war1-pale-war")->texture);

    renderer.Present();

    previousGameStateDTO = qServerToRender.pop();

    while(true){
        std::shared_ptr<gameStateDTO_t> gameStateDTO = qServerToRender.pop();
        renderer.Clear();

        drawBackground(textureManager.getTexture("background-war1-pale-war")->texture);

        for (auto &currentPlayer : *(gameStateDTO->entities)){
            std::shared_ptr<entity_t> previousPlayer = findPlayer(currentPlayer->idEntity); //despues tener un map, para no tener find
            drawPlayer(previousPlayer, currentPlayer);
        }
        renderer.Present();
        previousGameStateDTO = gameStateDTO;
    }

	return 0;
}
