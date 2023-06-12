class ZombieSpawner {
   private:
    int spawnInterval;
    int frameCounter;

   public:
    ZombieSpawner();

    void spawn();

    void update();
};
