#ifndef ACTION_RENDER_H_
#define ACTION_RENDER_H_

#include <vector>
#include <cstdint>

typedef enum {
    EXIT,
    MUTE,
    RESIZE,
    UNMUTE
} TypeAction_t;

class ActionRender {
    private:
    TypeAction_t type;
    uint32_t param1;
    uint32_t param2;

    public:
    ActionRender(TypeAction_t type, uint32_t param1, uint32_t param2);

    TypeAction_t typeAction(void);

    uint32_t getParam1(void);

    uint32_t getParam2(void);
};
#endif