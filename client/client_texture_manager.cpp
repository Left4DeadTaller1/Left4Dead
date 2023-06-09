#include "client_texture_manager.h"

using namespace SDL2pp;

TextureManager::TextureManager(Renderer& renderer){
    loadTextures(renderer);
}

std::shared_ptr<GameTexture> TextureManager::getTexture(const std::string& textureName){
    return textures[textureName];
}

void TextureManager::loadTextures(Renderer& renderer){

    //load backgrounds
    textures["background-war1-bright-war"] = std::make_shared<GameTexture>(renderer, 
                                                DATA_PATH "/client/resources/backgrounds/War1/Bright/War.png");
    textures["background-war1-pale-war"] = std::make_shared<GameTexture>(renderer, 
                                                DATA_PATH "/client/resources/backgrounds/War1/Pale/War.png");
    textures["background-war2-bright-war"] = std::make_shared<GameTexture>(renderer, 
                                                DATA_PATH "/client/resources/backgrounds/War2/Bright/War2.png");                                                    
    textures["background-war2-pale-war"] = std::make_shared<GameTexture>(renderer, 
                                                DATA_PATH "/client/resources/backgrounds/War2/Pale/War2.png");
    textures["background-war3-bright-war"] = std::make_shared<GameTexture>(renderer, 
                                                DATA_PATH "/client/resources/backgrounds/War3/Bright/War3.png");
    textures["background-war3-pale-war"] = std::make_shared<GameTexture>(renderer, 
                                                DATA_PATH "/client/resources/backgrounds/War3/Pale/War3.png");
    textures["background-war4-bright-war"] = std::make_shared<GameTexture>(renderer, 
                                                DATA_PATH "/client/resources/backgrounds/War4/Bright/War4.png");
    textures["background-war4-pale-war"] = std::make_shared<GameTexture>(renderer, 
                                                DATA_PATH "/client/resources/backgrounds/War4/Pale/War4.png");

    //load textures soldier 1
    textures["soldier1-walk"] = std::make_shared<GameTexture>(renderer, 
                                        DATA_PATH "/client/resources/Soldier_1/Walk.png");
    textures["soldier1-shot2"] = std::make_shared<GameTexture>(renderer, 
                                        DATA_PATH "/client/resources/Soldier_1/Shot_2.png");
    textures["soldier1-shot1"] = std::make_shared<GameTexture>(renderer, 
                                        DATA_PATH "/client/resources/Soldier_1/Shot_1.png");
    textures["soldier1-run"] = std::make_shared<GameTexture>(renderer, 
                                        DATA_PATH "/client/resources/Soldier_1/Run.png");
    textures["soldier1-recharge"] = std::make_shared<GameTexture>(renderer, 
                                        DATA_PATH "/client/resources/Soldier_1/Recharge.png");
    textures["soldier1-idle"] = std::make_shared<GameTexture>(renderer, 
                                        DATA_PATH "/client/resources/Soldier_1/Idle.png");
    textures["soldier1-hurt"] = std::make_shared<GameTexture>(renderer, 
                                        DATA_PATH "/client/resources/Soldier_1/Hurt.png");
    textures["soldier1-grenade"] = std::make_shared<GameTexture>(renderer, 
                                        DATA_PATH "/client/resources/Soldier_1/Grenade.png");
    textures["soldier1-explosion"] = std::make_shared<GameTexture>(renderer, 
                                        DATA_PATH "/client/resources/Soldier_1/Explosion.png");
    textures["soldier1-dead"] = std::make_shared<GameTexture>(renderer, 
                                        DATA_PATH "/client/resources/Soldier_1/Dead.png");
    textures["soldier1-attack"] = std::make_shared<GameTexture>(renderer, 
                                        DATA_PATH "/client/resources/Soldier_1/Attack.png");
}