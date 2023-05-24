#include "game_thread.h"
#define MAX_QUEUE_SIZE 16000

GameThread::GameThread()
    : game(), inputQueue(MAX_QUEUE_SIZE) {}

void GameThread::addPlayer() {
    std::string idPlayer = "Player" + std::to_string(playerQueues.size());
    game.addPlayer(idPlayer);
    playerQueues.emplace_back();  // create new queue for this player
}

Queue<Action>& GameThread::getInputQueue() {
    return inputQueue;
}

void GameThread::run() {
    while (true) {
        // game.update();
    }
}

void GameThread::startGame() {
    game.startGameLoop();
}

void GameThread::stop() {}

GameThread::~GameThread() {}
