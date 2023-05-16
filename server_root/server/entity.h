#ifndef ENTITY_H
#define ENTITY_H

class Entity {
   private:
    int x;
    int y;
    int width;
    int height;

   public:
    // this is just for colision testing in the future the width and the height
    //  will be determine by the type of the entity
    Entity(int xPosition, int yPosition, int width, int height);
    ~Entity();

    int getX();
    int getY();
    int getWidth();
    int getHeight();
};

#endif  // !ENTITY_H