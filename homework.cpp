#include <vector>
#include <string>
#include <iostream>

using namespace std;

pair<vector<string>, int> starts_with_c(const vector<string>& v, char c) {
    vector<string> res;
    int count = 0;
    for (int i = 0; i < v.size(); i++) {
        if (!v[i].empty() and v[i][0] == c) {
            res.push_back(v[i]);
            count++;
        }
    }
    return make_pair(res, count);
}

int main() {
    vector<string> vec;
    char c;

    cout << "Введите букву для поиска: ";
    cin >> c;
    
    cin.ignore();

    cout << "Напишите ваш текст (для завершения напишите STOP):\n";
    string input_str;
    while (true) {
        getline(cin, input_str);
        if (input_str == "STOP") {
            break;
        }
        vec.push_back(input_str);
    }

    pair<vector<string>, int> result = starts_with_c(vec, c);
    cout << "Количество строк, начинающихся с '" << c << "': " << result.second << endl;

    return 0;
}
