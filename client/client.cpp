#include "client.h"

Client::Client(const char* hostname, const char* servname) : socket(hostname, servname),
                                                             receivingThread(socket),
                                                             isConnected(true) {}

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
    // methods to connect to menu
    // una vez ya en partida llamas a processUserInput() y lanzas a receiver;
}

int Client::render(){
    // Initialize SDL library
	SDL sdl(SDL_INIT_VIDEO);

	// Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
	Window window("SDL2pp demo",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WIDTH_WINDOW, HEIGHT_WINDOW,
			SDL_WINDOW_RESIZABLE);

	// Create accelerated video renderer with default driver
	Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Load sprites image as a new texture
	Texture war(renderer, DATA_PATH "/resources/backgrounds/War1/Bright/war.png");

	// Clear screen
	renderer.Clear();

	// Render our image, stretching it to the whole window
	renderer.Copy(war);

	// Show rendered frame
	renderer.Present();

	// 5 second delay
	SDL_Delay(5000);

	// Here all resources are automatically released and library deinitialized
	return 0;
}

Client::~Client() {}