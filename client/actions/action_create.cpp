#include "action_create.h"

Create::Create(std::string scenario) : scenario(scenario) {}

std::vector<int8_t> Create::serialize() const {
    std::vector<int8_t> data;
    data.push_back(CREATE);
    data.push_back(scenario.length());
    data.insert(data.end(), scenario.begin(), scenario.end());
    return data;
};
