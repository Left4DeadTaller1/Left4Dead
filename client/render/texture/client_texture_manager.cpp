#include "client_texture_manager.h"

using namespace SDL2pp;

TextureManager::TextureManager(Renderer& renderer){
    loadTextures(renderer);
}

GameTexture& TextureManager::getBackgroundTexture(const std::string& nameTexture){
    std::map<std::string, GameTexture>::iterator iter = texturesBackground.find(nameTexture);
    if (iter == texturesBackground.end()) {
        //lanzar excepcion
    }
    return iter->second;
}

std::map<state_t, GameTexture>& TextureManager::getTextures(typeEntity_t type){
    if (type == JUMPER){
        return texturesJumper;
    }
    if (type == SPEAR){
        return texturesSpear;
    }
    if (type == VENOM){
        return texturesVenom;
    }
    if (type == WITCH){
        return texturesWitch;
    }
    if (type == ZOMBIE){
        return texturesZombie;
    }
    if (type == SOLDIER1){
        return texturesSoldier1;
    }
}

void TextureManager::loadTextures(Renderer& renderer){

    //load backgrounds
    texturesBackground.emplace("background-war1-bright-war", GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War1/Bright/War.png"));
    texturesBackground.emplace("background-war1-pale-war", GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War1/Pale/War.png"));
    texturesBackground.emplace("background-war2-bright-war", GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War2/Bright/War2.png"));                                                    
    texturesBackground.emplace("background-war2-pale-war", GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War2/Pale/War2.png"));
    texturesBackground.emplace("background-war3-bright-war", GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War3/Bright/War3.png"));
    texturesBackground.emplace("background-war3-pale-war", GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War3/Pale/War3.png"));
    texturesBackground.emplace("background-war4-bright-war", GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War4/Bright/War4.png"));
    texturesBackground.emplace("background-war4-pale-war", GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War4/Pale/War4.png"));
    texturesBackground.emplace("barras-vida", GameTexture(renderer, 11,
                                                DATA_PATH "/client/render/resources/vida/barrasvida.png"));

    //load textures soldier 1
    texturesSoldier1.emplace(ATTACK, GameTexture(renderer, 3,
                                        DATA_PATH "/client/render/resources/Soldier_1/Attack.png"));
    texturesSoldier1.emplace(DEAD, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Soldier_1/Dead.png"));
    texturesSoldier1.emplace(DYING, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Soldier_1/Dead.png"));
    texturesSoldier1.emplace(HURT, GameTexture(renderer, 3,
                                        DATA_PATH "/client/render/resources/Soldier_1/Hurt.png"));
    texturesSoldier1.emplace(IDLE, GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Soldier_1/Idle.png"));
    texturesSoldier1.emplace(RELOADING, GameTexture(renderer, 13,
                                        DATA_PATH "/client/render/resources/Soldier_1/Recharge.png"));
    texturesSoldier1.emplace(RUNNING, GameTexture(renderer, 8,
                                        DATA_PATH "/client/render/resources/Soldier_1/Run.png"));
    texturesSoldier1.emplace(SHOOTING, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Soldier_1/Shot_1.png"));
    //texturesSoldier1.emplace(shot2, GameTexture(renderer, 4,
    //                                    DATA_PATH "/client/render/resources/Soldier_1/Shot_2.png"));
    texturesSoldier1.emplace(WALKING, GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Soldier_1/Walk.png"));

    //load texturesJumper jumper
    texturesJumper.emplace(ATTACK, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Jumper/Attack_1.png"));
    texturesJumper.emplace(ATTACK1, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Jumper/Attack_1.png"));
    texturesJumper.emplace(ATTACK2, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Jumper/Attack_2.png"));
    texturesJumper.emplace(ATTACK3, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Jumper/Attack_3.png"));
    texturesJumper.emplace(DEAD, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Jumper/Dead.png"));
    texturesJumper.emplace(DYING, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Jumper/Dead.png"));
    texturesJumper.emplace(EATING, GameTexture(renderer, 11,
                                        DATA_PATH "/client/render/resources/Jumper/Eating.png"));
    texturesJumper.emplace(HURT, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Jumper/Hurt.png"));
    texturesJumper.emplace(IDLE, GameTexture(renderer, 9,
                                        DATA_PATH "/client/render/resources/Jumper/Idle.png"));
    texturesJumper.emplace(JUMP, GameTexture(renderer, 6,
                                        DATA_PATH "/client/render/resources/Jumper/Jump.png"));
    texturesJumper.emplace(RUNNING, GameTexture(renderer, 8,
                                        DATA_PATH "/client/render/resources/Jumper/Run.png"));
    texturesJumper.emplace(WALKING, GameTexture(renderer, 10,
                                        DATA_PATH "/client/render/resources/Jumper/Walk.png"));

    //load texturesSpear spear
    texturesSpear.emplace(ATTACK, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Spear/Attack_1.png"));
    texturesSpear.emplace(ATTACK1, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Spear/Attack_1.png"));
    texturesSpear.emplace(ATTACK2, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Spear/Attack_2.png"));
    texturesSpear.emplace(DEAD, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Spear/Dead.png"));
    texturesSpear.emplace(DYING, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Spear/Dead.png"));
    texturesSpear.emplace(FALL, GameTexture(renderer, 6,
                                        DATA_PATH "/client/render/resources/Spear/Fall.png"));
    texturesSpear.emplace(HURT, GameTexture(renderer, 3,
                                        DATA_PATH "/client/render/resources/Spear/Hurt.png"));
    texturesSpear.emplace(IDLE, GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Spear/Idle.png"));
    texturesSpear.emplace(PROTECT, GameTexture(renderer, 2,
                                        DATA_PATH "/client/render/resources/Spear/Protect.png"));
    texturesSpear.emplace(RUNNING, GameTexture(renderer, 6,
                                        DATA_PATH "/client/render/resources/Spear/Run.png"));
    texturesSpear.emplace(RUN_AND_ATTACK, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Spear/Run+attack.png"));
    texturesSpear.emplace(WALKING, GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Spear/Walk.png"));

    //load texturesVenom venom
    texturesVenom.emplace(ATTACK, GameTexture(renderer,8, 
                                        DATA_PATH "/client/render/resources/Venom/Attack2.png"));
    texturesVenom.emplace(SHOOTING, GameTexture(renderer,8, 
                                        DATA_PATH "/client/render/resources/Venom/Attack1.png"));
    texturesVenom.emplace(ATTACK1, GameTexture(renderer,8, 
                                        DATA_PATH "/client/render/resources/Venom/Attack1.png"));
    texturesVenom.emplace(ATTACK1a, GameTexture(renderer, 12,
                                        DATA_PATH "/client/render/resources/Venom/Attack1a.png"));
    texturesVenom.emplace(ATTACK2, GameTexture(renderer, 14,
                                        DATA_PATH "/client/render/resources/Venom/Attack2.png"));
    texturesVenom.emplace(DEAD, GameTexture(renderer, 6,
                                        DATA_PATH "/client/render/resources/Venom/Dead.png"));
    texturesVenom.emplace(DYING, GameTexture(renderer, 6,
                                        DATA_PATH "/client/render/resources/Venom/Dead.png"));
    texturesVenom.emplace(HURT, GameTexture(renderer, 3,
                                        DATA_PATH "/client/render/resources/Venom/Hurt.png"));
    texturesVenom.emplace(IDLE, GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Venom/Idle.png"));
    texturesVenom.emplace(JUMP, GameTexture(renderer, 9,
                                        DATA_PATH "/client/render/resources/Venom/Jump.png"));
    texturesVenom.emplace(RUNNING, GameTexture(renderer, 8,
                                        DATA_PATH "/client/render/resources/Venom/Run.png"));
    texturesVenom.emplace(WALKING, GameTexture(renderer, 6,
                                        DATA_PATH "/client/render/resources/Venom/Walk.png"));

    //load texturesWitch witch
    texturesWitch.emplace(ATTACK, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Witch/Attack_1.png"));
    texturesWitch.emplace(ATTACK1, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Witch/Attack_1.png"));
    texturesWitch.emplace(ATTACK2, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Witch/Attack_2.png"));
    texturesWitch.emplace(ATTACK3, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Witch/Attack_3.png"));
    texturesWitch.emplace(DEAD, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Witch/Dead.png"));
    texturesWitch.emplace(DYING, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Witch/Dead.png"));
    texturesWitch.emplace(HURT, GameTexture(renderer, 3,
                                        DATA_PATH "/client/render/resources/Witch/Hurt.png"));
    texturesWitch.emplace(IDLE, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Witch/Idle.png"));
    texturesWitch.emplace(JUMP, GameTexture(renderer, 6,
                                        DATA_PATH "/client/render/resources/Witch/Jump.png"));
    texturesWitch.emplace(RUNNING, GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Witch/Run.png"));
    texturesWitch.emplace(SCREAM, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Witch/Scream.png"));
    texturesWitch.emplace(WALKING, GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Witch/Walk.png"));

    //load texturesZombie zombie
    texturesZombie.emplace(ATTACK, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Zombie/Attack_1.png"));
    texturesZombie.emplace(ATTACK1, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Zombie/Attack_1.png"));
    texturesZombie.emplace(ATTACK2, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Zombie/Attack_2.png"));
    texturesZombie.emplace(ATTACK3, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Zombie/Attack_3.png"));
    texturesZombie.emplace(BITE, GameTexture(renderer, 11,
                                        DATA_PATH "/client/render/resources/Zombie/Bite.png"));
    texturesZombie.emplace(DEAD, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Zombie/Dead.png"));
    texturesZombie.emplace(DYING, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Zombie/Dead.png"));
    texturesZombie.emplace(HURT, GameTexture(renderer, 3,
                                        DATA_PATH "/client/render/resources/Zombie/Hurt.png"));
    texturesZombie.emplace(IDLE, GameTexture(renderer, 8,
                                        DATA_PATH "/client/render/resources/Zombie/Idle.png"));
    texturesZombie.emplace(JUMP, GameTexture(renderer, 8,
                                        DATA_PATH "/client/render/resources/Zombie/Jump.png"));
    texturesZombie.emplace(RUNNING, GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Zombie/Run.png"));
    texturesZombie.emplace(WALKING, GameTexture(renderer, 8,
                                        DATA_PATH "/client/render/resources/Zombie/Walk.png"));
}