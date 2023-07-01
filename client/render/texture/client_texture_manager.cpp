#include "client_texture_manager.h"

using namespace SDL2pp;

TextureManager::TextureManager(Renderer& renderer):
    lifeBar(renderer, 11 ,DATA_PATH "/client/render/resources/vida/barrasvida.png"){
    loadTextures(renderer);
}

std::map<TypeWeapon_t, GameTexture>& TextureManager::getTexturesWeapon(){
    return texturesWeapon;
}

GameTexture& TextureManager::getTexture(TypeMap_t typeMap){
    std::map<TypeMap_t, GameTexture>::iterator iter = texturesBackground.find(typeMap);
    if (iter == texturesBackground.end()) {
        throw std::runtime_error("No se encontro textura\n");
    }
    return iter->second;
}

GameTexture& TextureManager::getTexture(std::string texture){
    std::map<std::string, GameTexture>::iterator iter = otherTextures.find(texture);
    if (iter == otherTextures.end()) {
        throw std::runtime_error("No se encontro textura\n");
    }
    return iter->second;
}

GameTexture& TextureManager::getTextureLifeBar(void){
    return lifeBar;
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
    if (type == SOLDIER2){
        return texturesSoldier2;
    }
    if (type == SOLDIER3){
        return texturesSoldier3;
    }
}

void TextureManager::loadTextures(Renderer& renderer){

    //load backgrounds
    texturesBackground.emplace(WAR1_BRIGHT, GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War1/Bright/War.png"));
    texturesBackground.emplace(WAR1_PALE, GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War1/Pale/War.png"));
    texturesBackground.emplace(WAR2_BRIGHT, GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War2/Bright/War2.png"));                                                    
    texturesBackground.emplace(WAR2_PALE, GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War2/Pale/War2.png"));
    texturesBackground.emplace(WAR3_BRIGHT, GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War3/Bright/War3.png"));
    texturesBackground.emplace(WAR3_PALE, GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War3/Pale/War3.png"));
    texturesBackground.emplace(WAR4_BRIGHT, GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War4/Bright/War4.png"));
    texturesBackground.emplace(WAR4_PALE, GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/backgrounds/War4/Pale/War4.png"));

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
    texturesSoldier1.emplace(WALKING, GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Soldier_1/Walk.png"));


    //load textures soldier 2
    texturesSoldier2.emplace(ATTACK, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Soldier_2/Attack.png"));
    texturesSoldier2.emplace(DEAD, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Soldier_2/Dead.png"));
    texturesSoldier2.emplace(DYING, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Soldier_2/Dead.png"));
    texturesSoldier2.emplace(HURT, GameTexture(renderer, 3,
                                        DATA_PATH "/client/render/resources/Soldier_2/Hurt.png"));
    texturesSoldier2.emplace(IDLE, GameTexture(renderer, 9,
                                        DATA_PATH "/client/render/resources/Soldier_2/Idle.png"));
    texturesSoldier2.emplace(RELOADING, GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Soldier_2/Recharge.png"));
    texturesSoldier2.emplace(RUNNING, GameTexture(renderer, 8,
                                        DATA_PATH "/client/render/resources/Soldier_2/Run.png"));
    texturesSoldier2.emplace(SHOOTING, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Soldier_2/Shot_1.png"));
    texturesSoldier2.emplace(WALKING, GameTexture(renderer, 8,
                                        DATA_PATH "/client/render/resources/Soldier_2/Walk.png"));

    //load textures soldier 3
    texturesSoldier3.emplace(ATTACK, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Soldier_3/Attack.png"));
    texturesSoldier3.emplace(DEAD, GameTexture(renderer, 5,
                                        DATA_PATH "/client/render/resources/Soldier_3/Dead.png"));
    texturesSoldier3.emplace(DYING, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Soldier_3/Dead.png"));
    texturesSoldier3.emplace(HURT, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Soldier_3/Hurt.png"));
    texturesSoldier3.emplace(IDLE, GameTexture(renderer, 7,
                                        DATA_PATH "/client/render/resources/Soldier_3/Idle.png"));
    texturesSoldier3.emplace(RELOADING, GameTexture(renderer, 8,
                                        DATA_PATH "/client/render/resources/Soldier_3/Recharge.png"));
    texturesSoldier3.emplace(RUNNING, GameTexture(renderer, 6,
                                        DATA_PATH "/client/render/resources/Soldier_3/Run.png"));
    texturesSoldier3.emplace(SHOOTING, GameTexture(renderer, 4,
                                        DATA_PATH "/client/render/resources/Soldier_3/Shot_1.png"));
    texturesSoldier3.emplace(WALKING, GameTexture(renderer, 8,
                                        DATA_PATH "/client/render/resources/Soldier_3/Walk.png"));

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

    //load weapons
    texturesWeapon.emplace(P90, GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/arma1.png"));
    texturesWeapon.emplace(RIFLE, GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/arma2.png"));
    texturesWeapon.emplace(SNIPER, GameTexture(renderer, 1,
                                                DATA_PATH "/client/render/resources/arma3.png"));

    //load others textures
    otherTextures.emplace("papiro", GameTexture(renderer, 1,
                                            DATA_PATH "/client/render/resources/papiro.png"));
    otherTextures.emplace("game over", GameTexture(renderer, 1,
                                            DATA_PATH "/client/render/resources/gameover.png"));                                               
}