#include "renderer_config.h"

#include <iostream>

RendererConfig::RendererConfig() {
    try {
        std::string filename = BASE_PATH "/client/configuration/configuration.yaml";

        YAML::Node config = YAML::LoadFile(filename);

        if (config["rendererParams"]) {
            if (config["rendererParams"]["dimensionsWindows"]) {
                dimensionsWindows = config["rendererParams"]["dimensionsWindows"].as<std::map<std::string, int>>();
            }

            if (config["rendererParams"]["dimensionsLifeBar"]) {
                dimensionsLifeBar = config["rendererParams"]["dimensionsLifeBar"].as<std::map<std::string, int>>();
            }

            if (config["rendererParams"]["renderParams"]) {
                renderParams = config["rendererParams"]["renderParams"].as<std::map<std::string, int>>();
            }
        }

    } catch (const YAML::Exception& ex) {
        std::cerr << "YAML Error: " << ex.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error loading configuration: " << e.what() << std::endl;
    }
}

RendererConfig& RendererConfig::getInstance() {
    static RendererConfig instance;
    return instance;
}

std::map<std::string, int>& RendererConfig::getDimensionsWindows() {
    return dimensionsWindows;
}

std::map<std::string, int>& RendererConfig::getDimensionsLifeBar() {
    return dimensionsLifeBar;
}

std::map<std::string, int>& RendererConfig::getRenderParams(){
    return renderParams;
}

