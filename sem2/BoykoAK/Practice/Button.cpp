#include "Button.h"

Button::Button() {};


void Button::SetButtonSprite(sf::Texture t) {
    B_Sprite.setTexture(t);
}

bool Button::IsMouseOverButton(sf::RenderWindow& window) {
    float btnX = B_Sprite.getPosition().x;
    float btnY = B_Sprite.getPosition().y;

    float btnX_1 = B_Sprite.getPosition().x + B_Sprite.getLocalBounds().width;
    float btnY_1 = B_Sprite.getPosition().y + B_Sprite.getLocalBounds().height;


    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;

    if (mouseX < btnX_1 && mouseX > btnX && mouseY < btnY_1 && mouseY > btnY) {
        return true;
    }
    return false;
}