#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <string>
#include <tuple>

#include "attack.h"

class CollisionDetector;

enum MovementDirectionX {
    ENTITY_LEFT,
    ENTITY_RIGHT,
    ENTITY_NONE_X,
};

enum MovementDirectionY {
    ENTITY_UP,
    ENTITY_DOWN,
    ENTITY_NONE_Y,
};

enum EntityType {
    PLAYER,
    ZOMBIE,
};

enum FacingDirection {
    FACING_LEFT,
    FACING_RIGHT,
};

struct EntityDTO {
    EntityType type;
    std::string id;
    int x;
    int y;
    int health;
    // TODO check if i need this field
    int movementDirectionX;
    FacingDirection facingDirection;
    int actionCounter;

    virtual ~EntityDTO() = default;
};

class Entity {
   protected:
    int x;
    int y;
    int width;
    int height;
    int health;
    std::string entityId;
    MovementDirectionX movementDirectionX;
    MovementDirectionY movementDirectionY;
    FacingDirection facingDirection;
    int movementSpeed;
    // TODO: remove this
    int actionCounter;

    friend class CollisionDetector;

   public:
    // this is just for colision testing in the future the width and the height
    //  will be determine by the type of the entity
    Entity(int xPosition, int yPosition, std::string id);
    MovementDirectionX getMovementDirectionX();
    MovementDirectionY getMovementDirectionY();
    std::string getId();
    int getX();
    int getY();
    int getHealth();
    int getMovementSpeed();
    int getActionCounter();
    void decreaseActionCounter();

    virtual bool isMoving() = 0;
    virtual void takeDamage(int amountOfDamage) = 0;
    virtual void decreaseATKCooldown() = 0;
    virtual bool checkIfDead() = 0;
    virtual void kill() = 0;
    virtual bool isDead() = 0;
    virtual bool isRemovable() = 0;
    virtual void idle() = 0;

    virtual Attack attack() = 0;

    virtual EntityType getType() = 0;

    virtual std::shared_ptr<EntityDTO> getDto();
    virtual std::tuple<int, int> getDirectionsAmount() = 0;

    void move(int deltaX, int deltaY);
    virtual bool canAttack() = 0;
    virtual ~Entity();
};

#endif  // !ENTITY_H