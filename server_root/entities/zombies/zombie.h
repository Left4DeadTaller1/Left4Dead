#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <map>
#include <string>
#include <vector>

#include "attack.h"
#include "entity.h"
#include "player.h"

// enum ActionState {
//     ATTACKING,
//     JUMPING,
//     SHOUTING,
//     IDLE,
// };

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
   protected:
    std::map<std::string, int> attacksCooldowns;
    int mutationLevel;

   public:
    // Constructor
    Zombie(int xPosition, int yPosition, std::string zombieId, int mutationLevel);
    void move();
    ~Zombie();

    EntityType getType() override;
    virtual std::shared_ptr<EntityDTO> getDto() = 0;
    void fillBaseZombieDTO(std::shared_ptr<ZombieDTO> dto);

    virtual void startMoving() = 0;

    void decideTarget(std::vector<std::shared_ptr<Player>> &players);

    void decreaseATKCooldown() override;

    std::tuple<int, int> getDirectionsAmount();

    // virtual int getAttackRange() = 0;

    virtual Attack attack() = 0;

    bool canAttack() override;  // added canAttack function declaration here
};

#endif  // ZOMBIE_H
