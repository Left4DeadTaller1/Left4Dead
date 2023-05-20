#include "client_event_manager.h"
#include <iostream>
#include <exception>

EventManagerThread::EventManagerThread(Queue<std::string>& queueSenderGame, 
								Queue<std::string>& queueRenderEvent,
								Window& window, bool& isConnected):
    							queueSenderGame(queueSenderGame), 
								queueRenderEvent(queueRenderEvent),
								window(window),
								isConnected(isConnected) {}

void EventManagerThread::run() { try {

	while (true) {

		SDL_Event event;
		//con SDL_WaitEvent(&event) algunos eventos no los registra
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE: case SDLK_q:
						return;
					case SDLK_RIGHT: 
						std::cout << "entra a flecha derecha\n";
						//queueSenderGame.push(move())
						break;
					case SDLK_LEFT:
						std::cout << "entra a flecha izquierda\n";
						break;
					case SDLK_UP:
						std::cout << "entra a flecha arriba\n";
						break;
					case SDLK_DOWN:
						std::cout << "entra a flecha abajo\n";
						break;
				}
			} else if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
					case SDLK_RIGHT: 
						std::cout << "sale a flecha derecha\n";
						break;
					case SDLK_LEFT:
						std::cout << "sale a flecha izquierda\n";
						break;
					case SDLK_UP:
						std::cout << "sale a flecha arriba\n";
						break;
					case SDLK_DOWN:
						std::cout << "sale a flecha abajo\n";
						break;
				}
			}
		}
	}
	} catch (const std::exception& e) {
        std::cerr << "An exception occurred in EventManager::run(): " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown exception occurred in EventManager::run()" << std::endl;
    }
}








