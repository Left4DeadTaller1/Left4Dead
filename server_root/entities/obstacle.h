
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <string>

#include "entity.h"

class Obstacle : public Entity {
   public:
    Obstacle(int xPosition, int yPosition, std::string obstacleId, int height, int width);
    bool isAttackable() override;
    EntityType getType() override;
    bool isMoving();
    bool takeDamage(int amountOfDamage);
    void decreaseATKCooldown() override;
    bool checkIfDead();
    void kill();
    bool isDead();
    bool isRemovable();
    void idle();
    Attack generateAttack();
    void startMoving();
    std::tuple<int, int> getDirectionsAmount();
    bool canAttack();
};

#endif  // OBSTACLE_H