/*#include "client_player.h"

using namespace SDL2pp;

ClientPlayer(TextureManager& textureManager): textureManager(textureManager) {};

void ClientPlayer::draw(SDL2pp::Renderer& renderer){
    GameTexture& texture = textureManager.getTexture(SOLDIER1, currentPlayer.state);

    Rect srcRect((texture.width / texture.n)* (previousPlayer.x % texture.n),
                0,
                texture.width / texture.n, 
                texture.height);

    Rect dstRect((currentPlayer.x * VIEWPORT_WIDTH) / GAME_WIDTH,
                VIEWPORT_HEIGHT - currentPlayer.y - GAME_HEIGHT,
                ENTITY_WIDTH, 
                ENTITY_HEIGHT);

    ClientRenderer::copySprite(texture.texture, srcRect, dstRect, currentPlayer.lookingTo);
}

void ClientPlayer::updatePlayer(player_t& newCurrentPlayer){
    previousPlayer = currentPlayer;
    currentPlayer = newCurrentPlayer;
}*/