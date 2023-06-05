#include "action_join.h"

Join::Join(int code) : code(code){}

actionDTO_t* Join::getDTO() const {
    JoinDTO_t* dto = new(JoinDTO_t);
    dto->code = code;

    actionDTO_t* dtoAction = new(actionDTO_t);
    dtoAction->type = JOIN;
    dtoAction->dto = (void*)dto;
    return dtoAction;
}

/*void Join::run(Game& game) {
    return;
}*/