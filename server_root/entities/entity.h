#ifndef ENTITY_H
#define ENTITY_H

class CollisionDetector;

enum MovementState {
    WALKING,
    RUNNING,
    ENTITY_IDLE
};

enum MovementDirectionX {
    LEFT,
    RIGHT,
    NONE_X
};

enum MovementDirectionY {
    UP,
    DOWN,
    NONE_Y
};

// TODO make this a virtual class later on
class Entity {
   protected:
    int x;
    int y;
    int width;
    int height;
    int health;
    MovementState movementState;
    MovementDirectionX movementDirectionX;
    MovementDirectionY movementDirectionY;

    friend class CollisionDetector;

   public:
    // this is just for colision testing in the future the width and the height
    //  will be determine by the type of the entity
    Entity(int xPosition, int yPosition, int width, int height);
    MovementState getMovementState();
    MovementDirectionX getMovementDirectionX();
    MovementDirectionY getMovementDirectionY();
    int getMovementSpeed();
    void move(int deltaX, int deltaY);
    virtual ~Entity();
};

#endif  // !ENTITY_H