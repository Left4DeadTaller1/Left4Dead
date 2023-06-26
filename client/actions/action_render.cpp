#include "action_render.h"

ActionRender::ActionRender(TypeAction_t type, uint32_t param1, uint32_t param2): 
                                                type(type),
                                                param1(param1),
                                                param2(param2){}


TypeAction_t ActionRender::typeAction(void){
    return type;
}

uint32_t ActionRender::getParam1(void){
    return param1;
}

uint32_t ActionRender::getParam2(void){
    return param2;
}
