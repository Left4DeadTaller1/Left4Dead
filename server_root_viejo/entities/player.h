#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>

#include "entity.h"

class Player : public Entity {
    private:
    void updatePosition();
    void updateState();

    public:
    Player(int idPlayer, int xPosition, int yPosition, int width, int height);

    virtual void startMove(int dirX, int dirY) override;

    virtual void endMove() override;

    virtual void update() override;
};

#endif  // PLAYER_H_