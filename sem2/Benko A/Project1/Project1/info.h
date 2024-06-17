#pragma once

#include <vector>
#include <string>
#include <sstream>

class Info {
private:
    std::vector <std::pair <std::string, std::pair<int, int>  >>  values;
public:
    Info(const std::initializer_list<std::pair<std::string, std::pair<int, int>>>& l) : values(l) {}
    std::string getStr() 
    {
        std::stringstream strStm;
        for (auto& val : values) {
            strStm << val.first << ": " << val.second.first << " / " << val.second.second << '\n' << '\n';
        }
        return strStm.str();
    }
};