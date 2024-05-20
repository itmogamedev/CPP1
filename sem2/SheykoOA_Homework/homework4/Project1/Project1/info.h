#pragma once

#include <vector>
#include <string>
#include <sstream>

class Info {
private:
    std::vector<std::pair<std::string, std::pair<int, int>>> values;

public:
    Info(const std::initializer_list<std::pair<std::string, std::pair<int, int>>>& list) : values(list) {}

    std::string getStr() {
        std::stringstream ss;
        for (auto& v : values) {
            ss << v.first << ": " << v.second.first << " / " << v.second.second << '\n' << '\n';
        }
        return ss.str();
    }
};
