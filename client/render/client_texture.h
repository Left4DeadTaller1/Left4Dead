#ifndef CLIENT_TEXTURE_H
#define CLIENT_TEXTURE_H

#include <SDL2pp/SDL2pp.hh>
#include <string>

class GameTexture {
    protected:
    SDL2pp::Texture texture;
    int width;
    int height;
    int n;          //division texture

    friend class ClientRenderer;

    public:
    GameTexture(SDL2pp::Renderer& renderer, int divisionTexture, const std::string& texturePath);
};


#endif  // CLIENT_TEXTURE_H