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

#include <list>
#include <memory>
#include <vector>

#include "attack.h"
#include "entity.h"
#include "player.h"
#include "zombie.h"

class CollisionDetector {
   public:
    CollisionDetector();
    ~CollisionDetector();

    bool isColliding(Entity& e1, int deltaX, int deltaY, Entity& e2);
    bool checkForCollisions(Entity& entity, int deltaX, int deltaY, std::vector<std::shared_ptr<Entity>>& entities);

    std::list<std::shared_ptr<Entity>> beingAttack(Attack& attack, std::vector<std::shared_ptr<Entity>>& entities);

    void beingAttackInfiniteRange(const std::shared_ptr<Entity>& entity, Attack& attack, std::list<std::shared_ptr<Entity>>& entitiesBeingATK);

    void beingAttackFiniteRange(int range, const std::shared_ptr<Entity>& entity, Attack& attack, std::list<std::shared_ptr<Entity>>& entitiesBeingATK);
};

#endif  // COLLISION_DETECTOR_H
