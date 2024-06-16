#pragma once

#include <vector>
#include <string>
#include <stdarg.h>
#include "cat.h"

class Info {
private:
	std::vector<std::pair<int, int>> values;
    Pet* cat_;

public:
    Info(Pet* cat) { cat_ = cat; }

    std::string getStr() {
        std::string str = "";
        for (auto v: values) {
            str += std::to_string(v.first) + " / " +
                std::to_string(v.second) + '\t';
        }
        return str;
    }

    void update();
};

void Info::update()
{
    values.clear();
    
    values.push_back(std::make_pair(cat_->getSize(), cat_->getMaxSize()));
    values.push_back(std::make_pair(cat_->getFull(), cat_->getMaxFull()));
    values.push_back(std::make_pair(cat_->getHydr(), cat_->getMaxHydr()));
    values.push_back(std::make_pair(cat_->getClean(), cat_->getMaxClean()));
}