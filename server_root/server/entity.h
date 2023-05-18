#ifndef ENTITY_H
#define ENTITY_H

class CollisionDetector;

// TODO make this a virtual class later on
class Entity {
   private:
    int x;
    int y;
    int width;
    int height;
    int health;

    friend class CollisionDetector;

   public:
    // this is just for colision testing in the future the width and the height
    //  will be determine by the type of the entity
    Entity(int xPosition, int yPosition, int width, int height);
    ~Entity();
};

#endif  // !ENTITY_H