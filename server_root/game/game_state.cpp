#include "game_state.h"

GameState::GameState(int idGame, std::vector<Player*>& players): idGame(idGame),
                                                                players(players){};

void GameState::move(int deltaX, int deltaY, int idPlayer){
    players[idPlayer]->move(deltaX, deltaY);
}
