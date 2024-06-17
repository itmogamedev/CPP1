#include "Graphics.h"

void idleAnimation(sf::Sprite &sprite, std::string output){
    sprite.setTexture(AssetManager::GetTexture(resourcePath() +
                                               "dinoAssets/"+ output +"/idle.png"));
}

void battleMenu(){
    
start:
                        sf::RenderWindow showBattleWindow (sf::VideoMode(800,600,60), "Dino Wars",sf::Style::Resize);
                        
                        //hp icon
                        sf::Texture hpIcon;
                        sf::Sprite hpIconSprite;
                        if ( !hpIcon.loadFromFile( resourcePath() + "greenbar.png" ) )
                            std::cout << "Can't find the image" << std::endl;
                        hpIconSprite.setPosition( 100, 250 );
                        hpIconSprite.setTexture( hpIcon );
                        
                        
                        
                        //hp icon
                        sf::Texture hpIconEnemy;
                        sf::Sprite hpIconSpriteEnemy;
                        if ( !hpIconEnemy.loadFromFile( resourcePath() + "greenbar.png" ) )
                            std::cout << "Can't find the image" << std::endl;
                        hpIconSpriteEnemy.setPosition( 570, 250 );
                        hpIconSpriteEnemy.setTexture( hpIconEnemy );
                        
                        
                        //mapping for string vector
                        std::map<std::string,int> hash;
                        hash["Kuro"] = 0;
                        hash["Loki"] = 1;
                        hash["Mono"] = 2;
                        
                        //kira characteristics
                        sf::Text kiraCharacteristicsText ("STRENGTH - " + std::to_string(Kira().STRENGTH) + "\nDEXTERITY - " + std::to_string(Kira().DEXTERITY) + "\nINTELLIGENCE - " + std::to_string(Kira().INTELLIGENCE),font);
                        kiraCharacteristicsText.setCharacterSize(25);
                        kiraCharacteristicsText.setFillColor(sf::Color::White);
                        
                        //cole characteristics
                        sf::Text coleCharacteristicsText ("STRENGTH - " + std::to_string(Cole().STRENGTH) + "\nDEXTERITY - " + std::to_string(Cole().DEXTERITY) + "\nINTELLIGENCE - " + std::to_string(Cole().INTELLIGENCE),font);
                        coleCharacteristicsText.setCharacterSize(25);
                        coleCharacteristicsText.setFillColor(sf::Color::White);
                        
                        //mono characteristics
                        sf::Text monoCharacteristicsText ("STRENGTH - " + std::to_string(Mono().STRENGTH) + "\nDEXTERITY - " + std::to_string(Mono().DEXTERITY) + "\nINTELLIGENCE - " + std::to_string(Mono().INTELLIGENCE),font);
                        monoCharacteristicsText.setCharacterSize(25);
                        monoCharacteristicsText.setFillColor(sf::Color::White);
                        
                        //background
                        sf::Texture textureBackgroundPlain;
                        if (!textureBackgroundPlain.loadFromFile(resourcePath() + "plainBackground.jpg")) {
                            return EXIT_FAILURE;
                        }
                        sf::Texture textureBackgroundMountain;
                        if (!textureBackgroundMountain.loadFromFile(resourcePath() + "background.jpg")) {
                            return EXIT_FAILURE;
                        }
                        sf::Texture textureBackgroundRiver;
                        if (!textureBackgroundRiver.loadFromFile(resourcePath() + "riverBackground.jpg")) {
                            return EXIT_FAILURE;
                        }
                        // Seed the random number generator with the current time
                        std::srand(std::time(0));
                        // Generate a random day using rand() and the enum range
                        Terrain randomTerrain = static_cast<Terrain>(std::rand() % 3);
                        sf::Sprite spriteBackground;
                        // Switch statement to print the corresponding day
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
                        //myDino sprite
DeathMyDino:            std::string myDinoOutput = vectorDinosReady[rand()%vectorDinosReady.size()];
                        sf::Vector2i spriteSize(24,24);
                        sf::Sprite myDino;
                        myDino.setScale(6, 6);
                        myDino.setPosition(100,300);
                        int frameNum = 3;
                        float animationDuration = 0.5;
                        
                        
                        //enemyDino Sprite
DeathEnemyDino:         idleAnimation(myDino, myDinoOutput);
                        std::string enemyDinoOutput = vectorDinosReady[rand()%vectorDinosReady.size()];
                        sf::Sprite enemyDino;
                        idleAnimation(enemyDino, enemyDinoOutput);
                        enemyDino.setScale(-6, 6);
                        enemyDino.setPosition(715,300);
                        
                        //hp green line
                        sf::Texture greenLine;
                        sf::Sprite greenLineSprite;
                        if ( !greenLine.loadFromFile( resourcePath() + "greenbarUpper.png" ) )
                            std::cout << "Can't find the image" << std::endl;
                        greenLineSprite.setPosition( 100, 265 );
                        greenLineSprite.setTexture( greenLine );
                        
                        sf::Time elapsedTime;
                        sf::Clock clock;
                        //hp green line
                        sf::Texture greenLineEnemy;
                        sf::Sprite greenLineSpriteEnemy;
                        if ( !greenLineEnemy.loadFromFile( resourcePath() + "greenbarUpper.png" ) )
                            std::cout << "Can't find the image" << std::endl;
                        greenLineSpriteEnemy.setPosition( 570, 265 );
                        greenLineSpriteEnemy.setTexture( greenLineEnemy );
                        
                        //font
                        sf::Font font;
                        if (!font.loadFromFile(resourcePath() + "blackberry.otf")) {
                            return EXIT_FAILURE;
                        }
                        //title
                        sf::Text battleTitle("Press enter to smash!",font);
                        battleTitle.setFillColor(sf::Color::Red);
                        battleTitle.setPosition(180, 60);
                        battleTitle.setCharacterSize(70);
                        
                        //battle algorithm
                        Kira kira = Kira();
                        Kira kiraEnemy = Kira();
                        Cole cole = Cole();
                        Cole coleEnemy = Cole();
                        Mono mono = Mono();
                        Mono monoEnemy = Mono();
                        bool needToDrawEnemy = true;
                        if ( killCounter == 3) {
                            showBattleWindow.close();
                            winnerWindowPrint();
                        }
                        if (vectorDinosReady.size() == 0) {
loose:                      showBattleWindow.close();
                            looserWindowPrint();
                        }
                        
                        while (showBattleWindow.isOpen()) {
begin:
                            sf::Event Event;
                            showBattleWindow.clear();
                            showBattleWindow.draw(spriteBackground);
                            sf::Time deltaTime = clock.restart();
                            elapsedTime += deltaTime;
                            float timeAsSecond = elapsedTime.asSeconds();
                            
                            int animFrame = static_cast<int>((timeAsSecond/animationDuration)* static_cast<float>(frameNum))% frameNum;
                            
                            myDino.setTextureRect(sf::IntRect(animFrame*spriteSize.x,0,spriteSize.x,spriteSize.y));
                            enemyDino.setTextureRect(sf::IntRect(animFrame*spriteSize.x,0,spriteSize.x,spriteSize.y));
                            showBattleWindow.draw(myDino);
                            if (animFrame == frameNum - 1 && timeAsSecond >= 1.25f) {
                                myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/" + myDinoOutput + "/idle.png"));
                                enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/" + enemyDinoOutput + "/idle.png"));
                            }
                            showBattleWindow.draw(hpIconSprite);
                            showBattleWindow.draw(greenLineSprite);
                            showBattleWindow.draw(hpIconSpriteEnemy);
                            if (needToDrawEnemy == true) {
                                showBattleWindow.draw(greenLineSpriteEnemy);
                                showBattleWindow.draw(enemyDino);
                            }
                            showBattleWindow.draw(battleTitle);
                            std::string myDinoPicked;
                            switch (hash[myDinoOutput]) {
                                case 0:
                                    showBattleWindow.draw(kiraCharacteristicsText);
                                    myDinoPicked = "Kira";
                                    kiraCharacteristicsText.setPosition(100, 450);
                                    break;
                                case 1:
                                    showBattleWindow.draw(coleCharacteristicsText);
                                    myDinoPicked = "Cole";
                                    coleCharacteristicsText.setPosition(100, 450);
                                    break;
                                case 2:
                                    showBattleWindow.draw(monoCharacteristicsText);
                                    myDinoPicked = "Mono";
                                    monoCharacteristicsText.setPosition(100, 450);
                                    break;
                            }
                            showBattleWindow.display();
                            while (showBattleWindow.pollEvent(Event)) {
                                switch (Event.type) {
                                    case sf::Event::KeyPressed:
                                        switch (hash[enemyDinoOutput]) {
                                            case 0:
                                                if (greenLineSpriteEnemy.getScale().x > 0.28 && greenLineSprite.getScale().x > 0.25)
                                                {
                                                    if (myDinoPicked == "Kira") {
                                                        kiraEnemy.HP = kiraEnemy.HP - kira.damage(randomTerrain);
                                                        kira.HP = kira.HP - kiraEnemy.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(kiraEnemy.HP/100, 1);
                                                        greenLineSprite.setScale(kira.HP/100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ myDinoOutput +"/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ enemyDinoOutput +"/hurt.png"));
                                                    }
                                                    if (myDinoPicked == "Cole") {
                                                        kiraEnemy.HP = kiraEnemy.HP - cole.damage(randomTerrain);
                                                        cole.HP = cole.HP - kiraEnemy.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(kiraEnemy.HP/100, 1);
                                                        greenLineSprite.setScale(cole.HP/100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ myDinoOutput +"/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ enemyDinoOutput +"/hurt.png"));
                                                    }
                                                    if (myDinoPicked == "Mono") {
                                                        kiraEnemy.HP = kiraEnemy.HP - mono.damage(randomTerrain);
                                                        mono.HP = mono.HP - kiraEnemy.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(kiraEnemy.HP/100, 1);
                                                        greenLineSprite.setScale(mono.HP/100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ myDinoOutput +"/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ enemyDinoOutput +"/hurt.png"));
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
                                                    if (vectorDinosReady.size()!=0) {
                                                        vectorDinosReady.erase( std::remove(vectorDinosReady.begin(), vectorDinosReady.end(), myDinoPicked), vectorDinosReady.end() );
                                                    }
                                                    if (vectorDinosReady.size() == 0) {
                                                        goto loose;
                                                    }
                                                    goto start;
                                                }

                                                if(greenLineSprite.getScale().x < 0.25)
                                                {
                                                    if (vectorDinosReady.size()!=0) {
                                                        needToDrawMyGrave = true;
                                                        vectorDinosReady.erase( std::remove(vectorDinosReady.begin(), vectorDinosReady.end(), myDinoPicked), vectorDinosReady.end() );
                                                    }
                                                    goto DeathMyDino;
                                                }
                                                
                                                break;
                                            case 1:
                                                if (greenLineSpriteEnemy.getScale().x > 0.28 && greenLineSprite.getScale().x > 0.25)
                                                {
                                                    if (myDinoPicked == "Kira") {
                                                        coleEnemy.HP = coleEnemy.HP - kira.damage(randomTerrain);
                                                        kira.HP = kira.HP - coleEnemy.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(coleEnemy.HP/100, 1);
                                                        greenLineSprite.setScale(kira.HP/100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ myDinoOutput +"/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ enemyDinoOutput +"/hurt.png"));
                                                    }
                                                    if (myDinoPicked == "Cole") {
                                                        coleEnemy.HP = coleEnemy.HP - cole.damage(randomTerrain);
                                                        cole.HP = cole.HP - coleEnemy.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(coleEnemy.HP/100, 1);
                                                        greenLineSprite.setScale(cole.HP/100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ myDinoOutput +"/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ enemyDinoOutput +"/hurt.png"));
                                                    }
                                                    if (myDinoPicked == "Mono") {
                                                        coleEnemy.HP = coleEnemy.HP - mono.damage(randomTerrain);
                                                        mono.HP = mono.HP - coleEnemy.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(coleEnemy.HP/100, 1);
                                                        greenLineSprite.setScale(mono.HP/100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ myDinoOutput +"/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ enemyDinoOutput +"/hurt.png"));
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
                                                    if (vectorDinosReady.size()!=0) {
                                                        vectorDinosReady.erase( std::remove(vectorDinosReady.begin(), vectorDinosReady.end(), myDinoPicked), vectorDinosReady.end() );
                                                    }
                                                    if (vectorDinosReady.size() == 0) {
                                                        goto loose;
                                                    }
                                                    goto start;
                                                }
                                                if(greenLineSprite.getScale().x < 0.25)
                                                {
                                                    if (vectorDinosReady.size()!=0) {
                                                        needToDrawMyGrave = true;
                                                        vectorDinosReady.erase( std::remove(vectorDinosReady.begin(), vectorDinosReady.end(), myDinoPicked), vectorDinosReady.end() );
                                                    }
                                                    goto DeathMyDino;
                                                }
                                                
                                                
                                                break;
                                            case 2:
                                                if (greenLineSpriteEnemy.getScale().x > 0.28 && greenLineSprite.getScale().x > 0.25)
                                                {
                                                    if (myDinoPicked == "Kira") {
                                                        monoEnemy.HP = monoEnemy.HP - kira.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(monoEnemy.HP/100, 1);
                                                        kira.HP = kira.HP - monoEnemy.damage(randomTerrain);
                                                        greenLineSprite.setScale(kira.HP/100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ myDinoOutput +"/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ enemyDinoOutput +"/hurt.png"));
                                                    }
                                                    if (myDinoPicked == "Cole") {
                                                        monoEnemy.HP = monoEnemy.HP - cole.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(monoEnemy.HP/100, 1);
                                                        cole.HP = cole.HP - monoEnemy.damage(randomTerrain);
                                                        greenLineSprite.setScale(cole.HP/100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ myDinoOutput +"/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ enemyDinoOutput +"/hurt.png"));
                                                    }
                                                    if (myDinoPicked == "Mono") {
                                                        monoEnemy.HP = monoEnemy.HP - mono.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(monoEnemy.HP/100, 1);
                                                        mono.HP = mono.HP - monoEnemy.damage(randomTerrain);
                                                        greenLineSprite.setScale(mono.HP/100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ myDinoOutput +"/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ enemyDinoOutput +"/hurt.png"));
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
                                                    if (vectorDinosReady.size()!=0) {
                                                        vectorDinosReady.erase( std::remove(vectorDinosReady.begin(), vectorDinosReady.end(), myDinoPicked), vectorDinosReady.end() );
                                                    }
                                                    if (vectorDinosReady.size() == 0) {
                                                        goto loose;
                                                    }
                                                    goto start;
                                                }
                                                if(greenLineSprite.getScale().x < 0.25)
                                                {
                                                    if (vectorDinosReady.size()!=0) {
                                                        needToDrawMyGrave = true;
                                                        vectorDinosReady.erase( std::remove(vectorDinosReady.begin(), vectorDinosReady.end(), myDinoPicked), vectorDinosReady.end() );
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
