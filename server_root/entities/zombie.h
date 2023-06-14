#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <map>
#include <string>
#include <vector>

#include "attack.h"
#include "entity.h"
#include "player.h"

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
    std::map<std::string, int> attacksCooldowns;

   public:
    // Constructor
    Zombie(int xPosition, int yPosition, std::string zombieId, ZombieType type);
    void move();
    ~Zombie();

    EntityType getType() override;
    ZombieType getZombieType();
    std::shared_ptr<EntityDTO> getDto() override;

    void decideTarget(std::vector<std::shared_ptr<Player>> &players);

    void decreaseATKCooldown() override;

    int getAttackRange();

    Attack attack() override;

    bool canAttack() override;  // added canAttack function declaration here
};

#endif  // ZOMBIE_H
