#ifndef ACTION_CLIENT_H_
#define ACTION_CLIENT_H_

//#include "../server_root/game/game.h"

typedef enum {
    CREATE,
    JOIN,
    START_GAME,
    START_MOVE,
    END_MOVE,
    START_SHOOT,
    END_SHOOT
} Type;

typedef struct actionDTO actionDTO_t;

struct actionDTO{
    Type type;
    void* dto; 
};

class ActionClient {
   public:
    ActionClient(void) {}

    //le voy a tener que hacer delete
    virtual actionDTO_t* getDTO() const = 0;

    //virtual void run(Game& game) = 0;

    virtual ~ActionClient() {}
};

#endif