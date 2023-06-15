#include "game_config.h"

#include <iostream>

GameConfig::GameConfig() {
    try {
        std::string filename = "/home/regman/taller/left4Dead/server_root/game/configuration/configuration.yaml";

        YAML::Node config = YAML::LoadFile(filename);

        if (config["mapFiles"]) {
            mapFiles = config["mapFiles"].as<std::vector<std::string>>();
        }

        if (config["gameParams"]) {
            // Load game dimensions
            if (config["gameParams"]["dimensions"]) {
                gameDimensions = config["gameParams"]["dimensions"].as<std::map<std::string, int>>();
            }

            // Load entities parameters
            if (config["gameParams"]["entities"]) {
                entitiesParams = config["gameParams"]["entities"].as<std::map<std::string, int>>();
            }

            // Load weapons parameters
            if (config["gameParams"]["weapons"]) {
                weaponsParams = config["gameParams"]["weapons"].as<std::map<std::string, int>>();
            }

            if (config["gameParams"]["spawns"]) {
                weaponsParams = config["gameParams"]["spawns"].as<std::map<std::string, int>>();
            }
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

std::map<std::string, int> GameConfig::getGameDimensions() const {
    return gameDimensions;
}

std::map<std::string, int> GameConfig::getEntitiesParams() const {
    return entitiesParams;
}

std::map<std::string, int> GameConfig::getWeaponsParams() const {
    return weaponsParams;
}
std::map<std::string, int> GameConfig::getSpawnsParams() const {
    return spawnsParams;
}
