#pragma once
#include <iostream>
#include <fstream>
#include "Store.h"
#include "Dino.h"

class FileManager {
private:
    std::string lines;

public:

    std::string* getLines();
    void save(std::string file, Store* store);

    void load(std::string file);

    void parseLine(Store* store);
    Dino* stringToDino(std::string str, Store* store);
};
