#include "client_render.h"

ClientRenderer::ClientRenderer(Queue<int>& qServerToRender, 
                    Queue<ActionClient*>& qEventsToRender, 
                    Window& window):
                    qServerToRender(qServerToRender),
                    qEventsToRender(qEventsToRender),
                    window(window),
                    posX(0),
                    posY(0){}

void ClientRenderer::drawSoldier(Renderer& renderer, Texture& soldier, 
                                int& textureWidth, int& textureHeight, 
                                int& newPosX, int& newPosY){

    renderer.Copy(
        soldier,
        Rect((textureWidth / 7 )* (posX % 7), 0, textureWidth / 7, textureHeight),
        Rect(newPosX, newPosY, 150, 150)
    );
    posX = newPosX;
    posY = newPosY;
}

void ClientRenderer::drawBackground(Renderer& renderer, Texture& background){
    renderer.Copy(background);
}

//el evento de cerrar la ventana que le llegue del event manager
int ClientRenderer::render(){
    std::cout << "entra al render\n";

    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    Texture soldier1_walk(renderer, DATA_PATH "/client/resources/Soldier_1/Walk.png");
    Texture background1_war(renderer, DATA_PATH "/client/resources/backgrounds/War1/Bright/War.png");

    SDL_Texture* sdlTexture = soldier1_walk.Get();
    int textureWidth, textureHeight;
    SDL_QueryTexture(sdlTexture, NULL, NULL, &textureWidth, &textureHeight);

    renderer.Clear();
    std::cout << "pasa clear\n";

    drawBackground(renderer, background1_war);
    drawSoldier(renderer, soldier1_walk, textureWidth, textureHeight, posX, posY);

    renderer.Present();
    std::cout << "pasa present\n";

    while(true){
        std::cout << "antes de popear en el render\n";
        int newPosX = qServerToRender.pop();
        int newPosY = qServerToRender.pop();
        std::cout << "despues de popear en el render\n";
        renderer.Clear();

        drawBackground(renderer, background1_war);
        drawSoldier(renderer, soldier1_walk, textureWidth, textureHeight, newPosX, newPosY);

        renderer.Present();
    }

	return 0;
}
