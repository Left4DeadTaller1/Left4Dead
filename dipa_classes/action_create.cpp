#include "action_create.h"

Create::Create(std::string scenario) : scenario(scenario) {}

actionDTO_t* Create::getDTO() const {
    CreateDTO_t* dto = new(CreateDTO_t);
    dto->scenario = scenario;

    actionDTO_t* dtoAction = new(actionDTO_t);
    dtoAction->type = CREATE;
    dtoAction->dto = (void*)dto;
    return dtoAction;
}

/*void Create::run(Game& game) {
    return;
};*/