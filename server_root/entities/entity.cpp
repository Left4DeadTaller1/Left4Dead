#include "entity.h"

Entity::Entity(int xPosition, int yPosition, int width, int height)
    : x(xPosition), y(yPosition), width(width), height(height), health(100) {
}

Entity::~Entity() {
}