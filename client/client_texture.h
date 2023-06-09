#ifndef CLIENT_TEXTURE_H
#define CLIENT_TEXTURE_H

#include <SDL2pp/SDL2pp.hh>
#include <string>

class GameTexture {
    protected:
    SDL2pp::Texture texture;
    int width;
    int height;
    //valor division

    friend class ClientRenderer;

    public:
    GameTexture(SDL2pp::Renderer& renderer, const std::string& texturePath);

    //~GameTexture(); //delete punteros
};


#endif  // CLIENT_TEXTURE_H