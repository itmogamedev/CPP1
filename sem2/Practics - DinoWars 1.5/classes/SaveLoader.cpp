#include "SaveLoader.h"

SaveLoader::SaveLoader(std::string i_filename)
{
	filename = i_filename;
}
void SaveLoader::save(Player& player)
{
    std::ofstream outFile(filename);

    if (outFile.is_open()) {
        outFile << player.getCoins() << "\n";

        for (const auto& dino : player.dinos_owned) {
            outFile << dino->getDinoData();
            outFile << std::endl;
        }

        outFile.close();
       // std::cout << "SAVED.\n";
    }
    else {
       // std::cerr << "UNABLE TO SAVE.\n";
    }
}

void SaveLoader::load(Player& player)
{
    std::ifstream inFile(filename);
    int type, prefTer, stren, agil, mana, def;
    char colon;
    std::string semicolon;

    if (inFile.is_open()) {
        // ÑÊÎËÜÊÎ ÌÎÍÅÒ
        std::string line;
        std::getline(inFile, line);
        if (!line.empty()) 
        {
            player.setCoins(std::stoi(line));
        }
        player.dinos_owned.clear();
        // ÏÎÊÀ ÅÑÒÜ ÑÒĞÎÊÈ, ÄÈÍÎÇÀÂĞÈÊÈ ÅÑÒÜ
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);

            // ÏÎØËÀ ÊÎËÁÀÑÀ
            ss >> type >> prefTer >> stren >> agil >> mana >> def;

            Dino* newDino = new Dino(def, stren, mana, agil);
            newDino->set_typeandter(static_cast<species>(type), static_cast<terrain>(prefTer));


            // Â ÇÀÃÎÍ ÅÃÎ
            player.dinos_owned.push_back(newDino);
        }

        inFile.close();
       // std::cout << "LOADED.\n";
    }
    else {
       // std::cerr << "UNABLE TO LOAD.\n";
    }
}
