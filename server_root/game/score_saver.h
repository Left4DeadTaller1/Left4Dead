#ifndef SCORE_SAVER_H_
#define SCORE_SAVER_H_
#include <yaml-cpp/yaml.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

class ScoreSaver {
   private:
    std::vector<std::tuple<std::string, int, int>> scores;

    void loadScores();
    void writeScores();

   public:
    ScoreSaver();
    ~ScoreSaver();
    void saveScore(const std::string& nickName, int score, int time);
    std::vector<std::tuple<std::string, int, int>> getScores();
};
#endif  // SCORE_SAVER_H_