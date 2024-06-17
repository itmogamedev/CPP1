#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>

#include "windows.h"

int tem = 0;
bool stsl1 = false, stsl2 = false, stsl3 = false, stsl4 = false, stsl5 = false, stsl6 = false;
int MASS[6];

#include "dino.h"
#include "button.h"
#include "ui.h"
#include "start.h"
#include "play.h"
#include "inventory.h"
#include "shop.h"

int main()
{
    std::string line2, cu;
    std::ifstream in2("dino_numbers.txt");
    if (in2.is_open())
    {
        while (getline(in2, line2))
        {
            cu = line2;
        }
    }
    in2.close();

    if (cu.length() > 0 && cu.length() <= 1) {
        stsl1 = true;
        stsl2 = false;
        stsl3 = false;
        tem = 1;
    }if (cu.length() > 1 && cu.length() <= 2) {
        stsl1 = true;
        stsl2 = true;
        stsl3 = false;
        tem = 2;
    }if (cu.length() >= 3) {
        stsl1 = true;
        stsl2 = true;
        stsl3 = true;
        tem = 3;
    }

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "DINO FIGTHERS 2");
    window.setFramerateLimit(240);

    sf::Font font;
    if (!font.loadFromFile("EpilepsySansBold.ttf")) {}

    while (window.isOpen())
    {
        Wind Wind = chTam(window, font);

        if (Wind == Wind::play)
        {
            int Play = play(window, font);
        }
        if (Wind == Wind::inventory)
        {
            Inven Inven = inven(window, font);
        }
        if (Wind == Wind::shop)
        {
            Buy Buy = shopin(window, font);
        }
        if (Wind == Wind::exit)
        {
            window.close();
        }
    }
}