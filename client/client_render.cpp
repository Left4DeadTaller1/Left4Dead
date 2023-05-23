#include "client_render.h"

ClientRenderer::ClientRenderer(Queue<Action*>& qServerToRender, 
                    Queue<Action*>& qEventsToRender, 
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
        Rect(textureWidth * (posX % 7), 0, textureWidth / 7, textureHeight),
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

    Texture soldier1_walk(renderer, DATA_PATH "/client/resources/Soldier_1/Walk.png");
    Texture background1_war(renderer, DATA_PATH "/client/resources/backgrounds/War1/Bright/War.png");

    SDL_Texture* sdlTexture = soldier1_walk.Get();
    int textureWidth, textureHeight;
    SDL_QueryTexture(sdlTexture, NULL, NULL, &textureWidth, &textureHeight);

    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    while(true){
        int newPosX = qServerToRender.pop();
        int newPosY = qServerToRender.pop();

        renderer.Clear();

        ClientRenderer::drawBackground(renderer, background1_war);
        ClientRenderer::drawSoldier(renderer, soldier1_walk, textureWidth, textureHeight, newPosX, newPosY);

        renderer.Present();
    }
	return 0;
}


/*void ClientRenderer::drawSoldier(Renderer& renderer, Texture& soldier, int textureWidth, int textureHeight){
    std::cout << "textureWidth: " << textureWidth << "\n";
    std::cout << "textureHeight: " << textureHeight << "\n";

    renderer.Copy(
        soldier,
        Rect(0, 0, textureWidth / 7, textureHeight),
        Rect(0, 600, 150, 150)
    );
    renderer.Copy(
        soldier,
        Rect((textureWidth / 7), 0, textureWidth / 7, textureHeight),
        Rect((textureWidth / 7), 600, 150, 150)
    );
    renderer.Copy(
        soldier,
        Rect((textureWidth / 7) * 2, 0, textureWidth / 7, textureHeight),
        Rect((textureWidth / 7) * 2, 600, 150, 150)
    );
    renderer.Copy(
        soldier,
        Rect((textureWidth / 7) * 3, 0, textureWidth / 7, textureHeight),
        Rect((textureWidth / 7) * 3, 600, 150, 150)
    );
    renderer.Copy(
        soldier,
        Rect((textureWidth / 7) * 4, 0, textureWidth / 7, textureHeight),
        Rect((textureWidth / 7) * 4, 600, 150, 150)
    );
    renderer.Copy(
        soldier,
        Rect((textureWidth / 7) * 5, 0, textureWidth / 7, textureHeight),
        Rect((textureWidth / 7) * 5, 600, 150, 150)
    );
    renderer.Copy(
        soldier,
        Rect((textureWidth / 7) * 6, 0, textureWidth / 7, textureHeight),
        Rect((textureWidth / 7) * 6, 600, 150, 150)
    );
}*/