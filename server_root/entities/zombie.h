#ifndef ZOMBIE_H
#define ZOMBIE_H
#define ATK_COOLDOWN 10  // TODO think this in relation with fps game loop

#include <string>

#include "entity.h"

struct ZombieDTO : EntityDTO {
};

class Zombie : public Entity {
   private:
   public:
    // Constructor
    Zombie(int xPosition, int yPosition, int width, int height, std::string zombieId);
    void move();
    ~Zombie();

    EntityType getType() override;
    std::shared_ptr<EntityDTO> getDto() override;

    bool canAttack() override;  // added canAttack function declaration here
};

#endif  // ZOMBIE_H
