
#include <vector>

#include "infected.h"
#include "jumper.h"
#include "spear.h"
#include "venom.h"
#include "witch.h"
#include "zombie.h"

struct SpawnPoint {
    int x;
    int y;
    bool witchAffected;
};

class ZombieSpawner {
   private:
    std::vector<SpawnPoint> spawnPoints;
    int spawnInterval;
    int totalZombies;
    int mutationLevel;

   public:
    ZombieSpawner();
    std::shared_ptr<Entity> spawn();
    int getTotalZombies();
    void increaseTotalZombies();
    void mutate();
};
