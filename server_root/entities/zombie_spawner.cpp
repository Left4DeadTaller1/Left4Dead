#include "zombie_spawner.h"

// TODO set the spawnInterval with config yaml
ZombieSpawner::ZombieSpawner() : spawnInterval(100), frameCounter(0) {}

void ZombieSpawner::update() {
    frameCounter++;
    if (frameCounter >= spawnInterval) {
        frameCounter = 0;
        spawn();
    }
}

void ZombieSpawner::spawn() {
    // TODO use prototpype pattern
}