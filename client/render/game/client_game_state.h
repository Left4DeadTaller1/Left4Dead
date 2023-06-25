
#ifndef CLIENT_GAME_STATE_H_
#define CLIENT_GAME_STATE_H_

#include <vector>

enum state_t : uint8_t {
    WALKING,            //all
    RUNNING,            //all
    WALKING_SHOOTING,   //      soldier1
    RUNNING_SHOOTING,   //      soldier1
    SHOOTING,           //      soldier1
    ATTACK,             //      soldier1
    JUMP,               //              jumper          venom   witch   zombie
    SCREAM,             //                                      witch
    RELOADING,          //      soldier1
    HURT,               //all
    DYING,              //all  
    DEAD,               //all    
    IDLE,               //all
    ATTACK1,            //              jumper  spear   venom   witch   zombie
    ATTACK2,            //              jumper  spear   venom   witch   zombie
    ATTACK3,            //              jumper                  witch   zombie
    EATING,             //              jumper
    FALL,               //                      spear
    PROTECT,            //                      spear
    RUN_AND_ATTACK,     //                      spear
    ATTACK1a,           //                              venom
    BITE                //                                              zombie
};

enum typeEntity_t : uint8_t {
    ZOMBIE,
    JUMPER,
    WITCH,
    SPEAR,
    VENOM,
    SOLDIER1,
    SOLDIER2,
    SOLDIER3
};


/*typedef struct player player_t;
typedef struct infected infected_t;
typedef struct gameStateDTO gameStateDTO_t;*/

typedef struct player {
    uint16_t idPlayer;
    state_t state;
    uint8_t actionCounter;
    uint16_t x;
    uint16_t y;
    uint8_t lookingTo;
    uint16_t health;
    //uint8_t typePlayer;
} player_t;

typedef struct infected {
    uint16_t idInfected;
    typeEntity_t typeInfected;
    state_t state;
    uint8_t actionCounter;
    uint16_t x;
    uint16_t y;
    uint8_t lookingTo;
    uint16_t health;
} infected_t;

typedef struct gameStateDTO {
    std::vector<player_t> players;
    std::vector<infected_t> infected;
} gameStateDTO_t;

#endif



