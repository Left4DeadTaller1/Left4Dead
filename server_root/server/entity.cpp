#include "entity.h"

Entity::Entity(int xPosition, int yPosition, int width, int height) {
    this->x = xPosition;
    this->y = yPosition;
    this->width = width;
    this->height = height;
}

int Entity::getX() { return this->x; }
int Entity::getY() { return this->y; }
int Entity::getWidth() { return this->width; }
int Entity::getHeight() { return this->height; }

Entity::~Entity() {}