
#include <vector>

struct SpawnPoint {
    int x;
    int y;
};

class ZombieSpawner {
   private:
    std::vector<SpawnPoint> spawnPoints;
    int spawnInterval;
    int frameCounter;

   public:
    ZombieSpawner();

    void spawn();

    void update();
};
