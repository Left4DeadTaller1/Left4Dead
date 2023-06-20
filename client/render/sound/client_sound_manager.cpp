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
    loadTranslations();
}

SoundManager::~SoundManager() {
    Mix_CloseAudio();
    Mix_Quit();
}

void SoundManager::playSound(typeEntity_t typeEntity, state_t state, int playMode){
    if (state == IDLE){
        return;
    }
    if (state == WALKING_SHOOTING){
        state = WALKING;
    }
    if (state == RUNNING_SHOOTING){
        state = RUNNING;
    }
    std::string nameSound = translationTypeEntity[typeEntity] + "-" + translationState[state];
    std::cout << "name : " << nameSound << "\n";
    std::map<std::string, std::shared_ptr<Sound>>::iterator iter = sounds.find(nameSound);
    if (iter == sounds.end()) {
        std::cout << "NO SE ENCONTRO SONIDO: " << nameSound << "\n";
        //lanzar excepcion
    }
    (iter->second)->play(playMode);
}

void SoundManager::stopSound(typeEntity_t typeEntity, state_t state){
    if (state == IDLE){
        return;
    }
    if (state == WALKING_SHOOTING){
        state = WALKING;
    }
    if (state == RUNNING_SHOOTING){
        state = RUNNING;
    }
    std::string nameSound = translationTypeEntity[typeEntity] + "-" + translationState[state];
    std::map<std::string, std::shared_ptr<Sound>>::iterator iter = sounds.find(nameSound);
    if (iter == sounds.end()) {
        std::cout << "NO SE ENCONTRO SONIDO: " << nameSound << "\n";
        //lanzar excepcion
        return;
    }
    (iter->second)->stop();
}

void SoundManager::loadTranslations(){
    translationTypeEntity[JUMPER] = "jumper";
    translationTypeEntity[SPEAR] = "spear";
    translationTypeEntity[VENOM] = "venom";
    translationTypeEntity[WITCH] = "witch";
    translationTypeEntity[ZOMBIE] = "zombie";
    translationTypeEntity[SOLDIER1] = "soldier1";
    translationTypeEntity[SOLDIER2] = "soldier2";
    translationTypeEntity[SOLDIER3] = "soldier3";

    translationState[WALKING] = "walk";
    translationState[RUNNING] = "run";
    translationState[IDLE] = "idle";
    translationState[DEAD] = "dead";
    translationState[HURT] = "hurt";
    translationState[RELOADING] = "recharge";
    translationState[SHOOTING] = "shot1";
    translationState[ATTACK] = "attack";
    translationState[ATTACK1] = "attack1";
    translationState[ATTACK2] = "attack2";
    translationState[ATTACK3] = "attack3";
    translationState[EATING] = "eating";
    translationState[JUMP] = "jump";
    translationState[FALL] = "fall";
    translationState[PROTECT] = "protect";
    translationState[RUN_AND_ATTACK] = "run+attack";
    translationState[ATTACK1a] = "attack1a";
    translationState[SCREAM] = "scream";
    translationState[BITE] = "bite";
}

void SoundManager::loadSounds(){
    //load sounds soldier 1
    sounds.emplace("soldier1-attack", std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/disparo3.wav", 2));
    sounds.emplace("soldier1-dead", std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/dead.wav", 3));
    sounds.emplace("soldier1-explosion", std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/explosion.wav", 4));
    sounds.emplace("soldier1-grenade", std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/granada.wav", 5));
    sounds.emplace("soldier1-hurt", std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/grito_de_ayuda.wav", 6));
    sounds.emplace("soldier1-recharge", std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/cargar_arma1.wav", 7));
    sounds.emplace("soldier1-run", std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/trotar.wav", 8));
    sounds.emplace("soldier1-shot1", std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/disparo1.wav", 9));
    sounds.emplace("soldier1-shot2", std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/disparo1.wav", 10));
    sounds.emplace("soldier1-walk", std::make_shared<Sound>(DATA_PATH "/client/render/resources/sounds/caminar2.wav", 11));
}
