#include <yaml-cpp/yaml.h>

#include <fstream>
#include <iostream>

class ServerConfig {
   public:
    int port;
    std::vector<std::string> mapFiles;
    std::map<std::string, int> gameParams;

    // Podría ser útil permitir que la ruta del archivo se especifique como un argumento de línea
    //  de comandos, para que puedas cambiar fácilmente la configuración sin tener que recompilar
    //  el código
    ServerConfig() {
        std::string filename = "server/configuration.yaml";
        YAML::Node config = YAML::LoadFile(filename);

        port = config["port"].as<int>();
        mapFiles = config["mapFiles"].as<std::vector<std::string>>();
        gameParams = config["gameParams"].as<std::map<std::string, int>>();
    }
};