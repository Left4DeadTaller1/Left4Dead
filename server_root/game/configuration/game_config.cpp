#include "game_config.h"

#include <iostream>

GameConfig::GameConfig() {
    try {
        // TODO figure out how to not use absolute path
        std::string filename = "/home/regman/taller/left4Dead/server_root/game/configuration/configuration.yaml";

        YAML::Node config = YAML::LoadFile(filename);

        if (config["mapFiles"]) {
            mapFiles = config["mapFiles"].as<std::vector<std::string>>();
        }

        if (config["gameParams"]) {
            gameParams = config["gameParams"].as<std::map<std::string, int>>();
        }
    } catch (const YAML::Exception& ex) {
        std::cerr << "YAML Error: " << ex.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error loading configuration: " << e.what() << std::endl;
    }
}

GameConfig& GameConfig::getInstance() {
    static GameConfig instance;
    return instance;
}

std::vector<std::string> GameConfig::getMapFiles() const {
    return mapFiles;
}

std::map<std::string, int> GameConfig::getGameParams() const {
    return gameParams;
}
