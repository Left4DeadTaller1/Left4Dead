#ifndef ENTITY_H
#define ENTITY_H

#include <memory>

class CollisionDetector;

typedef enum {
    WALKING,
    RUNNING,
    RELOADING,
    SHOOTING,
    IDLE,
    DEAD,
    HURT,
} state_t;

typedef struct entity {
    int idEntity;
    state_t state;
    int x;
    int y;
    int health;
} entity_t;

// TODO make this a virtual class later on
class Entity {
   protected:
    int idEntity;
    state_t state;
    int x;
    int y;
    int width;
    int height;
    int health;

    int dirX;
    int dirY;

    //int shooting;
    //int reloading;

    friend class CollisionDetector;

    virtual void updatePosition() = 0;
    virtual void updateState() = 0;

   public:
    // this is just for colision testing in the future the width and the height
    //  will be determine by the type of the entity
    Entity(int idEntity, int xPosition, int yPosition, int width, int height);

    //virtual void move(int dirX, int dirY) = 0;
    virtual void startMove(int dirX, int dirY) = 0;

    virtual void endMove() = 0;

    virtual void update() = 0;

    void getEntityDTO(std::shared_ptr<entity_t>* entity);
    
    ~Entity();
};

#endif  // !ENTITY_H