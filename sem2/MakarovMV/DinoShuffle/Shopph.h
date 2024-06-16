#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <cstdlib>  

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::fstream;
using std::ifstream;


void handleShop(sf::RenderWindow& win, const sf::Vector2i mousePoz, std::vector<int>& selectedDinos);