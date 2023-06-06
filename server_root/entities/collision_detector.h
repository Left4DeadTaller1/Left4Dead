/* Just to comment a little bit on the idea of why this is a class, i thought about 3 approaches:
  - Collision Detection in Entity Class:
   Add a method within Entity class that checks for collisions with other Entity objects, this
   is straightforward, but can become inefficient wwith many entities, as every entity would need to check for collisions with every other entity.

  Collision Detection in Game Class: we add a method for checking collisions in the Game class, this method would iterate through all Entity objects and check for collisions. But im afraid of
  game ending with too many responsabilities

  Collision Detection Class: Creating a separate CollisionDetector class. This class would have methods for checking for collisions between entities. keeping collision detection logic separate from the entity logic and game logic. So i went for this one.

*/

#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include <memory>
#include <vector>

#include "entity.h"
#include "player.h"
#include "shot.h"
#include "zombie.h"

class CollisionDetector {
   public:
    CollisionDetector();
    ~CollisionDetector();

    bool isColliding(Entity& e1, int deltaX, int deltaY, Entity& e2);
    bool checkForCollisions(Entity& entity, int deltaX, int deltaY, std::vector<std::shared_ptr<Entity>>& entities);
    std::vector<Entity*> getBeingShot(Shot& bullet, std::vector<Entity*>& entities);
};

#endif  // COLLISION_DETECTOR_H
