#include "weapon.h"

#include "game_config.h"

Weapon::Weapon(WeaponType type)
    : type(type) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> gameParams = config.getGameParams();

    switch (type) {
        case SMG:
            maxBullets = gameParams["SMG_MAX_BULLETS"];
            bullets = maxBullets;
            cooldown = 0;
            damage = gameParams["SMG_DAMAGE"];
            break;

        case RIFLE:
            maxBullets = gameParams["RIFLE_MAX_BULLETS"];
            bullets = maxBullets;
            cooldown = 0;
            damage = gameParams["RIFLE_DAMAGE"];
            break;

        case SNIPER:
            maxBullets = gameParams["SNIPER_MAX_BULLETS"];
            bullets = maxBullets;
            cooldown = 0;
            damage = gameParams["SNIPER_DAMAGE"];
            break;
    }
}

Attack Weapon::shoot(int bulletXOrigin, int bulletDirection, int bulletLowerY, int bulletUpperY) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> gameParams = config.getGameParams();

    switch (type) {
        case SMG:
            cooldown = gameParams["SMG_COOLDOWN"];
            bullets -= gameParams["SMG_BULLETS_SHOT"];
            return Attack(BULLET, damage, bulletXOrigin, bulletDirection, bulletLowerY, bulletLowerY + bulletUpperY);

        case RIFLE: {
            cooldown = gameParams["RIFLE_COOLDOWN"];
            int rifleBulletsShot = gameParams["RIFLE_BULLETS_SHOT"];
            if (bullets - rifleBulletsShot < 0)
                bullets = 0;
            else
                bullets -= rifleBulletsShot;
            return Attack(BULLET, damage, bulletXOrigin, bulletDirection, bulletLowerY, bulletLowerY + bulletUpperY);
        }

        case SNIPER:
            cooldown = gameParams["SNIPER_COOLDOWN"];
            bullets -= gameParams["SNIPER_BULLETS_SHOT"];
            return Attack(PIERCING_BULLET, damage, bulletXOrigin, bulletDirection, bulletLowerY, bulletLowerY + bulletUpperY);

        default:
            return Attack(BULLET, 0, 0, RIGHT, 0, 0);
    }
}

bool Weapon::canShoot() {
    if (bullets > 0 && cooldown == 0)
        return true;
    else
        return false;
}

void Weapon::decreaseCooldown() {
    if (cooldown > 0)
        cooldown--;
}

void Weapon::reload() {
    bullets = maxBullets;
}

Weapon::~Weapon() {
}