#include "client_sound_manager.h"

using namespace SDL2pp;

SoundManager::SoundManager(){
    if (Mix_Init(MIX_INIT_MP3) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to open audio: " << Mix_GetError() << std::endl;
    }
    loadSounds();
}

SoundManager::~SoundManager() {
    Mix_CloseAudio();
    Mix_Quit();
}

std::map<state_t, std::shared_ptr<Sound>>& SoundManager::getSounds(typeEntity_t type){
    if (type == JUMPER){
        return soundsJumper;
    }
    if (type == SPEAR){
        return soundsSpear;
    }
    if (type == VENOM){
        return soundsVenom;
    }
    if (type == WITCH){
        return soundsWitch;
    }
    if (type == ZOMBIE){
        return soundsZombie;
    }
    if (type == SOLDIER1){
        return soundsSoldier1;
    }
}

void SoundManager::loadSounds(){
    //load sounds soldier 1
    soundsSoldier1.emplace(ATTACK, std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/disparo3.wav", 2));
    soundsSoldier1.emplace(DEAD, std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/dead.wav", 3));
    soundsSoldier1.emplace(DYING, std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/dead.wav", 4));
    soundsSoldier1.emplace(HURT, std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/grito_de_ayuda.wav", 6));
    soundsSoldier1.emplace(RELOADING, std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/cargar_arma1.wav", 7));
    soundsSoldier1.emplace(RUNNING, std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/trotar.wav", 8));
    soundsSoldier1.emplace(SHOOTING, std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/disparo1.wav", 9));
    soundsSoldier1.emplace(WALKING, std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/caminar2.wav", 11));
}
