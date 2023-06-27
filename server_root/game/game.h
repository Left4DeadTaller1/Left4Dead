#ifndef GAME_H_
#define GAME_H_

#include <list>
#include <queue>
#include <unordered_map>

#include "action.h"
#include "collision_detector.h"
#include "entity.h"
#include "player.h"
#include "queue.h"
#include "server_message.h"
#include "server_protocol.h"
#include "thread.h"
#include "zombie.h"
#include "zombie_spawner.h"

// TODO add craters where it needs to depending on the map
enum MapType {
    MAP1_BACKGROUND,
    MAP2_BACKGROUND,
    MAP3_BACKGROUND,
    MAP4_BACKGROUND,
    MAP5_BACKGROUND,
    MAP6_BACKGROUND,
    MAP7_BACKGROUND,
    MAP8_BACKGROUND,
};

class Game : public Thread {
    /*‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
    -------------------Api for clientCommunication------------------
    ________________________________________________________________*/
   private:
    // This is the big Queue where all the clients push their actions
    Queue<Action> inputQueue;
    // This is for managing the vector
    std::unordered_map<std::string, size_t> playerIdToQueueIndex;
    std::vector<Queue<std::shared_ptr<std::vector<uint8_t>>>*> playerQueues;
    int nextPlayerIndex;

   public:
    explicit Game(int mapType);
    void run() override;
    std::string addPlayer(Queue<std::shared_ptr<std::vector<uint8_t>>>& gameResponses, std::string nickName, int weaponType, int gameCode);
    void removePlayer(Queue<std::shared_ptr<std::vector<uint8_t>>>& gameResponses);
    Queue<Action>& getInputQueue();

    // Later add the API for the clients to push actions to the InputQueue
    void pushAction(Action action);

    void startGame();
    void sendAction(Action action);
    void stop();
    bool isGameRunning();
    bool hasGameStarted();
    bool hasActivePlayers();
    void closePlayerQueues();

    void killGame();

    ~Game();

    // Methods for Testing do not use in production
    std::vector<Queue<std::shared_ptr<std::vector<uint8_t>>>*>& _getPlayerQueues();

    /*‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
    -----------------------Api for Game-----------------------------
    ________________________________________________________________*/
   private:
    MapType mapBackground;
    bool gameRunning;
    bool gameStarted;
    CollisionDetector collisionDetector;
    std::unordered_map<std::string, std::queue<Action>>
        playersActions;
    std::vector<std::shared_ptr<Player>> players;
    // std::vector<std::shared_ptr<Zombie>> zombies;
    std::list<std::shared_ptr<Entity>> entities;
    ServerProtocol protocol;
    ZombieSpawner zombieSpawner;
    int framesCounter;
    int zombiesKilled;

    void
    spawnPlayer(std::string idPlayer, std::string playerNickname, int weaponType);
    void removePlayer(Player& playerToRemove);
    void updateState();
    bool updatePlayerState(Player& player, std::queue<Action>& playerActions);
    void move(Entity& entity);
    void attack(Entity& entity);
    void useSkill(Entity& entity);
    void performEntitySkill(Entity& entity);
    void getPlayersActions();
    void removeDeadEntities();
    void reloadPlayer(Player& player);
    void revivePlayer(Player& player);
    bool checkAfk(Player& player);
    void disconnectPlayer(Player& player);
    bool hasAlivePlayers(std::vector<std::shared_ptr<Player>> players);

    void sendState();
    std::vector<std::shared_ptr<EntityDTO>> getDtos();
    void sendScoreScreen();

   public:
    // Methods for Testing do not use in production
    const std::unordered_map<std::string, std::queue<Action>>& _getPlayersActions() const;
};

#endif  // GAME_H_
