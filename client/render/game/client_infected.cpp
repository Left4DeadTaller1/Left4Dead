#include "client_infected.h"

using namespace SDL2pp;
#define LOOPS_TO_ADVANCE_FRAME 5

ClientInfected::ClientInfected(std::map<state_t, GameTexture>& textures,
                            std::map<state_t, std::shared_ptr<Sound>>& sounds,
                            infected_t& currentInfected,
                            GameTexture& textureLifeBar) : 
                            texturesInfected(textures),
                            sounds(sounds),
                            isDead(false),
                            counterDeath(counterDeath),
                            lifeBar(textureLifeBar, currentInfected.health, 
                            currentInfected.x, currentInfected.y, 
                            currentInfected.lookingTo, currentInfected.typeInfected) {

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
    width = dimensionsWindows["WINDOW_WIDTH"] / dimensionsWindows["CTE_DIVISION_WIDTH_ENTITY"];
    height = dimensionsWindows["WINDOW_HEIGHT"] / dimensionsWindows["CTE_DIVISION_HEIGHT_ENTITY"];
};

GameTexture& ClientInfected::getTextureInfected(state_t state){
    std::map<state_t, GameTexture>::iterator iter = texturesInfected.find(state);
    if (iter == texturesInfected.end()) {
        throw std::runtime_error("Error al cargar la textura");
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
        throw std::runtime_error("No se encontró el sonido");
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
        throw std::runtime_error("No se encontró el sonido");
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

    lifeBar.draw(renderer);
}

void ClientInfected::updateInfected(infected_t& newCurrentInfected){
    previousState = currentState;
    currentState = newCurrentInfected.state;
    x = newCurrentInfected.x;
    y = newCurrentInfected.y;
    lookingTo = newCurrentInfected.lookingTo;
    lifeBar.updateLifeBar(newCurrentInfected.health, newCurrentInfected.x, 
                        newCurrentInfected.y, newCurrentInfected.lookingTo);
}

void ClientInfected::updateSizeWindow(uint32_t newWidth, uint32_t newHeight){
    RendererConfig& config = RendererConfig::getInstance();
    std::map<std::string, int> dimensionsWindows = config.getDimensionsWindows();

    viewportWidth = newWidth + 2 * dimensionsWindows["IMAGE_BORDER_PADDING"];
    viewportHeight = newHeight;
    width = newWidth/ dimensionsWindows["CTE_DIVISION_WIDTH_ENTITY"];
    height = newHeight / dimensionsWindows["CTE_DIVISION_HEIGHT_ENTITY"];

    lifeBar.updateSizeWindow(newWidth, newHeight);
}