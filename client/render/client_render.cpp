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

std::string traducir(int state){
    if (state == WALKING){
        return "walk";
    }
    if (state == RUNNING){
        return "run";
    }
    if (state == IDLE){
        return "idle";
    }
    if (state == DEAD){
        return "DEADDDDDDDDDD";
    } 
    if (state == DYING){
        return "DYINGGGG";
    } 
    if (state == HURT){
        return "hurt";
    }
    if (state == RELOADING){
        return "reloading";
    }
    if (state == SHOOTING){
        return "shooting";
    }
    if (state == ATTACK){
        return "attack";
    }
    if (state == JUMP){
        return "jump";
    }
    if (state == SCREAM){
        return "scream";
    }else {
        std::cout << "OTRO - state: " << state << "\n";
        return "otro";
    }
}

std::string traducirType(int typeInfected){
    if (typeInfected == SOLDIER1){
        return "soldier1";
    }
    if (typeInfected == JUMPER){
        return "jumper";
    }
    if (typeInfected == VENOM){
        return "venom";
    }
    if (typeInfected == WITCH){
        return "witch";
    }
    if (typeInfected == ZOMBIE){
        return "zombie";
    }else {
        return "TIPO NO IDENTIFICADO";
    }
}

int ClientRenderer::handlerAction(std::shared_ptr<ActionRender> action){
    if (action->typeAction() == EXIT){
        std::cout << "ENTRA A SALIR DEL RENDER\n";
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
    std::cout << "TYPE MAP: " << (int)typeMap << "\n";
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
                //std::cout << "se popea accion\n";
                std::cout << action->typeAction() << "\n";
                if (handlerAction(action) == -1){
                    return 0;
                }              
            }
        }

        for (int i = 0; i < 10; i++){
            std::shared_ptr<gameStateDTO_t> gameStateDTO;
            qServerToRender.try_pop(gameStateDTO);
            if (gameStateDTO){
                /*for (auto &currentPlayer : gameStateDTO->players) {
                    std::cout << "type: " << "soldier1" << "\n";
                    std::cout << "idPlayer: " << (int)(currentPlayer.idPlayer) << "\n";
                    std::cout << "state: " << traducir((int)(currentPlayer.state)) << "\n";
                    std::cout << "x: " << (int)(currentPlayer.x) << "\n";
                    std::cout << "y: " << (int)(currentPlayer.y) << "\n";
                    std::cout << "health: " << (int)(currentPlayer.health) << "\n";
                }

                for (auto &currentPlayer : gameStateDTO->infected) {
                    std::cout << "type: " << traducirType((int)(currentPlayer.typeInfected)) << "\n";
                    std::cout << "idZombi: " << currentPlayer.idInfected << "\n";
                    std::cout << "state: " << traducir((int)(currentPlayer.state)) << "\n";
                    std::cout << "x: " << (int)(currentPlayer.x) << "\n";
                    std::cout << "y: " << (int)(currentPlayer.y) << "\n";
                    std::cout << "health: " << (int)(currentPlayer.health) << "\n";
                }*/
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
                game.drawLifeBar(renderer);

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





