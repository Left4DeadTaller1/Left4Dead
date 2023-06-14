#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <string>

#include "attack.h"

class CollisionDetector;

enum MovementState {
    ENTITY_WALKING,
    ENTITY_RUNNING,
    ENTITY_IDLE,
};

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

enum HealthState {
    ALIVE,
    HURT,
    DEAD,
    // TODO: add dying here
};

enum EntityType {
    PLAYER,
    ZOMBIE,
};

struct EntityDTO {
    EntityType type;
    std::string id;
    int x;
    int y;
    int health;
    int movementState;
    int movementDirectionX;
    int healthState;

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
    MovementState movementState;
    MovementDirectionX movementDirectionX;
    MovementDirectionY movementDirectionY;
    HealthState healthState;
    int movementSpeed;
    // TODO: think this better
    int framesHurt;

    friend class CollisionDetector;

   public:
    // this is just for colision testing in the future the width and the height
    //  will be determine by the type of the entity
    Entity(int xPosition, int yPosition, std::string id);
    MovementState getMovementState();
    MovementDirectionX getMovementDirectionX();
    MovementDirectionY getMovementDirectionY();
    HealthState getHealthState();
    void setHealthState(HealthState healthState);
    std::string getId();
    int getX();
    int getY();
    int getHealth();
    int getMovementSpeed();

    void takeDamage(int amountOfDamage);
    virtual void decreaseATKCooldown() = 0;

    virtual Attack attack() = 0;

    virtual EntityType getType() = 0;

    virtual std::shared_ptr<EntityDTO> getDto();

    void move(int deltaX, int deltaY);
    virtual bool canAttack() = 0;
    virtual ~Entity();
};

#endif  // !ENTITY_H