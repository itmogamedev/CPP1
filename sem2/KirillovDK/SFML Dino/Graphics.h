#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

class Graphics
{
public:
    Font font;

    Text playerHPText;
    Text enemyHPText;

    Text winText;
    Text loseText;
    Text drawText;

    Text battleLocationText;
    Text enemyDinosCountText;
    Text chooseYourDinosText;
    Text playerMoneyShopText;

    Text yourDinosText;
    Text dinosListText;
    Text dinosListBattleText;

    Text playerDinosLeftText;
    Text enemyDinosLeftText;

    Texture selectDinoButtonTexture;
    Texture unselectDinoButtonTexture;
    Sprite selectDinoButton[15];
    bool selectedDinos[15];

    Sprite startBattleButton;

    Text enemy1DinoText;
    Text enemy2DinoText;
    Text enemy3DinoText;

    Texture playerDinoTexture;
    Texture enemyDinoTexture;

    Sprite playerDinoSprite;
    Sprite enemyDinoSprite;

    Texture dinoTexture[5];

    Texture dino1BuyTexture;
    Texture dino2BuyTexture;
    Texture dino3BuyTexture;
    Texture dino4BuyTexture;
    Texture dino5BuyTexture;

    Texture buyButton;

    Sprite buy1Button;
    Sprite buy2Button;
    Sprite buy3Button;
    Sprite buy4Button;
    Sprite buy5Button;

    Sprite dino1BuySprite;
    Sprite dino2BuySprite;
    Sprite dino3BuySprite;
    Sprite dino4BuySprite;
    Sprite dino5BuySprite;

    Texture plainBGTexture;
    Texture mountainBGTexture;
    Texture riverBGTexture;

    Sprite plainBGSprite;
    Sprite mountainBGSprite;
    Sprite riverBGSprite;

    Texture mainMenuBackgroundTexture;
    Texture battleBackgroundTexture;
    Texture shopMenuBackgroundTexture;

    Sprite mainMenuBackgroundSprite;
    Sprite battleBackgroundSprite;
    Sprite shopMenuBackgroundSprite;

    Texture backToMainMenuButtonTexture;
    Texture battleButtonTexture;
    Texture shopButtonTexture;
    Texture dinoListButtonTexture;
    Texture quitButtonTexture;

    Sprite backToMainMenuButton;
    Sprite battleButton;
    Sprite shopButton;
    Sprite dinoListButton;
    Sprite quitButton;

    Texture getDamageTexture;
    Sprite getDamageSprite[6];

    Texture damageTexture;
    Sprite damageSprite[10];

    Music punchSound;
    Music deathSound;

    Graphics();

    void SetText(Text& text, std::string str, int size, Color color, int c1, int c2)
    {
        text.setString(str);
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(color);
        text.setStyle(Text::Bold);
        text.setPosition(c1, c2);
    }

    void SetImage(Sprite& sprite, Texture& texture, std::string str, float s1, float s2, int c1, int c2)
    {
        texture.loadFromFile(str);
        sprite.setTexture(texture);
        sprite.setScale(s1, s2);
        sprite.setPosition(c1, c2);
    }
};

#endif