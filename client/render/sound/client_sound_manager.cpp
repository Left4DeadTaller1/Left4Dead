#include "client_sound_manager.h"

using namespace SDL2pp;

SoundManager::SoundManager():
    music(nullptr){
    if (Mix_Init(MIX_INIT_MP3) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to open audio: " << Mix_GetError() << std::endl;
    }
    music = std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/fondo3.mp3", 1);
    loadSounds();
}

void SoundManager::playMusic(void){
    music->play(-1);
}

void SoundManager::stopMusic(void){
    music->stop();
}

SoundManager::~SoundManager() {
    Mix_CloseAudio();
    Mix_Quit();
}

std::map<state_t, std::shared_ptr<Sound>>& SoundManager::getSounds(typeEntity_t type){
    if (type == SOLDIER1 || type == SOLDIER2 || type == SOLDIER3){
        return soundsSoldier;
    }
}

void SoundManager::loadSounds(){
    soundsSoldier.emplace(ATTACK, std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/disparo3.wav", 0));
    soundsSoldier.emplace(DEAD, std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/dead.wav", 0));
    soundsSoldier.emplace(DYING, std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/dead.wav", 0));
    soundsSoldier.emplace(HURT, std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/grito_de_ayuda.wav", 0));
    soundsSoldier.emplace(RELOADING, std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/cargar_arma1.wav", 0));
    soundsSoldier.emplace(RUNNING, std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/trotar.wav", 0));
    soundsSoldier.emplace(SHOOTING, std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/disparo1.wav", 0));
    soundsSoldier.emplace(WALKING, std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/caminar2.wav", 0));
}

