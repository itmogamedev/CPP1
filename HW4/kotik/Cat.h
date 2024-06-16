#pragma once
#include <SFML/Graphics.hpp>
class Cat
{
private:
	const int minSize =0;
	const int maxSize =1000;
	int growthSpeed;
	const int maxHunger = 100;
	const int maxThirst=100;	
	const int maxDirt=100;



public:
	int dirt;
	int hunger;
	int thirst;
	int size;
	sf::String textureName;

	sf::Texture herotexture;//������� ������ Texture (��������)
	sf::Sprite herosprite;//������� ������ Sprite(������)
	//��������� ��������

	Cat();
	~Cat();
	int update();
	void render();
	void Feed();
	void Drink();
	void Wash();

};

