class ZombieSpawner {
   private:
    int spawnInterval;

   public:
    ZombieSpawner(int spawnInterval)
        : spawnInterval(spawnInterval) {}

    void spawn() {
        // Create new zombie with random properties
        // Add zombie to the game world
    }

    void update() {
        // Check if enough time has passed based on spawnInterval
        // If so, call spawn()
    }
};
