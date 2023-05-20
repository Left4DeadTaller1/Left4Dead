#include "client.h"

Client::Client(const char* hostname, const char* servname, Window& window) : 
                                                            /*socket(hostname, servname),
                                                             receivingThread(socket),*/
                                                             isConnected(true),
                                                             queue_sender(TAM_MAX_QUEUE),
                                                             queue_render(TAM_MAX_QUEUE),
                                                             window(window),
                                                             eventManager(queue_sender, queue_render, window){}

void Client::processUserInput() {
    // event instancia

    while (isConnected) {
        // identificar que tipo de evento es (moverse derecha o ize, etc)

        bool was_closed = false;
        try {
            while (!was_closed) {
                // swith(tipo de evento):
                //  case moverse para arriba:
                //  send moverse para arriba
            }
        }

        catch (const LibError& e) {
            // supongo que esto no hace falta realmente porque si hubo un liberror
            // el while se interrumpio pero bueno no esta de mas
            was_closed = true;
        }
    }
}

void Client::run() {

    eventManager.start();
    render(window);
    std::cout << "pasa start\n";
    // methods to connect to menu
    // una vez ya en partida llamas a processUserInput() y lanzas a receiver;
}

void Client::DrawSoldier(Renderer& renderer, Texture& soldier, int textureWidth, int textureHeight){
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

void Client::DrawBackground(Renderer& renderer, Texture& background){
    renderer.Copy(background);
}

int Client::render(Window& window){
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    renderer.Clear();

    Texture soldier1_walk(renderer, DATA_PATH "/client/resources/Soldier_1/Walk.png");
    Texture background1_war(renderer, DATA_PATH "/client/resources/backgrounds/War1/Bright/War.png");

    SDL_Texture* sdlTexture = soldier1_walk.Get();
    int textureWidth, textureHeight;
    SDL_QueryTexture(sdlTexture, NULL, NULL, &textureWidth, &textureHeight);

    Client::DrawBackground(renderer, background1_war);
    Client::DrawSoldier(renderer, soldier1_walk, textureWidth, textureHeight);

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

Client::~Client() {
    eventManager.join();
}
