#include "AssetManager.hpp"
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Dino.h"
#include "Player.h"

void idleAnimation(sf::Sprite &sprite, std::string output){
    sprite.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/"+ output +"/base/idle.png"));
}

void Battle(){

    AssetManager manager;
    bool needToDrawEnemyGrave = false;
    bool needToDrawMyGrave = false;

    int killCounter = 0;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "DINO WARS", sf::Style::Fullscreen);


    sf::Font font;
    font.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/Gerhaus.ttf");

    sf::Texture textureBackgroundPlain;
    textureBackgroundPlain.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/popa.jpg");

    sf::Texture textureBackgroundMountain;
    textureBackgroundMountain.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/Mountain.jpg");

    sf::Texture textureBackgroundRiver;
    textureBackgroundRiver.loadFromFile("C:/Users/Asus/CLionProjects/HelloSFML/River.jpg");

    std::srand(std::time(0));
    Terrain randomTerrain = static_cast<Terrain>(std::rand() % 3);
    sf::Sprite spriteBackground;
    switch (randomTerrain) {
        case Plain:
            spriteBackground.setTexture(textureBackgroundPlain);
            break;
        case River:
            spriteBackground.setTexture(textureBackgroundRiver);
            break;
        case Mountain:
            spriteBackground.setTexture(textureBackgroundMountain);
            break;
    }

    start:
    std::map<std::string,int> map;
    map["Kira"] = 0;
    map["Kuro"] = 1;
    map["Mort"] = 2;
    map["Olaf"] = 3;

    DeathMyDino:
        std::string myDinoOutput = player.vecPull[rand()%player.vecPull.size()];
    sf::Vector2i spriteSize(24,24);
    sf::Sprite myDino;
    myDino.setScale(sf::Vector2f(7.0f, 7.0f));
    myDino.setPosition(600,500);
    int frameNum = 3;
    float animationDuration = 1;


    DeathEnemyDino:
        idleAnimation(myDino, myDinoOutput);
    std::string enemyDinoOutput = player.vecPull[rand()%player.vecPull.size()];
    sf::Sprite enemyDino;
    idleAnimation(enemyDino, enemyDinoOutput);
    enemyDino.setScale(sf::Vector2f(-7.0f,7.0f));
    enemyDino.setPosition(1200,500);

    sf::Texture greenLine;
    sf::Sprite greenLineSprite;
    greenLine.loadFromFile(  "C:/Users/Asus/CLionProjects/HelloSFML/greenbarUpper.png" );
    greenLineSprite.setPosition( 630, 465 );
    greenLineSprite.setTexture( greenLine );

    sf::Time elapsedTime;
    sf::Clock clock;

    sf::Texture greenLineEnemy;
    sf::Sprite greenLineSpriteEnemy;
    greenLineEnemy.loadFromFile( "C:/Users/Asus/CLionProjects/HelloSFML/greenbarUpper.png" );
    greenLineSpriteEnemy.setPosition( 1035, 465 );
    greenLineSpriteEnemy.setTexture( greenLineEnemy );

    sf::Text battleTitle("Press enter to smash!", font);
    battleTitle.setFillColor(sf::Color::Green);
    battleTitle.setPosition(450, 60);
    battleTitle.setCharacterSize(70);

    Kira kira = Kira();
    Kira kiraEnemy = Kira();
    Kuro kuro = Kuro();
    Kuro kuroEnemy = Kuro();
    Mort mort = Mort();
    Mort mortEnemy = Mort();
    Olaf olaf = Olaf();
    Olaf olafEnemy = Olaf();

    bool needToDrawEnemy = true;
    if ( killCounter == 3) {
        window.close();
        Winner();
    }
    if (player.vecPull.size() == 0) {
        loose:
        window.close();
        Looser();
    }

    while (window.isOpen()) {

        sf::Event Event;
        window.clear();
        window.draw(spriteBackground);
        sf::Time deltaTime = clock.restart();
        elapsedTime += deltaTime;
        float timeAsSecond = elapsedTime.asSeconds();

        int animFrame = static_cast<int>((timeAsSecond/animationDuration)* static_cast<float>(frameNum))% frameNum;

        myDino.setTextureRect(sf::IntRect(animFrame*spriteSize.x,0,spriteSize.x,spriteSize.y));
        enemyDino.setTextureRect(sf::IntRect(animFrame*spriteSize.x,0,spriteSize.x,spriteSize.y));
        window.draw(myDino);
        if (animFrame == frameNum - 1 && timeAsSecond >= 1.25f) {
            myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/idle.png"));
            enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/idle.png"));
        }
        window.draw(greenLineSprite);
        if (needToDrawEnemy == true) {
            window.draw(greenLineSpriteEnemy);
            window.draw(enemyDino);
        }
        window.draw(battleTitle);
        std::string myDinoPicked;
        switch (map[myDinoOutput]) {
            case 0:
                myDinoPicked = "Kira";
                break;
            case 1:
                myDinoPicked = "Kuro";
                break;
            case 2:
                myDinoPicked = "Mort";
                break;
            case 3:
                myDinoPicked = "Olaf";
                break;
        }
        window.display();
        while (window.pollEvent(Event)) {
            switch (Event.type) {
                case sf::Event::KeyPressed:
                    switch (map[enemyDinoOutput]) {
                        case 0:
                            if (greenLineSpriteEnemy.getScale().x > 0.28 && greenLineSprite.getScale().x > 0.25)
                            {
                                if (myDinoPicked == "Kira") {
                                    kiraEnemy.HP = kiraEnemy.HP - kira.damage(randomTerrain);
                                    kira.HP = kira.HP - kiraEnemy.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(kiraEnemy.HP/100, 1);
                                    greenLineSprite.setScale(kira.HP/100, 1);
                                    myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/hurt.png"));
                                }
                                if (myDinoPicked == "Kuro") {
                                    kiraEnemy.HP = kiraEnemy.HP - kuro.damage(randomTerrain);
                                    kuro.HP = kuro.HP - kiraEnemy.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(kiraEnemy.HP/100, 1);
                                    greenLineSprite.setScale(kuro.HP / 100, 1);
                                    myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/hurt.png"));
                                }
                                if (myDinoPicked == "Mort") {
                                    kiraEnemy.HP = kiraEnemy.HP - mort.damage(randomTerrain);
                                    mort.HP = mort.HP - kiraEnemy.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(kiraEnemy.HP/100, 1);
                                    greenLineSprite.setScale(mort.HP / 100, 1);
                                    myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/hurt.png"));
                                }
                                if (myDinoPicked == "Olaf") {
                                    kiraEnemy.HP = kiraEnemy.HP - olaf.damage(randomTerrain);
                                    olaf.HP = olaf.HP - kiraEnemy.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(kiraEnemy.HP/100, 1);
                                    greenLineSprite.setScale(olaf.HP / 100, 1);
                                    myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/hurt.png"));
                                }
                            }
                            else
                            {
                                ++killCounter;
                                needToDrawEnemyGrave = true;
                                goto DeathEnemyDino;
                            }
                            if (greenLineSprite.getScale().x == greenLineSpriteEnemy.getScale().x && greenLineSprite.getScale().x < 0.25) {
                                ++killCounter;
                                needToDrawMyGrave = true;
                                needToDrawEnemyGrave = true;
                                if (player.vecPull.size()!=0) {
                                    player.vecPull.erase( std::remove(player.vecPull.begin(), player.vecPull.end(), myDinoPicked), player.vecPull.end() );
                                }
                                if (player.vecPull.size() == 0) {
                                    goto loose;
                                }
                                goto start;
                            }

                            if(greenLineSprite.getScale().x < 0.25)
                            {
                                if (player.vecPull.size()!=0) {
                                    needToDrawMyGrave = true;
                                    player.vecPull.erase( std::remove(player.vecPull.begin(), player.vecPull.end(), myDinoPicked), player.vecPull.end() );
                                }
                                goto DeathMyDino;
                            }
                            break;

                        case 1:
                            if (greenLineSpriteEnemy.getScale().x > 0.28 && greenLineSprite.getScale().x > 0.25)
                            {
                                if (myDinoPicked == "Kira") {
                                    kuroEnemy.HP = kuroEnemy.HP - kira.damage(randomTerrain);
                                    kira.HP = kira.HP - kuroEnemy.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(kuroEnemy.HP / 100, 1);
                                    greenLineSprite.setScale(kira.HP/100, 1);
                                    myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/hurt.png"));
                                }
                                if (myDinoPicked == "Kuro") {
                                    kuroEnemy.HP = kuroEnemy.HP - kuro.damage(randomTerrain);
                                    kuro.HP = kuro.HP - kuroEnemy.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(kuroEnemy.HP / 100, 1);
                                    greenLineSprite.setScale(kuro.HP / 100, 1);
                                    myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/hurt.png"));
                                }
                                if (myDinoPicked == "Mort") {
                                    kuroEnemy.HP = kuroEnemy.HP - mort.damage(randomTerrain);
                                    mort.HP = mort.HP - kuroEnemy.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(kuroEnemy.HP / 100, 1);
                                    greenLineSprite.setScale(mort.HP / 100, 1);
                                    myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/hurt.png"));
                                }
                                if (myDinoPicked == "Olaf") {
                                    kuroEnemy.HP = kuroEnemy.HP - olaf.damage(randomTerrain);
                                    olaf.HP = olaf.HP - kuroEnemy.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(kuroEnemy.HP / 100, 1);
                                    greenLineSprite.setScale(olaf.HP / 100, 1);
                                    myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/hurt.png"));
                                }
                            }
                            else
                            {
                                ++killCounter;
                                needToDrawEnemy = false;
                                needToDrawEnemyGrave = true;
                                goto DeathEnemyDino;
                            }
                            if (greenLineSprite.getScale().x == greenLineSpriteEnemy.getScale().x && greenLineSprite.getScale().x < 0.25) {
                                ++killCounter;
                                needToDrawMyGrave = true;
                                needToDrawEnemyGrave = true;
                                if (player.vecPull.size()!=0) {
                                    player.vecPull.erase( std::remove(player.vecPull.begin(), player.vecPull.end(), myDinoPicked), player.vecPull.end() );
                                }
                                if (player.vecPull.size() == 0) {
                                    goto loose;
                                }
                                goto start;
                            }
                            if(greenLineSprite.getScale().x < 0.25)
                            {
                                if (player.vecPull.size()!=0) {
                                    needToDrawMyGrave = true;
                                    player.vecPull.erase( std::remove(player.vecPull.begin(), player.vecPull.end(), myDinoPicked), player.vecPull.end() );
                                }
                                goto DeathMyDino;
                            }
                            break;

                        case 2:
                            if (greenLineSpriteEnemy.getScale().x > 0.28 && greenLineSprite.getScale().x > 0.25)
                            {
                                if (myDinoPicked == "Kira") {
                                    mortEnemy.HP = mortEnemy.HP - kira.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(mortEnemy.HP / 100, 1);
                                    kira.HP = kira.HP - mortEnemy.damage(randomTerrain);
                                    greenLineSprite.setScale(kira.HP/100, 1);
                                    myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/hurt.png"));
                                }
                                if (myDinoPicked == "Kuro") {
                                    mortEnemy.HP = mortEnemy.HP - kuro.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(mortEnemy.HP / 100, 1);
                                    kuro.HP = kuro.HP - mortEnemy.damage(randomTerrain);
                                    greenLineSprite.setScale(kuro.HP / 100, 1);
                                    myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/hurt.png"));
                                }
                                if (myDinoPicked == "Mort") {
                                    mortEnemy.HP = mortEnemy.HP - mort.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(mortEnemy.HP / 100, 1);
                                    mort.HP = mort.HP - mortEnemy.damage(randomTerrain);
                                    greenLineSprite.setScale(mort.HP / 100, 1);
                                    myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/hurt.png"));
                                }
                                if (myDinoPicked == "Olaf") {
                                    mortEnemy.HP = mortEnemy.HP - olaf.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(mortEnemy.HP / 100, 1);
                                    olaf.HP = olaf.HP - mortEnemy.damage(randomTerrain);
                                    greenLineSprite.setScale(olaf.HP / 100, 1);
                                    myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/hurt.png"));
                                }
                            }
                            else
                            {
                                ++killCounter;
                                needToDrawEnemy = false;
                                needToDrawEnemyGrave = true;
                                goto DeathEnemyDino;
                            }
                            if (greenLineSprite.getScale().x == greenLineSpriteEnemy.getScale().x && greenLineSprite.getScale().x < 0.25) {
                                ++killCounter;
                                needToDrawMyGrave = true;
                                needToDrawEnemyGrave = true;
                                if (player.vecPull.size()!=0) {
                                    player.vecPull.erase( std::remove(player.vecPull.begin(), player.vecPull.end(), myDinoPicked), player.vecPull.end() );
                                }
                                if (player.vecPull.size() == 0) {
                                    goto loose;
                                }
                                goto start;
                            }
                            if(greenLineSprite.getScale().x < 0.25)
                            {
                                if (player.vecPull.size()!=0) {
                                    needToDrawMyGrave = true;
                                    player.vecPull.erase( std::remove(player.vecPull.begin(), player.vecPull.end(), myDinoPicked), player.vecPull.end() );
                                }
                                goto DeathMyDino;
                            }
                            break;

                        case 3:
                            if (greenLineSpriteEnemy.getScale().x > 0.28 && greenLineSprite.getScale().x > 0.25)
                            {
                                if (myDinoPicked == "Kira") {
                                    olafEnemy.HP = olafEnemy.HP - kira.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(olafEnemy.HP / 100, 1);
                                    kira.HP = kira.HP - olafEnemy.damage(randomTerrain);
                                    greenLineSprite.setScale(kira.HP/100, 1);
                                    myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/hurt.png"));
                                }
                                if (myDinoPicked == "Kuro") {
                                    olafEnemy.HP = olafEnemy.HP - kuro.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(olafEnemy.HP / 100, 1);
                                    kuro.HP = kuro.HP - olafEnemy.damage(randomTerrain);
                                    greenLineSprite.setScale(kuro.HP / 100, 1);
                                    myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/hurt.png"));
                                }
                                if (myDinoPicked == "Mort") {
                                    olafEnemy.HP = olafEnemy.HP - mort.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(olafEnemy.HP / 100, 1);
                                    mort.HP = mort.HP - olafEnemy.damage(randomTerrain);
                                    greenLineSprite.setScale(mort.HP / 100, 1);
                                    myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/hurt.png"));
                                }
                                if (myDinoPicked == "Olaf") {
                                    olafEnemy.HP = olafEnemy.HP - olaf.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(olafEnemy.HP / 100, 1);
                                    olaf.HP = olaf.HP - olafEnemy.damage(randomTerrain);
                                    greenLineSprite.setScale(olaf.HP / 100, 1);
                                    myDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + myDinoOutput + "/base/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture("C:/Users/Asus/CLionProjects/HelloSFML/" + enemyDinoOutput + "/base/hurt.png"));
                                }
                            }
                            else
                            {
                                ++killCounter;
                                needToDrawEnemy = false;
                                needToDrawEnemyGrave = true;
                                goto DeathEnemyDino;
                            }
                            if (greenLineSprite.getScale().x == greenLineSpriteEnemy.getScale().x && greenLineSprite.getScale().x < 0.25) {
                                ++killCounter;
                                needToDrawMyGrave = true;
                                needToDrawEnemyGrave = true;
                                if (player.vecPull.size()!=0) {
                                    player.vecPull.erase( std::remove(player.vecPull.begin(), player.vecPull.end(), myDinoPicked), player.vecPull.end() );
                                }
                                if (player.vecPull.size() == 0) {
                                    goto loose;
                                }
                                goto start;
                            }
                            if(greenLineSprite.getScale().x < 0.25)
                            {
                                if (player.vecPull.size()!=0) {
                                    needToDrawMyGrave = true;
                                    player.vecPull.erase( std::remove(player.vecPull.begin(), player.vecPull.end(), myDinoPicked), player.vecPull.end() );
                                }
                                goto DeathMyDino;
                            }
                            break;
                    }
                    break;
            }
        }
    }
}