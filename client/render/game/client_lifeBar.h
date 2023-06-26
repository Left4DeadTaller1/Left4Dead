#ifndef CLIENT_LIFE_BAR_H
#define CLIENT_LIFE_BAR_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <memory>
#include <map>
#include "client_game_state.h"
#include "renderer_config.h"
#include "client_texture_manager.h"
#include "client_sound_manager.h"

class LifeBar {
    private:
    uint32_t health;
    uint32_t x;
    uint32_t y;
    uint8_t lookingTo;
    typeEntity_t typeEntity;
    GameTexture& texture;

    uint32_t viewportWidth;
    uint32_t viewportHeight;
    uint32_t gameWidth;
    uint32_t gameHeight;
    uint32_t padding;

    uint32_t width;
    uint32_t height;
    uint32_t distXToEntityLookingLeft;
    uint32_t distXToEntityLookingRight;
    uint32_t distYToEntity;

    uint32_t maxHealth;
    uint32_t lifeLevels;

    public:
    LifeBar(GameTexture& texture, uint32_t health, 
                uint32_t x, uint32_t y, uint8_t lookingTo, 
                typeEntity_t typeEntity);
                
    void draw(SDL2pp::Renderer& renderer, int it);

    void updateLifeBar(uint32_t health, uint32_t x, 
                        uint32_t y, uint8_t lookingTo);

    void updateSizeWindow(uint32_t newWidth, uint32_t newHeight);
};

#endif