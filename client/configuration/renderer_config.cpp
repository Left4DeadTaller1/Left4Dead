/*#include "renderer_config.h"

#include <iostream>

RendererConfig::RendererConfig() {
    try {
        std::string filename = BASE_PATH "client/configuration/configuration.yaml";

        YAML::Node config = YAML::LoadFile(filename);

        if (data["textures"] && data["textures"].IsSequence()) {
            YAML::Node textures = data["textures"];

            for (const auto& texture : textures) {
                if (texture.IsMap()) {
                    std::string name = texture["name"].as<std::string>();
                    std::string path = texture["path"].as<std::string>();
                    int frames = texture["frames"].as<int>();
                    texturesParams[name] = std::make_pair(path, frames);
                }
            }
            for (const auto& pair : texturesParams) {
                std::cout << "Name: " << pair.first << std::endl;
                std::cout << "Path: " << pair.second.first << std::endl;
                std::cout << "Frames: " << pair.second.second << std::endl;
                std::cout << std::endl;
            }
        }

        if (data["backgrounds"] && data["backgrounds"].IsSequence()) {
            YAML::Node backgrounds = data["backgrounds"];

            std::map<std::string, std::string> backgroundMap;

            for (const auto& background : backgrounds) {
                if (background.IsMap()) {
                    std::string name = background["name"].as<std::string>();
                    std::string path = background["path"].as<std::string>();
                    backgroundMap[name] = path;
                }
            }
            for (const auto& pair : backgroundMap) {
                std::cout << "Name: " << pair.first << std::endl;
                std::cout << "Path: " << pair.second << std::endl;
                std::cout << std::endl;
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
}*/
