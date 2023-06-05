#ifndef CLIENT_RENDER_H
#define CLIENT_RENDER_H

#include <SDL2pp/SDL2pp.hh>
#include <exception>
#include <string>
#include <vector>

#include "liberror.h"
#include "client_receiver.h"
#include "action_client.h"
#include "queue.h"

using namespace SDL2pp;

class ClientRenderer {
   public:
    ClientRenderer(Queue<int>& qServerToRender, 
                    Queue<ActionClient*>& qEventsToRender, 
                    Window& window);
                    
    void run();

    int render();

   private:
    Queue<int>& qServerToRender;
    Queue<ActionClient*>& qEventsToRender;
    Window& window;
    int posX;
    int posY;

    void drawBackground(Renderer& renderer, Texture& background);

    void drawSoldier(Renderer& renderer, Texture& soldier, 
                                int& textureWidth, int& textureHeight, 
                                int& newPosX, int& newPosY);
};

#endif  // CLIENT_RENDER_H