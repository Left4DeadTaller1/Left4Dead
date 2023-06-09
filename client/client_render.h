#ifndef CLIENT_RENDER_H
#define CLIENT_RENDER_H

#include <SDL2pp/SDL2pp.hh>
#include <exception>
#include <string>
#include <vector>

#include "liberror.h"
#include "client_receiver.h"
#include "action_client.h"
#include "client_texture_manager.h"
#include "client_texture.h"
#include "queue.h"

class ClientRenderer {
   private:
   Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender;
   Queue<std::shared_ptr<ActionClient>>& qEventsToRender;
   SDL2pp::Window& window;
   SDL2pp::Renderer renderer;
   TextureManager textureManager;
   std::shared_ptr<gameStateDTO_t> previousGameStateDTO;

   void drawBackground(SDL2pp::Texture& background);

   void drawPlayer(std::shared_ptr<entity_t> previousPlayer, 
                  std::shared_ptr<entity_t> currentPlayer);

   std::shared_ptr<entity_t> findPlayer(int idPlayer);

   public:
   ClientRenderer(Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender, 
                    Queue<std::shared_ptr<ActionClient>>& qEventsToRender, 
                    SDL2pp::Window& window_);
                    
   int render();
};

#endif  // CLIENT_RENDER_H