#include "client_event_manager.h"

#include <exception>
#include <iostream>

EventManagerThread::EventManagerThread(Queue<ActionClient*>& qEventsToSender,
                                       Queue<ActionClient*>& qEventsToRender,
                                       Window& window, bool& isConnected) : qEventsToSender(qEventsToSender),
                                                                            qEventsToRender(qEventsToRender),
                                                                            window(window),
                                                                            isConnected(isConnected) {}
//para ahora voy a suponer que solo existe un jugador con id 0
void EventManagerThread::run() {
    try {
        while (true) {
            SDL_Event event;
            // con SDL_WaitEvent(&event) algunos eventos no los registra
            while (SDL_PollEvent(&event)) {
                ActionClient* action;
                if (event.type == SDL_QUIT) {
                    return;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            return;
                        case SDLK_RIGHT:
                            //instaciar el dto, no la accion
                            action = new StartMove(0, 1, 0);
                            break;
                        case SDLK_LEFT:
                            action = new StartMove(0, -1, 0);
                            break;
                        case SDLK_UP:
                            action = new StartMove(0, 0, -1);
                            break;
                        case SDLK_DOWN:
                            action = new StartMove(0, 0, 1);
                            break;
                        case SDLK_c:
                            action = new Create("partida0");
                            break;                        
                        case SDLK_j:
                            action = new Join(0);
                            break;
                        case SDLK_s:
                            action = new StartGame();
                            break;
                    }
                    qEventsToSender.push(action);
                } else if (event.type == SDL_KEYUP) {
                    switch (event.key.keysym.sym) {
                        case SDLK_RIGHT:
                            action = new EndMove(0);
                            qEventsToSender.push(action);
                            break;
                        case SDLK_LEFT:
                            action = new EndMove(0);
                            qEventsToSender.push(action);
                            break;
                        case SDLK_UP:
                            action = new EndMove(0);
                            qEventsToSender.push(action);
                            break;
                        case SDLK_DOWN:
                            action = new EndMove(0);
                            qEventsToSender.push(action);
                            break;
                    }
                } else if (event.type == SDL_QUIT){
                    std::cout << "entra a quit\n";
                    //que pushee end
                    //qEventsToSender.push();
                    //qEventsToRender.push();
                    return;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "An exception occurred in EventManager::run(): " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown exception occurred in EventManager::run()" << std::endl;
    }
}