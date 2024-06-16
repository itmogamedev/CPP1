#include "FileManager.h"
#include <string>


std::string* FileManager::getLines()
{
    return &lines;
}

void FileManager::save(std::string file, Store* store)
{
    std::ofstream out;
    out.open(file);

    if (out.is_open())
    {
        out << store->getBudget() << ";";

        std::vector<Dino*>* dinosPtr = store->collection.getDinos();
        for (Dino* i : *dinosPtr)
        {
            out << (*i).getName() << ",";
        }

        out << ";";

        dinosPtr = store->collection.getFightDinos();
        for (Dino* i : *dinosPtr)
        {
            out << (*i).getName() << ",";
        }
        out.close();
    }
}

void FileManager::load(std::string file)
{
    std::string line;
    std::ifstream in;
    in.open(file);

    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            lines.append(line);
        }
        in.close();
    }
}

Dino* FileManager::stringToDino(std::string str, Store* store)
{
    for (Dino* d : (*store->collection.getAllDinos()))
    {
        if ((*d).getName() == str)
        {
            return d;
        }
    }
    return nullptr;
}


void FileManager::parseLine(Store* store)
{
    std::size_t pos = lines.find(';');

    // first -- budget, int
    std::string sub = lines.substr(0, pos);
    store->setBudget(std::stoi(sub));
    lines.erase(0, pos + 1);

    // second -- dinos in collection, Dino
    pos = lines.find(';');
    sub = lines.substr(0, pos);
    lines.erase(0, pos + 1);

    pos = sub.find(',');

    while (pos != std::string::npos)
    {
        store->collection.addDino(stringToDino(sub.substr(0, pos), store));
        sub.erase(0, pos + 1);
        pos = sub.find(',');
    }

    // third -- fighters, Dino
    pos = lines.find(',');
    while (pos != std::string::npos)
    {
        store->collection.pushFightDino(stringToDino(lines.substr(0, pos), store));
        lines.erase(0, pos + 1);
        pos = lines.find(',');
    }
}