#ifndef GAME_THREAD_H_
#define GAME_THREAD_H_

#include "thread.h"

class GameThread : public Thread {
   private:
    // QUEUE<actions>
    // TODO: preguntar a fede si esto TIENE que ser un monitor? o con un mutex tamos
    // vector<queues><actions> clientsConnected(4) = [client1, ]
    // game Game;
    //  bool isInMenu;
    // vector<shot> flyingBullets;
   public:
    explicit GameThread();
    void run() override;

    // CreateGame();  //  Monitor de partida que llama al constructor de esta clase
    // joinGame();
    // startGame();
    // leaveGame();

    ~GameThread();
};

#endif  // GAME_THREAD_H_
