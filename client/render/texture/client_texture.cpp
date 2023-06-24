#include "client_texture.h"
using namespace SDL2pp;

GameTexture::GameTexture(Renderer& renderer, int divisionTexture, const std::string& texturePath):
    texture(renderer, texturePath),
    width(0),
    height(0),
    n(divisionTexture){
        SDL_QueryTexture(texture.Get(), NULL, NULL, &width, &height);
    }
