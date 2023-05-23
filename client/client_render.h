#ifndef CLIENT_RENDER_H
#define CLIENT_RENDER_H

#include <string>
#include <vector>

#include "liberror.h"
#include "client_receiver.h"
#include "client_action/action.h"
#include "queue.h"

#include <exception>
#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

class ClientRenderer {
   public:
    ClientRenderer(Queue<Action*>& qServerToRender, 
                    Queue<Action*>& qEventsToRender, 
                    Window& window,
                    int posX, 
                    int posY);
                    
    void run();

    int render();

   private:
    Queue<Action*>& qServerToRender;
    Queue<Action*>& qEventsToRender;
    Window& window;
    int posX;
    int posY;

    void drawBackground(Renderer& renderer, Texture& background);

    void drawSoldier(Renderer& renderer, Texture& soldier, int textureWidth, int textureHeight);
};

#endif  // CLIENT_RENDER_H