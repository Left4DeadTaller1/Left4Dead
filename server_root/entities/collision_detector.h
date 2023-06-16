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
#include "infected.h"
#include "jumper.h"
#include "player.h"
#include "spear.h"
#include "venom.h"
#include "witch.h"
#include "zombie.h"

class CollisionDetector {
   public:
    CollisionDetector();
    ~CollisionDetector();

    bool isColliding(Entity& e1, int deltaX, int deltaY, Entity& e2);
    bool checkForCollisions(Entity& entity, int deltaX, int deltaY, std::vector<std::shared_ptr<Entity>>& entities);

    // Player's attacks
    std::list<std::shared_ptr<Entity>> shoot(Attack& attack, std::vector<std::shared_ptr<Entity>>& entities);

    // Zombie's attacks
    // TODO:change the MovementDirectionX to a FACING DIRECTION
    std::shared_ptr<Player>& getPlayersInRange(int attackRange, Attack& attack, std::vector<std::shared_ptr<Player>>& players);

   private:
    // for the player's attacks
    void shootZombie(const std::shared_ptr<Entity>& entity, Attack& attack, std::list<std::shared_ptr<Entity>>& entitiesBeingATK);

    // for the zombie's attacks
    void attackPlayers(int range, const std::shared_ptr<Player>& player, Attack& attack, std::list<std::shared_ptr<Player>>& playersInRange);
};

#endif  // COLLISION_DETECTOR_H
