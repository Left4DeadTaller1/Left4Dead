#ifndef CLIENT_TEXTURE_MANAGER_H
#define CLIENT_TEXTURE_MANAGER_H

#include <SDL2pp/SDL2pp.hh>
#include <string>
#include <memory>
#include <map>
#include "client_texture.h"
#include "client_game_state.h"

class TextureManager {
    private:
    std::map<state_t, GameTexture> texturesSoldier1;
    std::map<state_t, GameTexture> texturesJumper;
    std::map<state_t, GameTexture> texturesSpear;
    std::map<state_t, GameTexture> texturesVenom;
    std::map<state_t, GameTexture> texturesWitch;
    std::map<state_t, GameTexture> texturesZombie;
    std::map<std::string, GameTexture> texturesBackground;
    //GameTexture lifeBar;

    void loadTextures(SDL2pp::Renderer& renderer);

    public:
    TextureManager(SDL2pp::Renderer& renderer);

    std::map<state_t, GameTexture>& getTextures(typeEntity_t type);

    GameTexture& getBackgroundTexture(const std::string& nameTexture);
};

#endif