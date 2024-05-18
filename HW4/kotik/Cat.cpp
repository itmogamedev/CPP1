#include "Cat.h"
#include <SFML/Graphics.hpp>
#include <iostream>
//#include "Game.h"

Cat::Cat()
{
	textureName = "bobr.png";
	herotexture.loadFromFile("resources/" + textureName);
	herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
	herosprite.setPosition(0, 0);//задаем начальные координаты появления спрайта
	size = 10;
	hunger = 0;
	thirst = 0;
	dirt = 0;
	growthSpeed = 5;
}

Cat::~Cat(){}

int Cat::update()
{
	
	herosprite.setScale(size*0.001, size*0.001);
	if (hunger < maxHunger / 2)
		size += growthSpeed;
	else if (hunger >= maxHunger) size -= growthSpeed;
	dirt += 1;
	thirst += 1;
	if (hunger <= maxHunger)
	hunger += 1;
	
	if (maxSize == size)
		return 1;
	if (size == 0 || maxThirst == thirst || maxDirt == dirt)
		return -1;
	return 0;
}

void Cat::render()
{
	
}

void Cat::Feed()
{	hunger = 0;}

void Cat::Drink()
{	thirst = 0;}

void Cat::Wash()
{	dirt = 0;}
