#include "weapon.h"

#include <iostream>

#include "game_config.h"

Weapon::Weapon(WeaponType type)
    : type(type) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> weaponsParams = config.getWeaponsParams();
    cooldown = 0;

    switch (type) {
        case SMG:
            maxBullets = weaponsParams["SMG_MAX_BULLETS"];
            bullets = maxBullets;
            damage = weaponsParams["SMG_DAMAGE"];
            break;

        case RIFLE:
            maxBullets = weaponsParams["RIFLE_MAX_BULLETS"];
            bullets = maxBullets;
            damage = weaponsParams["RIFLE_DAMAGE"];
            break;

        case SNIPER:
            maxBullets = weaponsParams["SNIPER_MAX_BULLETS"];
            bullets = maxBullets;
            damage = weaponsParams["SNIPER_DAMAGE"];
            break;
    }
}

Attack Weapon::shoot(int bulletXOrigin, int bulletDirection, int bulletLowerY, int bulletUpperY) {
    GameConfig& config = GameConfig::getInstance();
    std::map<std::string, int> weaponsParams = config.getWeaponsParams();
    int bulletsShot = 0;

    switch (type) {
        case SMG:
            cooldown = weaponsParams["SMG_COOLDOWN"];
            bulletsShot = weaponsParams["SMG_BULLETS_SHOT"];
            break;

        case RIFLE:
            cooldown = weaponsParams["RIFLE_COOLDOWN"];
            bulletsShot = weaponsParams["RIFLE_BULLETS_SHOT"];
            break;

        case SNIPER:
            cooldown = weaponsParams["SNIPER_COOLDOWN"];
            bulletsShot = weaponsParams["SNIPER_BULLETS_SHOT"];
            break;

        default:
            return Attack(BULLET, 0, 0, RIGHT, 0, 0);
    }

    if (bullets - bulletsShot > 0)
        bullets -= bulletsShot;
    else
        bullets = 0;

    if (type == SNIPER) {
        return Attack(PIERCING_BULLET, damage, bulletXOrigin, bulletDirection, bulletLowerY, bulletLowerY + bulletUpperY);
    } else {
        return Attack(BULLET, damage, bulletXOrigin, bulletDirection, bulletLowerY, bulletLowerY + bulletUpperY);
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

int Weapon::getBullets() {
    return bullets;
}

Weapon::~Weapon() {
}