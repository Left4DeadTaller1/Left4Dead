#include "game.h"

Game::Game(int idGame, std::vector<Player*>& players) : idGame(idGame),
                                                        players(players){};

void Game::move(int deltaX, int deltaY, int idPlayer) {
    players[idPlayer]->move(deltaX, deltaY);
}
