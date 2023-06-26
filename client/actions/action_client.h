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
    RECHARGE,
} Type;

typedef enum : int8_t{
    WALK,
    RUN
} TypeMove;

typedef enum : int8_t{
    WEAPON1,
    WEAPON2,
    WEAPON3
} TypeWeapon_t;

typedef enum : int8_t{
    MAP1,
    MAP2,
    MAP3,
    MAP4
} TypeMap_t;

typedef enum {
    RIGHT,
    LEFT,
    UP,
    DOWN
} DirectionMove;

class ActionClient {
   public:
    //ActionClient(void) {}

    //preguntas: devuelvo un puntero para no hacer una copia?
    virtual std::vector<int8_t> serialize() const = 0;

    virtual bool isExit(void) const = 0;

    virtual ~ActionClient() {}
};

#endif

