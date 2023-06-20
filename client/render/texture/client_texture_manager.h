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
    std::map<std::string, GameTexture> textures;
    std::map<typeEntity_t, std::string> translationTypeEntity;
    std::map<state_t, std::string> translationState;

    void loadTextures(SDL2pp::Renderer& renderer);

    void loadTranslations(void);

    public:
    TextureManager(SDL2pp::Renderer& renderer);

    GameTexture& getTexture(typeEntity_t typeEntity, state_t state);

    GameTexture& getBackgroundTexture(const std::string& nameTexture);
};

#endif