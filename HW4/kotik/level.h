#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

using std::vector;

#pragma once
class Level
{
public:
	vector<vector<int>> map;
	int tilesize = 90;
	int align = 10;
	int width;
	int height;
	Level(int x, int y) {
		width = x;
		height = y;
		for (int i = 0; i < x; i++) {
			vector<int> v;
			map.push_back(v);
			for (int j = 0; j < y; j++) {
				map[i].push_back(0);
			}
		}
	}
	~Level();
	void Show(sf::RenderWindow window) {
		for (int i = 0; i < width; i++) {
			sf::RectangleShape rect(sf::Vector2f(tilesize, tilesize));
			for (int j = 0; j < height; j++) {

				rect.setFillColor(sf::Color::Cyan);
				rect.setPosition((tilesize + align) * j + align, (tilesize + align) * i + align);
				window.draw(rect);
			}
		}
	}



private:

}; 
