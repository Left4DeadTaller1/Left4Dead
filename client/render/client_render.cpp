#include "client_render.h"

using namespace SDL2pp;
#define MS_PER_FRAME 33

ClientRenderer::ClientRenderer(Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender, 
                    Queue<std::shared_ptr<ActionClient>>& qEventsToRender, 
                    Window& window_):
                    qServerToRender(qServerToRender),
                    qEventsToRender(qEventsToRender),
                    window(window_),
                    renderer(window_, -1, SDL_RENDERER_ACCELERATED),
                    textureManager(renderer),
                    soundManager(),
                    previousGameStateDTO(NULL){}

void ClientRenderer::copySprite(Texture& texture, Rect& srcRect, Rect& dstRect, int lookingTo){
    if (lookingTo == ENTITY_LOOKING_LEFT) {
        SDL_RenderCopyEx(renderer.Get(), texture.Get(), &srcRect, &dstRect, 0, nullptr, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_RenderCopyEx(renderer.Get(), texture.Get(), &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
    }
}

void ClientRenderer::renderLifeBar(player_t& currentPlayer){
    GameTexture& texture = textureManager.getBackgroundTexture("barras-vida");

    SDL_Rect srcRect;
    srcRect.x = (texture.width / texture.n)* ((MAX_HEALTH - currentPlayer.health) / LIFE_LEVELS);
    srcRect.y = 0;
    srcRect.w = texture.width / texture.n;
    srcRect.h = texture.height;

    SDL_Rect dstRect;
    if (currentPlayer.lookingTo == 0) {
        dstRect.x = ((currentPlayer.x * VIEWPORT_WIDTH) / GAME_WIDTH)   \
                            + DIST_X_LIFE_BAR_TO_ENTITY_LOOKING_LEFT;
    } else {
        dstRect.x = ((currentPlayer.x * VIEWPORT_WIDTH) / GAME_WIDTH)   \
                            + DIST_X_LIFE_BAR_TO_ENTITY_LOOKING_RIGHT;
    }
    dstRect.y = (VIEWPORT_HEIGHT - currentPlayer.y - GAME_HEIGHT) + DIST_Y_LIFE_BAR_TO_ENTITY;
    dstRect.w = LIFE_BAR_WIDTH;
    dstRect.h = LIFE_BAR_HEIGHT;

    //copySprite(texture.texture, srcRect, dstRect, currentPlayer.lookingTo);
}

void ClientRenderer::drawInfected(infected_t& previousInfected, 
                                infected_t& currentInfected){
    
    GameTexture& texture = textureManager.getTexture(currentInfected.typeInfected, 
                                                        currentInfected.state);

    Rect srcRect((texture.width / texture.n)* (previousInfected.x % texture.n),
                0,
                texture.width / texture.n, 
                texture.height);

    Rect dstRect((currentInfected.x * VIEWPORT_WIDTH) / GAME_WIDTH,
                VIEWPORT_HEIGHT - currentInfected.y - GAME_HEIGHT,
                ENTITY_WIDTH, 
                ENTITY_HEIGHT);

    copySprite(texture.texture, srcRect, dstRect, currentInfected.lookingTo);
}

void ClientRenderer::drawPlayer(player_t& previousPlayer, 
                                player_t& currentPlayer){
    
    GameTexture& texture = textureManager.getTexture(SOLDIER1, currentPlayer.state);

    Rect srcRect((texture.width / texture.n)* (previousPlayer.x % texture.n),
                0,
                texture.width / texture.n, 
                texture.height);

    Rect dstRect((currentPlayer.x * VIEWPORT_WIDTH) / GAME_WIDTH,
                VIEWPORT_HEIGHT - currentPlayer.y - GAME_HEIGHT,
                ENTITY_WIDTH, 
                ENTITY_HEIGHT);

    copySprite(texture.texture, srcRect, dstRect, currentPlayer.lookingTo);
    if (currentPlayer.state != previousPlayer.state && currentPlayer.state != IDLE){     //y si soy yoelse {
        soundManager.playSound(SOLDIER1, currentPlayer.state, -1);
    }
    if (currentPlayer.state != previousPlayer.state){
        soundManager.stopSound(SOLDIER1, previousPlayer.state);
    }
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

void ClientRenderer::drawInicio(void) {
    renderer.Clear();
    drawBackground(textureManager.getBackgroundTexture("background-war1-pale-war").texture);
    renderer.Present();
}

int ClientRenderer::looprender(void) {
    drawInicio();
    previousGameStateDTO = qServerToRender.pop();

    while (true) {
        auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < 10; i++){
            std::shared_ptr<ActionClient> action;
            qEventsToRender.try_pop(action);
            if (action){
                //procesar accion
                if (action->isExit()){
                    return 0;
                }
            }
        }

        for (int i = 0; i < 10; i++){
            std::shared_ptr<gameStateDTO_t> gameStateDTO;
            qServerToRender.try_pop(gameStateDTO);
            if (gameStateDTO){
                for (auto &currentPlayer : gameStateDTO->players) {
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
                    }
                for (auto &currentPlayer : gameStateDTO->infected) {
                    std::cout << "ZOMBI\n";
                    std::map<uint8_t, infected_t>::iterator iter = (previousGameStateDTO->infected).find(currentPlayer.first);
                    if (iter != previousGameStateDTO->infected.end()) {
                        std::cout << "idZombi: " << (int)(currentPlayer.second.idInfected) << "\n";
                        std::cout << "state: " << (int)(currentPlayer.second.state) << "\n";
                        std::cout << "x: " << (int)(currentPlayer.second.x) << "\n";
                        std::cout << "y: " << (int)(currentPlayer.second.y) << "\n";
                        std::cout << "lookingTo: " << (int)(currentPlayer.second.lookingTo) << "\n";
                        std::cout << "health: " << (int)(currentPlayer.second.health) << "\n";
                        std::cout << "type: " << (int)(currentPlayer.second.typeInfected) << "\n";
                    } else {
                        std::cout << "no encontro al player\n";
                    }
                }
                renderer.Clear();

                drawBackground(textureManager.getBackgroundTexture("background-war1-pale-war").texture);

                SDL_Rect viewport;
                viewport.x = VIEWPORT_X_INITIAL;
                viewport.y = 0;
                viewport.w = VIEWPORT_WIDTH;
                viewport.h = VIEWPORT_HEIGHT;

                SDL_RenderSetViewport(renderer.Get(), &viewport);

                drawPlayers(gameStateDTO->players);
                drawInfected(gameStateDTO->infected);

                renderer.Present();
                SDL_RenderSetViewport(renderer.Get(), nullptr);

                previousGameStateDTO = gameStateDTO;
            }
        }

        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (elapsed.count() < MS_PER_FRAME) {
            std::this_thread::sleep_for(std::chrono::milliseconds(MS_PER_FRAME) - elapsed);
        }
    }

    return 0;
}




