#ifndef WEAPON_H
#define WEAPON_H

#include "attack.h"

enum WeaponType {
    SMG,
    RIFLE,
    SNIPER
};

class Weapon {
   private:
    WeaponType type;
    int maxBullets;
    int bullets;
    int damage;
    int cooldown;

   public:
    Weapon(WeaponType type);
    ~Weapon();
    WeaponType getType();
    Attack shoot(int bulletXOrigin, int bulletDirection, int bulletLowerY, int bulletUpperY);
    int getDamageFalloff();
    void decreaseCooldown();
    int getCooldown();
    bool canShoot();
    void reload();
    int getBullets();
};

#endif  // WEAPON_H