#ifndef CLIENT_TEXTURE_MANAGER_H
#define CLIENT_TEXTURE_MANAGER_H

#include <SDL2pp/SDL2pp.hh>
#include <string>
#include <memory>
#include <map>
#include "client_texture.h"
#include "client_protocol.h"

class TextureManager {
    private:
    std::map<std::string, std::shared_ptr<GameTexture>> textures;

    void loadTextures(SDL2pp::Renderer& renderer);

    public:
    TextureManager(SDL2pp::Renderer& renderer);

    std::shared_ptr<GameTexture> getTexture(const std::string& textureName);
};

#endif