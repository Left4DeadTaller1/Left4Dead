#ifndef CLIENT_PLAYER_H
#define CLIENT_PLAYER_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <memory>
#include <map>
#include "client_game_state.h"
#include "renderer_config.h"
#include "../../../server_root/game/configuration/game_config.h"
#include "client_texture_manager.h"
#include "client_texture.h"
#include "client_sound_manager.h"
#include "client_lifeBar.h"

class ClientPlayer {
    private:
    state_t previousState;
    state_t currentState;
    int x;
    int y;
    int lookingTo;
    bool isDead;
    int counterDeath;
    TypeWeapon_t weapon;
    std::string nickname;
    int bullets;
    bool isMyWindow;
    LifeBar lifeBar;
    state_t currentSound;
    std::map<state_t, GameTexture>& texturesPlayer;
    std::map<state_t, std::shared_ptr<Sound>>& sounds;
    std::map<TypeWeapon_t, GameTexture>& texturesWeapon;

    uint32_t width;
    uint32_t height;
    uint32_t viewportWidth;
    uint32_t viewportHeight;
    uint32_t gameWidth;
    uint32_t gameHeight;

    int p90MaxBullets;
    int rifleMaxBullets;
    int sniperMaxBullets;

    GameTexture& getTexturePlayer(state_t state);
    GameTexture& getTextureWeapon(TypeWeapon_t weapon);
    int maxBullets(TypeWeapon_t type);

    void playSound(state_t state, int playMode);

    void stopSound(state_t state);
    void drawWeaponAndBullets(SDL2pp::Renderer& renderer);
    void drawNickname(SDL2pp::Renderer& renderer);
    std::string typeWeaponToString(TypeWeapon_t type);

    public:
    ClientPlayer(std::map<state_t, GameTexture>& textures,
                            std::map<state_t, std::shared_ptr<Sound>>& sounds,
                            std::map<TypeWeapon_t, GameTexture>& texturesWeapon,
                            bool isMyWindow,
                            player_t& currentPlayer,
                            GameTexture& textureLifeBar);

    bool isPlayerDead(void);
    void draw(SDL2pp::Renderer& renderer, int it);
    void updatePlayer(player_t& newCurrentPlayer);
    void updateSizeWindow(uint32_t newWidth, uint32_t newHeight);
};

#endif