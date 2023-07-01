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
#include "mainwindow.h"
#include "action_client.h"
#include "client_texture_manager.h"
#include "client_sound_manager.h"
#include "client_game_state.h"
#include "client_game.h"
#include "client_texture.h"
#include "renderer_config.h"
#include "action_render.h"
#include "client_protocol.h"
#include "queue.h"
#include <atomic>

class ClientRenderer {
   private:
   std::atomic<bool>& isConnected;
   Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender;
   Queue<std::shared_ptr<ActionRender>>& qEventsToRender;
   ClientProtocol& protocol;
   SDL2pp::Window& window;
   SDL2pp::Renderer renderer;
   TextureManager textureManager;
   SoundManager soundManager;
   ClientGame game;
   MainWindow& windowQT;

   uint32_t viewportXInicial;
   uint32_t viewportWidth;
   uint32_t viewportHeight;

   int ms_per_frame;
   int loops_to_advance_frame;

   int handlerAction(std::shared_ptr<ActionRender> action);

   public:
   ClientRenderer(std::atomic<bool>& isConnected, 
                  Queue<std::shared_ptr<gameStateDTO_t>>& qServerToRender, 
                  Queue<std::shared_ptr<ActionRender>>& qEventsToRender, 
                  SDL2pp::Window& window_, ClientProtocol& protocol, 
                  MainWindow& windowQT);

   void copySprite(SDL2pp::Texture& texture, 
                  SDL2pp::Rect& srcRect, 
                  SDL2pp::Rect& dstRect, 
                  int lookingTo);
                    
   int looprender(void);
};

#endif  // CLIENT_RENDER_H