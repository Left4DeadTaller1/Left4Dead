#include "client_render.h"

using namespace SDL2pp;
#define MS_PER_FRAME 33
#define LOOPS_TO_ADVANCE_FRAME 5

ClientRenderer::ClientRenderer(std::atomic<bool>& isConnected,
                    Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender, 
                    Queue<std::shared_ptr<ActionRender>>& qEventsToRender, 
                    Window& window_, ClientProtocol& protocol, MainWindow& windowQT):
                    isConnected(isConnected),
                    qServerToRender(qServerToRender),
                    qEventsToRender(qEventsToRender),
                    protocol(protocol),
                    window(window_),
                    renderer(window_, -1, SDL_RENDERER_ACCELERATED),
                    textureManager(renderer),
                    soundManager(),
                    game(textureManager, soundManager, windowQT),
                    windowQT(windowQT){

    RendererConfig& config = RendererConfig::getInstance();
    std::map<std::string, int> dimensionsWindows = config.getDimensionsWindows();

    viewportXInicial = - dimensionsWindows["IMAGE_BORDER_PADDING"];
    viewportWidth = dimensionsWindows["WINDOW_WIDTH"] + 2 * dimensionsWindows["IMAGE_BORDER_PADDING"];
    viewportHeight = dimensionsWindows["WINDOW_HEIGHT"];
}

int ClientRenderer::handlerAction(std::shared_ptr<ActionRender> action){
    if (action->typeAction() == EXIT){
        isConnected = false;
        protocol.closeSocket();
        qServerToRender.close();
        return -1;
    }
    if (action->typeAction() == RESIZE){
        game.updateSizeWindow(action);
    }
    if (action->typeAction() == MUTE){
        soundManager.stopMusic();
    }
    if (action->typeAction() == UNMUTE){
        soundManager.playMusic();
    }
    return 0;
}

int ClientRenderer::looprender(void) {
    TTF_Init();

    soundManager.playMusic();
    TypeMap_t typeMap = windowQT.getTypeMap();
    GameTexture& textureMap = textureManager.getTexture(typeMap);
    renderer.Copy(textureMap.texture);

    uint32_t initialTime = SDL_GetTicks();
    uint32_t t1 = SDL_GetTicks();
    int counterFrame = 0;
    int rate = 1000 / MS_PER_FRAME;
    int it = 0;

    while (isConnected) {
        for (int i = 0; i < 10; i++){
            std::shared_ptr<ActionRender> action;
            qEventsToRender.try_pop(action);
            if (action){
                if (handlerAction(action) == -1){
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

                renderer.Copy(textureMap.texture);

                SDL_Rect viewport;
                viewport.x = viewportXInicial;
                viewport.y = 0;
                viewport.w = viewportWidth;
                viewport.h = viewportHeight;

                SDL_RenderSetViewport(renderer.Get(), &viewport);

                uint32_t currentTime = SDL_GetTicks();
                uint32_t gameTime = (currentTime - initialTime);
                game.drawGameTime(renderer, gameTime);

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
        if (counterFrame == LOOPS_TO_ADVANCE_FRAME){
            it++;
            counterFrame = 0;
        }
    }
    TTF_Quit();
    return 0;
}





