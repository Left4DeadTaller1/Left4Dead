
#ifndef CLIENT_GAME_STATE_H_
#define CLIENT_GAME_STATE_H_

#include <map>
/*
1 byte message type
2 byte cant entidades

1 byte type player (0)

1 byte id player
1 byte general state
2 byte x
2 byte y
2 byte directio en x (a donde mira)
1 byte health

1 byte type zombie (1)

1 byte id zombie
1 byte general state
2 byte x
2 byte y
2 byte directio en x (a donde mira)
1 byte health
*/

typedef struct player player_t;
typedef struct infected infected_t;
typedef struct gameStateDTO gameStateDTO_t;

typedef enum state_t : uint8_t {
    WALKING,            //all
    RUNNING,            //all
    WALKING_SHOOTING,   //      soldier1
    RUNNING_SHOOTING,   //      soldier1
    SHOOTING,           //      soldier1
    RELOADING,          //      soldier1
    HURT,               //all
    DEAD,               //all    
    IDLE,               //all
    ATTACK,             //      soldier1
    ATTACK1,            //              jumper  spear   venom   witch   zombie
    ATTACK2,            //              jumper  spear   venom   witch   zombie
    ATTACK3,            //              jumper                  witch   zombie
    EATING,             //              jumper
    JUMP,               //              jumper          venom   witch   zombie
    FALL,               //                      spear
    PROTECT,            //                      spear
    RUN_AND_ATTACK,     //                      spear
    ATTACK1a,           //                              venom
    SCREAM,             //                                      witch
    BITE                //                                              zombie
};

/*typedef enum state_t : uint8_t {
    WALKING,        //all
    RUNNING,        //all
    IDLE,           //all
    DEAD,           //all
    HURT,           //all
    RELOADING,      //      soldier1
    SHOOTING,       //      soldier1
    ATTACK,         //      soldier1
    ATTACK1,        //              jumper  spear   venom   witch   zombie
    ATTACK2,        //              jumper  spear   venom   witch   zombie
    ATTACK3,        //              jumper                  witch   zombie
    EATING,         //              jumper
    JUMP,           //              jumper          venom   witch   zombie
    FALL,           //                      spear
    PROTECT,        //                      spear
    RUN_AND_ATTACK, //                      spear
    ATTACK1a,       //                              venom
    SCREAM,         //                                      witch
    BITE            //                                              zombie
};*/

typedef enum typeEntity_t : uint8_t {
    ZOMBIE,
    JUMPER,
    WITCH,
    SPEAR,
    VENOM,
    SOLDIER1,
    SOLDIER2,
    SOLDIER3
};

struct player {
    uint8_t idPlayer;
    state_t state;
    uint16_t x;
    uint16_t y;
    uint16_t lookingTo;
    uint8_t health;
    //uint8_t typePlayer;
};

struct infected {
    uint8_t idInfected;
    state_t state;
    uint16_t x;
    uint16_t y;
    uint8_t lookingTo;
    uint8_t health;
    typeEntity_t typeInfected; //pedirle a reg este dato
};

struct gameStateDTO {
    std::map<uint8_t, player_t> players;
    std::map<uint8_t, infected_t> infected;
};

#endif



