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
    P90,
    RIFLE,
    SNIPER
} TypeWeapon_t;

typedef enum : int8_t{
    WAR1_BRIGHT,
    WAR1_PALE,
    WAR2_BRIGHT,
    WAR2_PALE,
    WAR3_BRIGHT,
    WAR3_PALE,
    WAR4_BRIGHT,
    WAR4_PALE,
} TypeMap_t;

typedef enum {
    RIGHT,
    LEFT,
    UP,
    DOWN
} DirectionMove;

class ActionClient {
   public:
    //preguntas: devuelvo un puntero para no hacer una copia?
    virtual std::vector<int8_t> serialize() const = 0;

    virtual bool isExit(void) const = 0;

    virtual ~ActionClient() {}
};

#endif

