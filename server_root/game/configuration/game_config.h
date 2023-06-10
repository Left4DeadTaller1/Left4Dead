#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <yaml-cpp/yaml.h>

#include <map>
#include <string>
#include <vector>

class GameConfig {
   public:
    static GameConfig& getInstance();

    std::vector<std::string> getMapFiles() const;
    std::map<std::string, int> getGameParams() const;

   private:
    std::vector<std::string> mapFiles;
    std::map<std::string, int> gameParams;

    GameConfig();
    GameConfig(const GameConfig&) = delete;
    void operator=(const GameConfig&) = delete;
};

#endif  // GAME_CONFIG_H
