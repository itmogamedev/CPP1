#pragma once

#include <vector>
#include <string>
#include <cstdarg>

class Info {
private:
    std::vector<std::pair<float, int>> values;

public:
    Info(float full, int maxFull, float hydr, int maxHydr, float clean, int maxClean) {
        values.push_back(std::make_pair(full, maxFull));
        values.push_back(std::make_pair(hydr, maxHydr));
        values.push_back(std::make_pair(clean, maxClean));
    }

    std::string getStr() const {
        std::string str;
        for (const auto& value : values) {
            int filled = static_cast<int>((value.first / value.second) * 10);
            str += std::string(filled, '|') + std::string(10 - filled, '.') + '\t';
        }
        return str;
    }
};


