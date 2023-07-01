#ifndef RENDERER_CONFIG_H
#define RENDERER_CONFIG_H

#include <yaml-cpp/yaml.h>

#include <map>
#include <string>
#include <vector>

class RendererConfig {
    private:
    std::map<std::string, int> dimensionsWindows;
    std::map<std::string, int> dimensionsLifeBar;
    std::map<std::string, int> renderParams;

    RendererConfig();
    RendererConfig(const RendererConfig&) = delete;
    void operator=(const RendererConfig&) = delete;
    
    public:
    static RendererConfig& getInstance();
    std::map<std::string, int>& getDimensionsWindows();
    std::map<std::string, int>& getDimensionsLifeBar();
    std::map<std::string, int>& getRenderParams();
};

#endif  // GAME_CONFIG_H
