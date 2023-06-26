#include "client_infected.h"

using namespace SDL2pp;
#define LOOPS_TO_ADVANCE_FRAME 5

ClientInfected::ClientInfected(std::map<state_t, GameTexture>& textures,
                            std::map<state_t, std::shared_ptr<Sound>>& sounds,
                            infected_t& currentInfected) : 
                            texturesInfected(textures),
                            sounds(sounds),
                            isDead(false),
                            counterDeath(counterDeath) {

    previousState = currentInfected.state;
    currentState = currentInfected.state;
    x = currentInfected.x;
    y = currentInfected.y;
    lookingTo = currentInfected.lookingTo;

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

GameTexture& ClientInfected::getTextureInfected(state_t state){
    std::map<state_t, GameTexture>::iterator iter = texturesInfected.find(state);
    if (iter == texturesInfected.end()) {
        //lanzar excepcion
    }
    return iter->second;
}

bool ClientInfected::isZombieDead(void){
    return isDead;
}

void ClientInfected::playSound(state_t state, int playMode){
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

void ClientInfected::stopSound(state_t state){
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

void ClientInfected::draw(SDL2pp::Renderer& renderer, int it){

    GameTexture& texture = getTextureInfected(currentState);

    int frame = it % texture.n;
    
    if ((currentState == DYING || currentState == DEAD)){
        counterDeath++;
    }
    if ((currentState == DYING || currentState == DEAD) && counterDeath * LOOPS_TO_ADVANCE_FRAME > texture.n){
        frame = texture.n - 1;
    }
    if (counterDeath / LOOPS_TO_ADVANCE_FRAME > 10){
        isDead = true;
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
    /*if (currentState != previousState){
        playSound(currentState, -1);
    }
    if (currentState != previousState && currentState == IDLE){
        stopSound(previousState);
    }*/
}

void ClientInfected::updateInfected(infected_t& newCurrentInfected){
    previousState = currentState;
    currentState = newCurrentInfected.state;
    x = newCurrentInfected.x;
    y = newCurrentInfected.y;
    lookingTo = newCurrentInfected.lookingTo;
}