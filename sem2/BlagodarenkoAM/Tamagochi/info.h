#pragma once

#include <vector>
#include <string>
#include <cstdarg>

class Info {
private:
    std::vector<std::pair<float, int>> values;

public:
    Info(float full, int maxFull, float hydr, int maxHydr, float clean, int maxClean);

    std::string getStr() const;
};


