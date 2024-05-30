#include "info.h"

Info::Info(float full, int maxFull, float hydr, int maxHydr, float clean, int maxClean)
{
    values.push_back(std::make_pair(full, maxFull));
    values.push_back(std::make_pair(hydr, maxHydr));
    values.push_back(std::make_pair(clean, maxClean));
}

std::string Info::getStr() const
{
    std::string str;
    for (const auto& value : values) {
        int filled = static_cast<int>((value.first / value.second) * 10);
        str += std::string(filled, '|') + std::string(10 - filled, '.') + "\t\t\t\t";
    }
    return str;
}
