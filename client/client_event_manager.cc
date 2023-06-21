#include "client_event_manager.h"

using namespace SDL2pp;

EventManagerThread::EventManagerThread(Queue<std::shared_ptr<ActionClient>>& qEventsToSender,
                                       Queue<std::shared_ptr<ActionClient>>& qEventsToRender,
                                       SDL2pp::Window& window, std::atomic<bool>& isConnected) : 
                                                                    qEventsToSender(qEventsToSender),
                                                                    qEventsToRender(qEventsToRender),
                                                                    window(window),
                                                                    isConnected(isConnected) {}

void EventManagerThread::run() {
    try {
        bool shiftPressed = false;
        bool rightMoveSent = false;
        bool leftMoveSent = false;
        bool upMoveSent = false;
        bool downMoveSent = false;
        bool shootSent = false;

        while (true) {
            SDL_Event event;
            while (SDL_WaitEvent(&event)) {
                std::shared_ptr<ActionClient> action;

                if (event.type == SDL_QUIT) {
                    action = std::make_shared<Exit>();
                    qEventsToRender.push(action);
                    qEventsToSender.close();
                    return;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_LSHIFT:
                            shiftPressed = true;
                            break;
                        case SDLK_s:
                            action = std::make_shared<StartGame>();
                            break;
                        case SDLK_r:
                            action = std::make_shared<Recharge>();
                            break;
                        case SDLK_x:
                            if (!shootSent) {
                                action = std::make_shared<StartShoot>();
                                shootSent = true;
                            }
                            break;
                        case SDLK_RIGHT:
                            if (!rightMoveSent) {
                                action = std::make_shared<StartMove>(shiftPressed ? RUN : WALK, RIGHT);
                                rightMoveSent = true;
                            }
                            break;
                        case SDLK_LEFT:
                            if (!leftMoveSent) {
                                action = std::make_shared<StartMove>(shiftPressed ? RUN : WALK, LEFT);
                                leftMoveSent = true;
                            }
                            break;
                        case SDLK_UP:
                            if (!upMoveSent) {
                                action = std::make_shared<StartMove>(shiftPressed ? RUN : WALK, UP);
                                upMoveSent = true;
                            }
                            break;
                        case SDLK_DOWN:
                            if (!downMoveSent) {
                                action = std::make_shared<StartMove>(shiftPressed ? RUN : WALK, DOWN);
                                downMoveSent = true;
                            }
                            break;
                    }

                    if (action) {
                        qEventsToSender.push(action);
                    }

                } else if (event.type == SDL_KEYUP) {
                    switch (event.key.keysym.sym) {
                        case SDLK_x:
                            if (shootSent){
                                action = std::make_shared<EndShoot>();
                                shootSent = false;
                            }
                            break;
                        case SDLK_RIGHT:
                            if (rightMoveSent) {
                                action = std::make_shared<EndMove>(RIGHT);
                                rightMoveSent = false;
                            }
                            break;
                        case SDLK_LEFT:
                            if (leftMoveSent) {
                                action = std::make_shared<EndMove>(LEFT);
                                leftMoveSent = false;
                            }
                            break;
                        case SDLK_UP:
                            if (upMoveSent) {
                                action = std::make_shared<EndMove>(UP);
                                upMoveSent = false;
                            }
                            break;
                        case SDLK_DOWN:
                            if (downMoveSent) {
                                action = std::make_shared<EndMove>(DOWN);
                                downMoveSent = false;
                            }
                            break;
                        case SDLK_LSHIFT:
                            shiftPressed = false;
                            break;
                    }

                    if (action) {
                        qEventsToSender.push(action);
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