#pragma once

#include <vector>
#include <string>
#include <stdarg.h>

class Info {
private:
    std::vector<std::pair<int, int>> values;

public:
    Info(int n, ...) {
        va_list args;
        va_start(args, n);
        for (int i = 0; i < n; i += 2) {
            values.push_back(std::make_pair(va_arg(args, int), va_arg(args, int)));
        }
        va_end(args);
    }

    std::string getStr() {
        std::string str;
        for (auto v : values) {
            str += std::to_string(v.first) + " / " + std::to_string(v.second) + '\t';
        }
        return str;
    }
};