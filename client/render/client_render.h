#ifndef CLIENT_RENDER_H
#define CLIENT_RENDER_H

#include <SDL2pp/SDL2pp.hh>
#include <exception>
#include <string>
#include <vector>

#include "liberror.h"
#include "action_client.h"
#include "client_texture_manager.h"
#include "client_game_state.h"
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

   void drawPlayer(player_t& previousPlayer, 
                  player_t& currentPlayer);

   void drawInfected(infected_t& previousInfected, 
            infected_t& currentInfected);

   void renderLifeBar(player_t& currentPlayer);

   public:
   ClientRenderer(Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender, 
                    Queue<std::shared_ptr<ActionClient>>& qEventsToRender, 
                    SDL2pp::Window& window_);
                    
   int render();
};

#endif  // CLIENT_RENDER_H