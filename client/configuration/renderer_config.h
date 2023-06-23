/*#ifndef RENDERER_CONFIG_H
#define RENDERER_CONFIG_H

#include <yaml-cpp/yaml.h>

#include <map>
#include <string>
#include <vector>

class RendererConfig {
    private:
    std::vector<std::string> mapFiles;
    std::map<std::string, int> rendererDimensions;
    // Crear un std::map para almacenar los valores
    std::map<std::string, std::pair<std::string, int>> texturesParams;
    //std::map<std::string, int> soundsParams;

    RendererConfig();
    RendererConfig(const RendererConfig&) = delete;
    void operator=(const RendererConfig&) = delete;
    
    public:
    static RendererConfig& getInstance();

    std::vector<std::string> getMapFiles() const;
    std::map<std::string, int> getrendererDimensions() const;
    //std::map<std::string, int> getTexturesParams() const;
    //std::map<std::string, int> getSoundsParams() const;
};

#endif  // GAME_CONFIG_H*/
