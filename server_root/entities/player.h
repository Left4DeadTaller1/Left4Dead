#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>

class Player {
    private:
    int posx;
    int posy;

    public:
    Player(int posxInicial, int posyInicial);

    void move(int deltaX, int deltaY);
};

#endif //PLAYER_H_