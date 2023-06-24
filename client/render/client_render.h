#ifndef CLIENT_RENDER_H
#define CLIENT_RENDER_H

#include "../../server_root/game/configuration/game_config.h"
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_mixer.h>
#include <exception>
#include <string>
#include <vector>
#include <thread>

#include "liberror.h"
#include "action_client.h"
#include "client_texture_manager.h"
#include "client_sound_manager.h"
#include "client_game_state.h"
#include "client_game.h"
#include "client_texture.h"
#include "queue.h"
#include <atomic>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_HEIGHT 150
#define GAME_WIDTH 1500

//entity
#define ENTITY_WIDTH WINDOW_WIDTH / 6
#define ENTITY_HEIGHT WINDOW_HEIGHT / 4
#define ENTITY_LOOKING_LEFT 0
#define ENTITY_LOOKING_RIGHT 1

//size viewport
#define IMAGE_BORDER_PADDING 40
#define VIEWPORT_X_INITIAL - IMAGE_BORDER_PADDING
#define VIEWPORT_WIDTH WINDOW_WIDTH + 2 * IMAGE_BORDER_PADDING
#define VIEWPORT_HEIGHT WINDOW_HEIGHT

//render life bar
#define LIFE_BAR_WIDTH 20
#define LIFE_BAR_HEIGHT 50
#define MAX_HEALTH 100
#define LIFE_LEVELS 10
#define DIST_X_LIFE_BAR_TO_ENTITY_LOOKING_LEFT 100
#define DIST_X_LIFE_BAR_TO_ENTITY_LOOKING_RIGHT 30
#define DIST_Y_LIFE_BAR_TO_ENTITY 30

class ClientRenderer {
   private:
   std::atomic<bool>& isConnected;
   Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender;
   Queue<std::shared_ptr<ActionClient>>& qEventsToRender;
   SDL2pp::Window& window;
   SDL2pp::Renderer renderer;
   TextureManager textureManager;
   SoundManager soundManager;
   ClientGame game;

   void drawBackground(SDL2pp::Texture& background);

   void drawPlayer(player_t& previousPlayer, 
                  player_t& currentPlayer, int it);

   void drawInfected(infected_t& previousInfected, 
            infected_t& currentInfected, int it);

   void renderLifeBar(player_t& currentPlayer);

   void  drawPlayers(std::map<uint8_t, player_t>& players, int it);

   void  drawInfected(std::map<uint8_t, infected_t>& infected, int it);

   void  drawInicio(void);

   public:
   ClientRenderer(std::atomic<bool>& isConnected, 
                  Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender, 
                  Queue<std::shared_ptr<ActionClient>>& qEventsToRender, 
                  SDL2pp::Window& window_);

   void copySprite(SDL2pp::Texture& texture, 
                  SDL2pp::Rect& srcRect, 
                  SDL2pp::Rect& dstRect, 
                  int lookingTo);
                    
   int looprender(void);
};

#endif  // CLIENT_RENDER_H