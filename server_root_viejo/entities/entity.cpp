#include "entity.h"
#include <iostream>

Entity::Entity(int idEntity, int xPosition, int yPosition, int width, int height)
    : idEntity(idEntity), state(IDLE), x(xPosition), y(yPosition), width(width), height(height), health(100),
    dirX(0), dirY(0){
}

//void Entity::move(int dirX, int dirY) {}

//retorno una copia, despues retornar puntero inteligente?
void Entity::getEntityDTO(std::shared_ptr<entity_t>* entity){
    (*entity)->idEntity = idEntity;
    (*entity)->state = state;
    (*entity)->x = x;
    (*entity)->y = y;
    (*entity)->health = health;
}

Entity::~Entity() {
}
