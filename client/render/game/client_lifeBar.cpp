#include "client_lifeBar.h"

LifeBar::LifeBar(GameTexture& texture, uint32_t health, 
            uint32_t x, uint32_t y, uint8_t lookingTo, 
            typeEntity_t typeEntity) : 
                texture(texture),
                health(health), x(x), y(y),
                lookingTo(lookingTo),
                typeEntity(typeEntity) {

    RendererConfig& config = RendererConfig::getInstance();
    std::map<std::string, int>& dimensionsWindows = config.getDimensionsWindows();
    std::map<std::string, int>& dimensionsLifeBar = config.getDimensionsLifeBar();

    viewportWidth = dimensionsWindows["WINDOW_WIDTH"] + 2 * dimensionsWindows["IMAGE_BORDER_PADDING"];
    viewportHeight = dimensionsWindows["WINDOW_HEIGHT"];
    gameWidth = dimensionsWindows["GAME_WIDTH"];
    gameHeight = dimensionsWindows["GAME_HEIGHT"];
    padding = dimensionsWindows["IMAGE_BORDER_PADDING"];

    width = dimensionsLifeBar["LIFE_BAR_WIDTH"];
    height = dimensionsLifeBar["LIFE_BAR_HEIGHT"];
    distXToEntityLookingLeft = dimensionsLifeBar["DIST_X_LIFE_BAR_TO_ENTITY_LOOKING_LEFT"];
    distXToEntityLookingRight = dimensionsLifeBar["DIST_X_LIFE_BAR_TO_ENTITY_LOOKING_RIGHT"];
    distYToEntity = dimensionsLifeBar["DIST_Y_LIFE_BAR_TO_ENTITY"];

    lifeLevels = dimensionsLifeBar["LIFE_LEVELS_SOLDIER"];

    GameConfig& configGame = GameConfig::getInstance();
    std::map<std::string, int> entityParams = configGame.getEntitiesParams();

    maxHealth = getMaxHealth(entityParams, typeEntity);
};

int LifeBar::getMaxHealth(std::map<std::string, int>& entityParams, typeEntity_t typeEntity){
    switch (typeEntity) {
        case ZOMBIE:
            return entityParams["INFECTED_HEALTH"];
        case JUMPER:
            return entityParams["JUMPER_HEALTH"];
        case WITCH:
            return entityParams["WITCH_HEALTH"];
        case SPEAR:
            return entityParams["SPEAR_HEALTH"];
        case VENOM:
            return entityParams["VENOM_HEALTH"];
        case SOLDIER1:
            return entityParams["PLAYER_HEALTH"];
        default:
            return 100;
    }
}

void LifeBar::draw(SDL2pp::Renderer& renderer){
    SDL_Rect srcRect;
    srcRect.x = (texture.width / texture.n)* ((maxHealth - health) / lifeLevels);
    srcRect.y = 0;
    srcRect.w = texture.width / texture.n;
    srcRect.h = texture.height;

    SDL_Rect dstRect;
    if (lookingTo == 0) {
        dstRect.x = ((x * viewportWidth) / gameWidth) + distXToEntityLookingLeft;
    } else {
        dstRect.x = ((x * viewportWidth) / gameWidth) + distXToEntityLookingRight;
    }
    dstRect.y = (viewportHeight - y - gameHeight) + distYToEntity;
    dstRect.w = width;
    dstRect.h = height;

    if (lookingTo == ENTITY_LOOKING_LEFT) {
        SDL_RenderCopyEx(renderer.Get(), texture.texture.Get(), &srcRect, &dstRect, 0, nullptr, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_RenderCopyEx(renderer.Get(), texture.texture.Get(), &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
    }
}

void LifeBar::updateLifeBar(uint32_t health, uint32_t x, 
                                uint32_t y, uint8_t lookingTo){
    this->health = health;
    this->x = x;
    this->y = y;
    this->lookingTo = lookingTo;
}

void LifeBar::updateSizeWindow(uint32_t newWidth, uint32_t newHeight){
    viewportWidth = newWidth + 2 * padding;
    viewportHeight = newHeight;
}