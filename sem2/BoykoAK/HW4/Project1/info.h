#pragma once

#include <vector>
#include <string>
#include <stdarg.h>

class Info {
private:
	std::vector<std::pair<int, int>> values;

public:
	Info(int n, ...) {
        int result = 0;
        va_list f;         //указатель va_list
        va_start(f, n);    // устанавливаем указатель
        for (int i = 0; i < n; i+=2) {
            values.push_back(
                std::make_pair(va_arg(f, int), va_arg(f, int)));  // получаем значение текущего параметра типа int
        }
        va_end(f); // завершаем обработку параметров
	}

    std::string getStr() {
        std::string str = "";
        for (auto v: values) {
            str += std::to_string(v.first) + " / " +
                std::to_string(v.second) + '\t';
        }
        return str;
    }
};