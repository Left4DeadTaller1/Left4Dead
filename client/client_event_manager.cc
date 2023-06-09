#include "client_event_manager.h"

using namespace SDL2pp;

EventManagerThread::EventManagerThread(Queue<std::shared_ptr<ActionClient>>& qEventsToSender,
                                       Queue<std::shared_ptr<ActionClient>>& qEventsToRender,
                                       SDL2pp::Window& window, bool& isConnected) : qEventsToSender(qEventsToSender),
                                                                            qEventsToRender(qEventsToRender),
                                                                            window(window),
                                                                            isConnected(isConnected) {}

void EventManagerThread::run() {
    try {
        bool shiftPressed = false;

        while (true) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                std::shared_ptr<ActionClient> action;
                
                if (event.type == SDL_QUIT) {
                    return;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            return;
                        case SDLK_LSHIFT:
                            shiftPressed = true;
                            break;
                        case SDLK_RIGHT:
                            action = std::make_shared<StartMove>(shiftPressed ? RUN : WALK, RIGHT);
                            break;
                        case SDLK_LEFT:
                            action = std::make_shared<StartMove>(shiftPressed ? RUN : WALK, LEFT);
                            break;
                        case SDLK_UP:
                            action = std::make_shared<StartMove>(shiftPressed ? RUN : WALK, UP);
                            break;
                        case SDLK_DOWN:
                            action = std::make_shared<StartMove>(shiftPressed ? RUN : WALK, DOWN);
                            break;
                        case SDLK_c:
                            action = std::make_shared<Create>("partida0");
                            break;
                        case SDLK_j:
                            action = std::make_shared<Join>(0);
                            break;
                        case SDLK_s:
                            action = std::make_shared<StartGame>();
                            break;
                    }

                    if (action) {
                        qEventsToSender.push(action);
                    }
                } else if (event.type == SDL_KEYUP) {
                    if (event.key.keysym.sym == SDLK_LSHIFT) {
                        shiftPressed = false;
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