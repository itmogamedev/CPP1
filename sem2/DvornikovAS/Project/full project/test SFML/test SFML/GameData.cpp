#include "GameData.h"

void GameData::saveDataToFile(const std::string& filename) {
    std::remove("data.txt");
    std::ofstream file(filename, std::ios::trunc);
    if (file.is_open()) {
        file << bal << std::endl;
        for (int i = 0; i < status.size(); i++) {
            bool s = status.at(i);
            file << s << std::endl;
        }
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

void GameData::loadDataFromFile(const std::string& filename) {
    std::ifstream file(filename);
    status.clear();
    if (file.is_open()) {
        file >> bal;
        for (int i = 0; i < 4; i++) {
            bool s;
            file >> s;
            status.push_back(s);
        }
    }
    else {
        std::cerr << "File not found: " << filename << std::endl;
    }
}

int GameData::getBalance() { return bal; }

void GameData::setBalance(int b) { bal = b; }

std::vector <bool> GameData::getStatus() { return status; }

void GameData::setStatus(std::vector<bool> s) { status = s; }
