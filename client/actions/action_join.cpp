#include "action_join.h"

Join::Join(int8_t code) : code(code){}

std::vector<int8_t> Join::serialize() const {
    std::vector<int8_t> data = {JOIN, code};
    return data;
};

bool Join::isExit(void) const {
    return false;
}