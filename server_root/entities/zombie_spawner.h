
#include <vector>

#include "zombie.h"

struct SpawnPoint {
    int x;
    int y;
};

class ZombieSpawner {
   private:
    std::vector<SpawnPoint> spawnPoints;
    int spawnInterval;
    int totalZombies;

   public:
    ZombieSpawner();
    std::shared_ptr<Entity> spawn();
};
