#include "client_render.h"

using namespace SDL2pp;
#define MS_PER_FRAME 33

ClientRenderer::ClientRenderer(std::atomic<bool>& isConnected,
                    Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender, 
                    Queue<std::shared_ptr<ActionClient>>& qEventsToRender, 
                    Window& window_):
                    isConnected(isConnected),
                    qServerToRender(qServerToRender),
                    qEventsToRender(qEventsToRender),
                    window(window_),
                    renderer(window_, -1, SDL_RENDERER_ACCELERATED),
                    textureManager(renderer),
                    soundManager(),
                    game(textureManager, soundManager){}


void ClientRenderer::drawBackground(Texture& background){
    renderer.Copy(background);
}

void ClientRenderer::drawInicio(void) {
    renderer.Clear();
    drawBackground(textureManager.getBackgroundTexture("background-war1-pale-war").texture);
    renderer.Present();
}

int ClientRenderer::looprender(void) {
    drawInicio();

    uint32_t t1 = SDL_GetTicks();
    int counterFrame = 0;
    int rate = 1000 / 50;//MS_PER_FRAME;
    int it = 0;

    while (isConnected) {

        for (int i = 0; i < 10; i++){
            std::shared_ptr<ActionClient> action;
            qEventsToRender.try_pop(action);
            if (action){
                //procesar accion
                if (action->isExit()){
                    qServerToRender.close();
                    return 0;
                }
            }
        }

        for (int i = 0; i < 10; i++){
            std::shared_ptr<gameStateDTO_t> gameStateDTO;
            qServerToRender.try_pop(gameStateDTO);
            if (gameStateDTO){
                game.updateGame(gameStateDTO);
                renderer.Clear();

                drawBackground(textureManager.getBackgroundTexture("background-war1-pale-war").texture);

                SDL_Rect viewport;
                viewport.x = VIEWPORT_X_INITIAL;
                viewport.y = 0;
                viewport.w = VIEWPORT_WIDTH;
                viewport.h = VIEWPORT_HEIGHT;

                SDL_RenderSetViewport(renderer.Get(), &viewport);

                game.drawPlayers(renderer, it);
                game.drawInfected(renderer, it);

                renderer.Present();
                SDL_RenderSetViewport(renderer.Get(), nullptr);
            }
        }
        uint32_t t2 = SDL_GetTicks();
        int rest = rate - (t2 - t1);
        if (rest < 0) {
            int behind = -rest;
            int lost = behind - behind % rate;
            t1 += lost;
            it += int(lost / rate);
        } else {
            SDL_Delay(rest);
        }
        t1 += rate;

        counterFrame++;
        if (counterFrame == 5){
            it++;
            counterFrame = 0;
        }
    }

    return 0;
    std::cout << "SALE DEL RENDER\n";
}





