#include "score_saver.h"

ScoreSaver::ScoreSaver() {}

ScoreSaver::~ScoreSaver() {
    writeScores();
}

void ScoreSaver::writeScores() {
    // Sort the scores in descending order based on score
    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return std::get<1>(a) > std::get<1>(b);
    });

    // Keep only the top 5 scores
    if (scores.size() > 5) {
        scores.resize(5);
    }
    try {
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Scores";
        out << YAML::Value << YAML::BeginSeq;

        for (const auto& entry : scores) {
            out << YAML::BeginMap;
            out << YAML::Key << "Players" << YAML::Value << std::get<0>(entry);
            out << YAML::Key << "Score" << YAML::Value << std::get<1>(entry);
            out << YAML::Key << "time" << YAML::Value << std::get<2>(entry);
            out << YAML::EndMap;
        }

        out << YAML::EndSeq;
        out << YAML::EndMap;

        std::string filename = BASE_PATH "/server_root/game/scores.yaml";

        std::ofstream fout(filename);
        fout << out.c_str();
    } catch (const std::exception& e) {
        std::cerr << "Error writing scores: " << e.what() << std::endl;
    }
}

void ScoreSaver::saveScore(const std::string& nickName, int score, int time) {
    loadScores();
    scores.push_back(std::make_tuple(nickName, score, time));
    writeScores();
}

std::vector<std::tuple<std::string, int, int>> ScoreSaver::getScores() {
    if (scores.empty()) {
        try {
            std::string filename = BASE_PATH "/server_root/game/scores.yaml";
            YAML::Node config = YAML::LoadFile(filename);

            if (config["Scores"]) {
                for (const auto& entry : config["Scores"]) {
                    std::string players = entry["Players"].as<std::string>();
                    int score = entry["Score"].as<int>();
                    int time = entry["time"].as<int>();
                    scores.push_back(std::make_tuple(players, score, time));
                }
            }
        } catch (const YAML::Exception& ex) {
            std::cerr << "YAML Error: " << ex.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error loading configuration: " << e.what() << std::endl;
        }
    }

    return scores;
}

void ScoreSaver::loadScores() {
    try {
        std::string filename = BASE_PATH "/server_root/game/scores.yaml";
        YAML::Node config = YAML::LoadFile(filename);

        if (config["Scores"]) {
            for (const auto& entry : config["Scores"]) {
                std::string players = entry["Players"].as<std::string>();
                int score = entry["Score"].as<int>();
                int time = entry["time"].as<int>();
                scores.push_back(std::make_tuple(players, score, time));
            }
        }
    } catch (const YAML::Exception& ex) {
        std::cerr << "YAML Error: " << ex.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error loading configuration: " << e.what() << std::endl;
    }
}
