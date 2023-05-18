#include <iostream>
#include <exception>

#include <SDL2pp/SDL2pp.hh>

#define WIDTH_WINDOW 800
#define HEIGHT_WINDOW 600

using namespace SDL2pp;

int main() try {
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
	Texture sky(renderer, DATA_PATH "/resources/backgrounds/War1/Bright/sky.png");
	Texture sun(renderer, DATA_PATH "/resources/backgrounds/War1/Bright/sun.png");
	Texture ruins(renderer, DATA_PATH "/resources/backgrounds/War1/Bright/ruins.png");
	Texture road(renderer, DATA_PATH "/resources/backgrounds/War1/Bright/road.png");
	Texture houses1(renderer, DATA_PATH "/resources/backgrounds/War1/Bright/houses1.png");

	// Clear screen
	renderer.Clear();

	// Render our image, stretching it to the whole window
	renderer.Copy(sky);
	renderer.Copy(sun);
	renderer.Copy(ruins);
	renderer.Copy(road);
	renderer.Copy(houses1);

	// Show rendered frame
	renderer.Present();

	// 5 second delay
	SDL_Delay(5000);

	// Here all resources are automatically released and library deinitialized
	return 0;
} catch (std::exception& e) {
	// If case of error, print it and exit with error
	std::cerr << e.what() << std::endl;
	return 1;
}