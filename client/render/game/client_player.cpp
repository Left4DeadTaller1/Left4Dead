#include "client_player.h"

using namespace SDL2pp;
#define LOOPS_TO_ADVANCE_FRAME 5

ClientPlayer::ClientPlayer(std::map<state_t, GameTexture>& textures,
                            std::map<state_t, std::shared_ptr<Sound>>& sounds,
                            std::map<TypeWeapon_t, GameTexture>& texturesWeapon,
                            bool isMyWindow,
                            player_t& currentPlayer,
                            GameTexture& textureLifeBar) :
                            isMyWindow(isMyWindow),
                            lifeBar(textureLifeBar, currentPlayer.health, currentPlayer.x,
                            currentPlayer.y, currentPlayer.lookingTo, SOLDIER1),
                            texturesPlayer(textures),
                            sounds(sounds),
                            texturesWeapon(texturesWeapon),
                            counterDeath(0),
                            isDead(false),
                            currentSound(IDLE) {

    previousState = currentPlayer.state;
    currentState = currentPlayer.state;
    x = currentPlayer.x;
    y = currentPlayer.y;
    lookingTo = currentPlayer.lookingTo;
    weapon = currentPlayer.typeWeapon;
    nickname = currentPlayer.nickname;
    bullets = currentPlayer.bullets;

    RendererConfig& config = RendererConfig::getInstance();
    //ver si aca van referencias
    std::map<std::string, int>& dimensionsWindows = config.getDimensionsWindows();
    //std::map<std::string, int> dimensionsLifeBar = config.getDimensionsLifeBar();

    viewportWidth = dimensionsWindows["WINDOW_WIDTH"] + 2 * dimensionsWindows["IMAGE_BORDER_PADDING"];
    viewportHeight = dimensionsWindows["WINDOW_HEIGHT"];
    gameWidth = dimensionsWindows["GAME_WIDTH"];
    gameHeight = dimensionsWindows["GAME_HEIGHT"];
    width = dimensionsWindows["WINDOW_WIDTH"] / dimensionsWindows["CTE_DIVISION_WIDTH_ENTITY"];
    height = dimensionsWindows["WINDOW_HEIGHT"] / dimensionsWindows["CTE_DIVISION_HEIGHT_ENTITY"];

    GameConfig& configGame = GameConfig::getInstance();
    std::map<std::string, int> weaponParams = configGame.getWeaponsParams();

    p90MaxBullets = weaponParams["SMG_MAX_BULLETS"];
    rifleMaxBullets = weaponParams["RIFLE_MAX_BULLETS"];
    sniperMaxBullets = weaponParams["SNIPER_MAX_BULLETS"];
};

bool ClientPlayer::isPlayerDead(void){
    return isDead;
}

GameTexture& ClientPlayer::getTextureWeapon(TypeWeapon_t weapon){
    std::map<TypeWeapon_t, GameTexture>::iterator iter = texturesWeapon.find(weapon);
    if (iter == texturesWeapon.end()) {
        throw std::runtime_error("Error al cargar la textura");
    }
    return iter->second;
}

GameTexture& ClientPlayer::getTexturePlayer(state_t state){
    std::map<state_t, GameTexture>::iterator iter = texturesPlayer.find(state);
    if (iter == texturesPlayer.end()) {
        throw std::runtime_error("Error al cargar la textura");
    }
    return iter->second;
}

void ClientPlayer::playSound(state_t state, int playMode){
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

void ClientPlayer::stopSound(state_t state){
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
    (iter->second)->stop();   
}

void ClientPlayer::draw(SDL2pp::Renderer& renderer, int it){

    GameTexture& texture = getTexturePlayer(currentState);

    int frame = it % texture.n;
    if (currentState == DYING){
        counterDeath++;
    } else {
        counterDeath = 0;
    }
    if ((currentState == DYING) && counterDeath * LOOPS_TO_ADVANCE_FRAME > texture.n){
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

    drawNickname(renderer);

    if (isMyWindow){
        drawWeaponAndBullets(renderer);
    }

    if (currentState != currentSound && isMyWindow){
        stopSound(currentSound);
        if (!isDead){
            playSound(currentState, -1);
            currentSound = currentState;
        }
    }
    lifeBar.draw(renderer);
}

void ClientPlayer::updatePlayer(player_t& newCurrentPlayer){
    previousState = currentState;
    currentState = newCurrentPlayer.state;
    x = newCurrentPlayer.x;
    y = newCurrentPlayer.y;
    lookingTo = newCurrentPlayer.lookingTo;
    bullets = newCurrentPlayer.bullets;
    lifeBar.updateLifeBar(newCurrentPlayer.health, newCurrentPlayer.x, 
                    newCurrentPlayer.y, newCurrentPlayer.lookingTo);
}

void ClientPlayer::updateSizeWindow(uint32_t newWidth, uint32_t newHeight){
    RendererConfig& config = RendererConfig::getInstance();
    std::map<std::string, int> dimensionsWindows = config.getDimensionsWindows();

    viewportWidth = newWidth + 2 * dimensionsWindows["IMAGE_BORDER_PADDING"];
    viewportHeight = newHeight;
    width = newWidth/ dimensionsWindows["CTE_DIVISION_WIDTH_ENTITY"];
    height = newHeight / dimensionsWindows["CTE_DIVISION_HEIGHT_ENTITY"];

    lifeBar.updateSizeWindow(newWidth, newHeight);
}

std::string ClientPlayer::typeWeaponToString(TypeWeapon_t type){
    if (type == P90){
        return "P90";
    }
    if (type == RIFLE){
        return "Rifle";
    }
    if (type == SNIPER){
        return "Sniper";
    }
    return "";
}

int ClientPlayer::maxBullets(TypeWeapon_t type){
    if (type == P90){
        return p90MaxBullets;
    }
    if (type == RIFLE){
        return rifleMaxBullets;
    }
    if (type == SNIPER){
        return sniperMaxBullets;
    }
    return -1;
}

void ClientPlayer::drawWeaponAndBullets(SDL2pp::Renderer& renderer) {

    GameTexture& texture = getTextureWeapon(weapon);

    Rect dstRect(viewportWidth - texture.width + 20,
            10,
            texture.width - 100, 
            texture.height - 60);

    SDL_RenderCopyEx(renderer.Get(), texture.texture.Get(), nullptr, &dstRect, 0, nullptr, SDL_FLIP_HORIZONTAL);


    Font font(DATA_PATH "/client/render/resources/font/Roboto-MediumItalic.ttf", 24);

    std::string text = "Bullets: " + std::to_string(bullets) + "/" + std::to_string(maxBullets(weapon));
    
    Surface textSurface(font.RenderText_Solid(text.c_str(), SDL_Color{ 0, 0, 0}));
    Texture textTexture(renderer, textSurface);

    Rect textRect(viewportWidth - 250, texture.height - 30, textSurface.GetWidth(), textSurface.GetHeight());

    renderer.Copy(textTexture, NullOpt, textRect);

    std::string text2 = "Weapon: " + typeWeaponToString(weapon);

    Surface textSurface2(font.RenderText_Solid(text2.c_str(), SDL_Color{ 0, 0, 0}));
    Texture textTexture2(renderer, textSurface2);

    Rect textRect2(viewportWidth - 250, texture.height, textSurface2.GetWidth(), textSurface2.GetHeight());

    renderer.Copy(textTexture2, NullOpt, textRect2);
}

void ClientPlayer::drawNickname(SDL2pp::Renderer& renderer){
    Font font(DATA_PATH "/client/render/resources/font/Roboto-MediumItalic.ttf", 16);
    Surface textSurface2(font.RenderText_Solid(nickname.c_str(), SDL_Color{ 255, 255, 255}));
    Texture textTexture2(renderer, textSurface2);

    Rect textRect2((x * viewportWidth) / gameWidth + 60, 
                    viewportHeight - y - gameHeight + 30, 
                    textSurface2.GetWidth(), 
                    textSurface2.GetHeight());

    renderer.Copy(textTexture2, NullOpt, textRect2);    
}

