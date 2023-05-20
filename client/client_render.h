#ifndef CLIENT_RENDER_H
#define CLIENT_RENDER_H

#include <string>
#include <vector>

#include "liberror.h"
#include "client_receiver.h"
#include "queue.h"

#include <exception>
#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

class ClientRenderer {
   public:
    ClientRenderer(Queue<std::string>& queueRenderGame, 
                    Queue<std::string>& queueRenderEvent, 
                    Window& window);
                    
    void run();

    int render();

   private:
    Queue<std::string>& queueRenderGame;
    Queue<std::string>& queueRenderEvent;
    Window& window;

    void drawBackground(Renderer& renderer, Texture& background);

    void drawSoldier(Renderer& renderer, Texture& soldier, int textureWidth, int textureHeight);
};

#endif  // CLIENT_RENDER_H