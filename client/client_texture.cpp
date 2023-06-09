#include "client_texture.h"
using namespace SDL2pp;

GameTexture::GameTexture(Renderer& renderer, const std::string& texturePath):
    texture(renderer, texturePath),
    width(0),
    height(0){
        SDL_QueryTexture(texture.Get(), NULL, NULL, &width, &height);
    }

