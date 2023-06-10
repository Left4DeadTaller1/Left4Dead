#ifndef ZOMBIE_H
#define ZOMBIE_H
#define ATK_COOLDOWN 10  // TODO think this in relation with fps game loop

#include <string>

#include "attack.h"
#include "entity.h"

enum ZombieType {
    INFECTED,
    JUMPER,
    WITCH,
    SPEAR,
    VENOM,
};

struct ZombieDTO : EntityDTO {
    ZombieType zombieType;
};

class Zombie : public Entity {
   private:
    ZombieType zombieType;

   public:
    // Constructor
    Zombie(int xPosition, int yPosition, int width, int height, std::string zombieId, ZombieType type);
    void move();
    ~Zombie();

    EntityType getType() override;
    ZombieType getZombieType();
    std::shared_ptr<EntityDTO> getDto() override;

    Attack attack() override;

    bool canAttack() override;  // added canAttack function declaration here
};

#endif  // ZOMBIE_H
