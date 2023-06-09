#ifndef ACTION_CLIENT_H_
#define ACTION_CLIENT_H_

#include <vector>
#include <cstdint>

typedef enum {
    CREATE,
    JOIN,
    START_GAME,
    START_MOVE,
    END_MOVE,
    START_SHOOT,
    END_SHOOT,
    RECHARGE
} Type;

typedef enum {
    WALK,
    RUN
} TypeMove;

typedef enum {
    RIGHT,
    LEFT,
    UP,
    DOWN
} DirectionMove;

class ActionClient {
   public:
    ActionClient(void) {}

    //preguntas: devuelvo un puntero para no hacer una copia?
    virtual std::vector<int8_t> serialize() const = 0;

    virtual ~ActionClient() {}
};

#endif

