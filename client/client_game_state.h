
#ifndef CLIENT_GAME_STATE_H_
#define CLIENT_GAME_STATE_H_

typedef struct entity entity_t;
typedef struct gameStateDTO gameStateDTO_t;

typedef enum {
    WALKING,
    RUNNING,
    RELOADING,
    SHOOTING,
    IDLE,
    DEAD,
    HURT,
} state_t;

struct entity {
    int idEntity;
    int8_t state;
    int x;
    int y;
    int health;
};

struct gameStateDTO {
    std::shared_ptr<std::vector<std::shared_ptr<entity_t>>> entities;
};

#endif



