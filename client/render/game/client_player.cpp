#include "client_player.h"

using namespace SDL2pp;

ClientPlayer::ClientPlayer(std::map<state_t, GameTexture>& textures,
                            std::map<state_t, std::shared_ptr<Sound>>& sounds,
                            player_t& currentPlayer) : 
                            texturesPlayer(textures),
                            sounds(sounds),
                            comingEndDeath(false) {

    previousState = currentPlayer.state;
    currentState = currentPlayer.state;
    x = currentPlayer.x;
    y = currentPlayer.y;
    lookingTo = currentPlayer.lookingTo;

    RendererConfig& config = RendererConfig::getInstance();
    std::map<std::string, int> dimensionsWindows = config.getDimensionsWindows();
    std::map<std::string, int> dimensionsLifeBar = config.getDimensionsLifeBar();

    viewportWidth = dimensionsWindows["WINDOW_WIDTH"] + 2 * dimensionsWindows["IMAGE_BORDER_PADDING"];
    viewportHeight = dimensionsWindows["WINDOW_HEIGHT"];
    gameWidth = dimensionsWindows["GAME_WIDTH"];
    gameHeight = dimensionsWindows["GAME_HEIGHT"];
    width = dimensionsWindows["WINDOW_WIDTH"] / 6;
    height = dimensionsWindows["WINDOW_HEIGHT"] / 4;
};

GameTexture& ClientPlayer::getTexturePlayer(state_t state){
    std::map<state_t, GameTexture>::iterator iter = texturesPlayer.find(state);
    if (iter == texturesPlayer.end()) {
        //lanzar excepcion
    }
    return iter->second;
}

void ClientPlayer::playSound(state_t state, int playMode){
    if (state == IDLE){
        return;
    }
    if (state == WALKING_SHOOTING){
        state = WALKING;
    }
    if (state == RUNNING_SHOOTING){
        state = RUNNING;
    }
    std::map<state_t, std::shared_ptr<Sound>>::iterator iter = sounds.find(state);
    if (iter == sounds.end()) {
        std::cout << "NO SE ENCONTRO SONIDO: " << state << "\n";
        //lanzar excepcion
    }
    (iter->second)->play(playMode);  
}

void ClientPlayer::stopSound(state_t state){
    if (state == WALKING_SHOOTING){
        state = WALKING;
    }
    if (state == RUNNING_SHOOTING){
        state = RUNNING;
    }
    std::map<state_t, std::shared_ptr<Sound>>::iterator iter = sounds.find(state);
    if (iter == sounds.end()) {
        std::cout << "NO SE ENCONTRO SONIDO: " << state << "\n";
        //lanzar excepcion
    }
    (iter->second)->stop();   
}

void ClientPlayer::draw(SDL2pp::Renderer& renderer, int it){

    GameTexture& texture = getTexturePlayer(currentState);

    int frame = it % texture.n;
    if ((currentState == DYING || currentState == DEAD) && (frame == texture.n - 1)){
        comingEndDeath == true;
    }
    if ((currentState == DYING || currentState == DEAD) && comingEndDeath){
        frame = texture.n - 1;
    }

    Rect srcRect((texture.width / texture.n) * frame,
                0,
                texture.width / texture.n, 
                texture.height);

    Rect dstRect((x * viewportWidth) / gameWidth,
                viewportHeight - y - gameHeight,
                width, 
                height);

    if (lookingTo == ENTITY_LOOKING_LEFT) {
        SDL_RenderCopyEx(renderer.Get(), texture.texture.Get(), &srcRect, &dstRect, 0, nullptr, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_RenderCopyEx(renderer.Get(), texture.texture.Get(), &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
    }

    //y si soy
    if (currentState != previousState){
        playSound(currentState, -1);
    }
    if (currentState != previousState && currentState == IDLE){
        stopSound(previousState);
    }
}

void ClientPlayer::updatePlayer(player_t& newCurrentPlayer){
    previousState = currentState;
    currentState = newCurrentPlayer.state;
    x = newCurrentPlayer.x;
    y = newCurrentPlayer.y;
    lookingTo = newCurrentPlayer.lookingTo;
}
