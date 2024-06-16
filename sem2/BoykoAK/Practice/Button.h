#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
public:
    sf::Texture B_Texture;
    sf::Sprite B_Sprite;

    Button();


    void SetActivity(bool n); // { isActive = n; }
    void SetButtonSprite(sf::Texture t); //{B_Sprite.setTexture(t);}
    bool IsMouseOverButton(sf::RenderWindow& window);
};

