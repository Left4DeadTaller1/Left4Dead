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
    Attack shoot(int bulletXOrigin, int bulletDirection, int bulletLowerY, int bulletUpperY);
    void decreaseCooldown();
    bool canShoot();
    void reload();
};

#endif  // WEAPON_H