#pragma once

#include <vector>
#include <string>
#include <stdarg.h>

class Info {
private:
    std::vector<std::pair<int, int>> values;

public:
    Info(int n, ...) {
        va_list f;
        va_start(f, n);
        for (int i = 0; i < n; i += 2) {
            values.push_back(std::make_pair(va_arg(f, int), va_arg(f, int)));
        }
        va_end(f);
    }

    std::string getStr() const {
        std::string str;
        for (const auto& v : values) {
            str += std::to_string(v.first) + " / " + std::to_string(v.second) + '\t';
        }
        return str;
    }
};
