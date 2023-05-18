#include "client_event_manager.h"
#include <iostream>
#include <exception>

#include <SDL2pp/SDL2pp.hh>

EventManager::EventManager(Queue<std::string>& queue_sender, Queue<std::string>& queue_render):
    queue_sender(queue_sender), queue_render(queue_render) {}

using namespace SDL2pp;

void EventManager::run() { try {
	while (true) {
		SDL_Event event;
		while (SDL_WaitEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: case SDLK_q:
					return;
				case SDLK_RIGHT: 
				std::cout << "entra a apreto flecha para la derecha\n";
				}
			} else if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
				case SDLK_RIGHT: 
				std::cout << "entra a solto flecha para la derecha\n";
				}
			}
		}
		SDL_Delay(1);
	}
    } catch (const std::exception& e) {
        std::cerr << "An exception occurred in Acceptor::run(): " << e.what() << std::endl;
    } catch (...) {
        // unknown exception
        std::cerr << "An unknown exception occurred in Acceptor::run()" << std::endl;
    }
}








