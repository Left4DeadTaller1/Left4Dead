#include "client_render.h"

ClientRenderer::ClientRenderer(Queue<std::string>& queueRenderGame, 
                    Queue<std::string>& queueRenderEvent, 
                    Window& window):
                    queueRenderGame(queueRenderGame),
                    queueRenderEvent(queueRenderEvent),
                    window(window) {}

void ClientRenderer::drawSoldier(Renderer& renderer, Texture& soldier, int textureWidth, int textureHeight){
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
}

void ClientRenderer::drawBackground(Renderer& renderer, Texture& background){
    renderer.Copy(background);
}

int ClientRenderer::render(){
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    renderer.Clear();

    Texture soldier1_walk(renderer, DATA_PATH "/client/resources/Soldier_1/Walk.png");
    Texture background1_war(renderer, DATA_PATH "/client/resources/backgrounds/War1/Bright/War.png");

    SDL_Texture* sdlTexture = soldier1_walk.Get();
    int textureWidth, textureHeight;
    SDL_QueryTexture(sdlTexture, NULL, NULL, &textureWidth, &textureHeight);

    ClientRenderer::drawBackground(renderer, background1_war);
    ClientRenderer::drawSoldier(renderer, soldier1_walk, textureWidth, textureHeight);

    renderer.Present();

	while (true) {
		SDL_Event event;
		while (SDL_WaitEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return 0;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: case SDLK_q:
					return 0;
				}
			}
		}
	}
	return 0;
}