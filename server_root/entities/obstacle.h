
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <string>

#include "entity.h"

class Obstacle : public Entity {
   public:
    Obstacle(int xPosition, int yPosition, std::string obstacleId);
    bool isAttackable() override;
    EntityType getType() override;

   private:
};

#endif  // OBSTACLE_H