#include "client_texture_manager.h"

using namespace SDL2pp;

TextureManager::TextureManager(Renderer& renderer){
    loadTextures(renderer);
    loadTranslations();
}

GameTexture& TextureManager::getBackgroundTexture(const std::string& nameTexture){
    std::map<std::string, GameTexture>::iterator iter = textures.find(nameTexture);
    if (iter == textures.end()) {
        //lanzar excepcion
    }
    return iter->second;
}

GameTexture& TextureManager::getTexture(typeEntity_t typeEntity, state_t state){
    if (state == WALKING_SHOOTING){
        state = WALKING;
    }
    if (state == RUNNING_SHOOTING){
        state = RUNNING;
    }
    std::string nameTexture = translationTypeEntity[typeEntity] + "-" + translationState[state];

    std::map<std::string, GameTexture>::iterator iter = textures.find(nameTexture);
    if (iter == textures.end()) {
        std::cout << "NO SE ENCONTRO TEXTURA: " << nameTexture << "\n";
        //lanzar excepcion
    }
    return iter->second;
}

void TextureManager::loadTranslations(){
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
    translationState[DYING] = "dead";
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

void TextureManager::loadTextures(Renderer& renderer){

    //load backgrounds
    textures.emplace("background-war1-bright-war", GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War1/Bright/War.png"));
    textures.emplace("background-war1-pale-war", GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War1/Pale/War.png"));
    textures.emplace("background-war2-bright-war", GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War2/Bright/War2.png"));                                                    
    textures.emplace("background-war2-pale-war", GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War2/Pale/War2.png"));
    textures.emplace("background-war3-bright-war", GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War3/Bright/War3.png"));
    textures.emplace("background-war3-pale-war", GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War3/Pale/War3.png"));
    textures.emplace("background-war4-bright-war", GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War4/Bright/War4.png"));
    textures.emplace("background-war4-pale-war", GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War4/Pale/War4.png"));
    textures.emplace("barras-vida", GameTexture(renderer, 11,
                                                DATA_PATH "/client/render/resources/vida/barrasvida.png"));

    //load textures soldier 1
    textures.emplace("soldier1-attack", GameTexture(renderer, 3,
                                        DATA_PATH "/client/render/resources/Soldier_1/Attack.png"));
    textures.emplace("soldier1-dead", GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Soldier_1/Dead.png"));
    textures.emplace("soldier1-explosion", GameTexture(renderer, 9,
                                        DATA_PATH "/client/render/resources/Soldier_1/Explosion.png"));
    textures.emplace("soldier1-grenade", GameTexture(renderer, 9,
                                        DATA_PATH "/client/render/resources/Soldier_1/Grenade.png"));
    textures.emplace("soldier1-hurt", GameTexture(renderer, 3,
                                        DATA_PATH "/client/render/resources/Soldier_1/Hurt.png"));
    textures.emplace("soldier1-idle", GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Soldier_1/Idle.png"));
    textures.emplace("soldier1-recharge", GameTexture(renderer, 13,
                                        DATA_PATH "/client/render/resources/Soldier_1/Recharge.png"));
    textures.emplace("soldier1-run", GameTexture(renderer, 8,
                                        DATA_PATH "/client/render/resources/Soldier_1/Run.png"));
    textures.emplace("soldier1-shot1", GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Soldier_1/Shot_1.png"));
    textures.emplace("soldier1-shot2", GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Soldier_1/Shot_2.png"));
    textures.emplace("soldier1-walk", GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Soldier_1/Walk.png"));

    //load textures jumper
    textures.emplace("jumper-attack", GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Jumper/Attack_1.png"));
    textures.emplace("jumper-attack1", GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Jumper/Attack_1.png"));
    textures.emplace("jumper-attack2", GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Jumper/Attack_2.png"));
    textures.emplace("jumper-attack3", GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Jumper/Attack_3.png"));
    textures.emplace("jumper-dead", GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Jumper/Dead.png"));
    textures.emplace("jumper-eating", GameTexture(renderer, 11,
                                        DATA_PATH "/client/render/resources/Jumper/Eating.png"));
    textures.emplace("jumper-hurt", GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Jumper/Hurt.png"));
    textures.emplace("jumper-idle", GameTexture(renderer, 9,
                                        DATA_PATH "/client/render/resources/Jumper/Idle.png"));
    textures.emplace("jumper-jump", GameTexture(renderer, 6,
                                        DATA_PATH "/client/render/resources/Jumper/Jump.png"));
    textures.emplace("jumper-run", GameTexture(renderer, 8,
                                        DATA_PATH "/client/render/resources/Jumper/Run.png"));
    textures.emplace("jumper-walk", GameTexture(renderer, 10,
                                        DATA_PATH "/client/render/resources/Jumper/Walk.png"));

    //load textures spear
    textures.emplace("spear-attack", GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Spear/Attack_1.png"));
    textures.emplace("spear-attack1", GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Spear/Attack_1.png"));
    textures.emplace("spear-attack2", GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Spear/Attack_2.png"));
    textures.emplace("spear-dead", GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Spear/Dead.png"));
    textures.emplace("spear-fall", GameTexture(renderer, 6,
                                        DATA_PATH "/client/render/resources/Spear/Fall.png"));
    textures.emplace("spear-hurt", GameTexture(renderer, 3,
                                        DATA_PATH "/client/render/resources/Spear/Hurt.png"));
    textures.emplace("spear-idle", GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Spear/Idle.png"));
    textures.emplace("spear-protect", GameTexture(renderer, 2,
                                        DATA_PATH "/client/render/resources/Spear/Protect.png"));
    textures.emplace("spear-run", GameTexture(renderer, 6,
                                        DATA_PATH "/client/render/resources/Spear/Run.png"));
    textures.emplace("spear-run+attack", GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Spear/Run+attack.png"));
    textures.emplace("spear-walk", GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Spear/Walk.png"));

    //load textures venom
    textures.emplace("venom-attack", GameTexture(renderer,8, 
                                        DATA_PATH "/client/render/resources/Venom/Attack2.png"));
    textures.emplace("venom-shot1", GameTexture(renderer,8, 
                                        DATA_PATH "/client/render/resources/Venom/Attack1.png"));
    textures.emplace("venom-attack1", GameTexture(renderer,8, 
                                        DATA_PATH "/client/render/resources/Venom/Attack1.png"));
    textures.emplace("venom-attack1a", GameTexture(renderer, 12,
                                        DATA_PATH "/client/render/resources/Venom/Attack1a.png"));
    textures.emplace("venom-attack2", GameTexture(renderer, 14,
                                        DATA_PATH "/client/render/resources/Venom/Attack2.png"));
    textures.emplace("venom-dead", GameTexture(renderer, 6,
                                        DATA_PATH "/client/render/resources/Venom/Dead.png"));
    textures.emplace("venom-hurt", GameTexture(renderer, 3,
                                        DATA_PATH "/client/render/resources/Venom/Hurt.png"));
    textures.emplace("venom-idle", GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Venom/Idle.png"));
    textures.emplace("venom-jump", GameTexture(renderer, 9,
                                        DATA_PATH "/client/render/resources/Venom/Jump.png"));
    textures.emplace("venom-run", GameTexture(renderer, 8,
                                        DATA_PATH "/client/render/resources/Venom/Run.png"));
    textures.emplace("venom-walk", GameTexture(renderer, 6,
                                        DATA_PATH "/client/render/resources/Venom/Walk.png"));

    //load textures witch
    textures.emplace("witch-attack", GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Witch/Attack_1.png"));
    textures.emplace("witch-attack1", GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Witch/Attack_1.png"));
    textures.emplace("witch-attack2", GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Witch/Attack_2.png"));
    textures.emplace("witch-attack3", GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Witch/Attack_3.png"));
    textures.emplace("witch-dead", GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Witch/Dead.png"));
    textures.emplace("witch-hurt", GameTexture(renderer, 3,
                                        DATA_PATH "/client/render/resources/Witch/Hurt.png"));
    textures.emplace("witch-idle", GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Witch/Idle.png"));
    textures.emplace("witch-jump", GameTexture(renderer, 6,
                                        DATA_PATH "/client/render/resources/Witch/Jump.png"));
    textures.emplace("witch-run", GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Witch/Run.png"));
    textures.emplace("witch-scream", GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Witch/Scream.png"));
    textures.emplace("witch-walk", GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Witch/Walk.png"));

    //load textures zombie
    textures.emplace("zombie-attack", GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Zombie/Attack_1.png"));
    textures.emplace("zombie-attack1", GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Zombie/Attack_1.png"));
    textures.emplace("zombie-attack2", GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Zombie/Attack_2.png"));
    textures.emplace("zombie-attack3", GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Zombie/Attack_3.png"));
    textures.emplace("zombie-bite", GameTexture(renderer, 11,
                                        DATA_PATH "/client/render/resources/Zombie/Bite.png"));
    textures.emplace("zombie-dead", GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Zombie/Dead.png"));
    textures.emplace("zombie-hurt", GameTexture(renderer, 3,
                                        DATA_PATH "/client/render/resources/Zombie/Hurt.png"));
    textures.emplace("zombie-idle", GameTexture(renderer, 8,
                                        DATA_PATH "/client/render/resources/Zombie/Idle.png"));
    textures.emplace("zombie-jump", GameTexture(renderer, 8,
                                        DATA_PATH "/client/render/resources/Zombie/Jump.png"));
    textures.emplace("zombie-run", GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Zombie/Run.png"));
    textures.emplace("zombie-walk", GameTexture(renderer, 8,
                                        DATA_PATH "/client/render/resources/Zombie/Walk.png"));
}