#ifndef WEAPON_H
#define WEAPON_H

#include "attack.h"

// TODO define those later on
#define SMG_DAMAGE 10
#define RIFLE_DAMAGE 20
#define SNIPER_DAMAGE 50

// TODO define those later on
#define SMG_COOLDOWN 10
#define RIFLE_COOLDOWN 30
#define SNIPER_COOLDOWN 50

#define SMG_MAX_BULLETS 30
#define RIFLE_MAX_BULLETS 50
#define SNIPER_MAX_BULLETS 20

#define SMG_BULLETS_SHOT 10
#define RIFLE_BULLETS_SHOT 20
#define SNIPER_BULLETS_SHOT 1

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