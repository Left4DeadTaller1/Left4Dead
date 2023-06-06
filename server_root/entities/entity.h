#ifndef ENTITY_H
#define ENTITY_H

#include <string>

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
    DEAD
};

// TODO make this a virtual class later on
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

    friend class CollisionDetector;

   public:
    // this is just for colision testing in the future the width and the height
    //  will be determine by the type of the entity
    Entity(int xPosition, int yPosition, int width, int height, std::string id);
    MovementState getMovementState();
    MovementDirectionX getMovementDirectionX();
    MovementDirectionY getMovementDirectionY();
    HealthState getHealthState();
    std::string getId();
    int getX();
    int getY();
    int getHealth();
    int getMovementSpeed();

    void setMovementState(MovementState movementState);
    void setMovementDirectionX(MovementDirectionX movementDirectionX);
    void setMovementDirectionY(MovementDirectionY movementDirectionY);

    virtual std::string getType() = 0;

    void move(int deltaX, int deltaY);
    virtual ~Entity();
};

#endif  // !ENTITY_H