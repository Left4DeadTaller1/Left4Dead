#include "weapon.h"

Weapon::Weapon(WeaponType type)
    : type(type) {
    switch (type) {
        case SMG:
            maxBullets = SMG_MAX_BULLETS;
            bullets = SMG_MAX_BULLETS;
            cooldown = 0;
            break;

        case RIFLE:
            maxBullets = RIFLE_MAX_BULLETS;
            bullets = RIFLE_MAX_BULLETS;
            cooldown = 0;
            break;

        case SNIPER:
            maxBullets = SNIPER_MAX_BULLETS;
            bullets = SNIPER_MAX_BULLETS;
            cooldown = 0;
            break;
    }
}

Attack Weapon::shoot(int bulletXOrigin, int bulletDirection, int bulletLowerY, int bulletUpperY) {
    // TODO: think if the logic for if being able to shoot should be here
    switch (type) {
        case SMG:
            cooldown = SMG_COOLDOWN;
            bullets -= SMG_BULLETS_SHOT;

            return Attack(BULLET, SMG_DAMAGE, bulletXOrigin, bulletDirection, bulletLowerY, bulletLowerY + bulletUpperY);
            break;

        case RIFLE:
            cooldown = RIFLE_COOLDOWN;

            if (bullets - RIFLE_BULLETS_SHOT < 0)
                bullets = 0;
            else
                bullets -= RIFLE_BULLETS_SHOT;

            return Attack(BULLET, RIFLE_DAMAGE, bulletXOrigin, bulletDirection, bulletLowerY, bulletLowerY + bulletUpperY);
            break;
        case SNIPER:
            cooldown = SNIPER_COOLDOWN;
            bullets -= SNIPER_BULLETS_SHOT;
            return Attack(PIERCING_BULLET, SNIPER_DAMAGE, bulletXOrigin, bulletDirection, bulletLowerY, bulletLowerY + bulletUpperY);
            break;
        default:
            return Attack(BULLET, 0, 0, RIGHT, 0, 0);
            break;
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