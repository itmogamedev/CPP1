#include <iostream>
#include <vector>
#include <string>

int main() {
    auto cur_strs_count{ // даем имя выражению
        [](char *ch, std::vector<std::string> *str_v_ptr) { // лямбда-выражение
            int n = 0;
            for (auto it = 0; it < (*str_v_ptr).size(); it++) {
                char ch_arr = (*str_v_ptr)[it][0];
                if (ch_arr == (*ch)) { n++; }
            }
            return n;

        }
    };

    char c1 = 'u';
    std::vector<std::string> strings_v = { "it's", "more", "than", "a", "university", ";", "universalia", "will", "be"};

    std::cout << cur_strs_count(&c1, &strings_v) << std::endl;

    return 0;
}
