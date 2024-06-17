#include "Graphics.h"
#include "DatabaseFunc.hpp"

AssetManager manager;
//vectors to post and pull from inventory
std::vector<std::string> vector;
std::vector<std::string> vectorDinosReady;


void startingBattleWindowPrint(){
    
    sf::RenderWindow battleWindow (sf::VideoMode(800,600,60), "Dino Wars",sf::Style::Resize);
    
    //background
    sf::Texture textureBackground;
    if (!textureBackground.loadFromFile(resourcePath() + "background.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite spriteBackground(textureBackground);
    
    
    //font
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "blackberry.otf")) {
        return EXIT_FAILURE;
    }
    
    //TITLE
    sf::Text titleBattle ("Choose your dino's", font);
    titleBattle.setFillColor(sf::Color::White);
    titleBattle.setCharacterSize(60);
    titleBattle.setPosition(sf::Vector2f(175,20));
    titleBattle.setStyle(sf::Text::Bold);
    
    
    //dino button
    //BUTTON FOR KIRA
    sf::Text buttonKuroPickText;
    float buttonKuroPickTextWidth = buttonKuroPickText.getLocalBounds().width;
    float buttonKuroPickTextHeight = buttonKuroPickText.getLocalBounds().height;
    buttonKuroPickText.setFont( font );
    buttonKuroPickText.setStyle( sf::Text::Regular );
    buttonKuroPickText.setString( "PICK" );
    buttonKuroPickText.setFillColor( sf::Color::Black );
    buttonKuroPickText.setCharacterSize( 55 );
    buttonKuroPickText.setPosition(sf::Vector2f(85,480));
    
    //BUTTON FOR COLE
    sf::Text buttonLokiPickText;
    float buttonLokiPickTextWidth = buttonLokiPickText.getLocalBounds().width;
    float buttonLokiPickTextTextHeight = buttonLokiPickText.getLocalBounds().height;
    buttonLokiPickText.setFont( font );
    buttonLokiPickText.setStyle( sf::Text::Regular );
    buttonLokiPickText.setString( "PICK" );
    buttonLokiPickText.setFillColor( sf::Color::Black );
    buttonLokiPickText.setCharacterSize( 55 );
    buttonLokiPickText.setPosition(sf::Vector2f(345,480));
    
    //BUTTON FOR MONO
    sf::Text buttonMonoPickText;
    float buttonMonoPickTextWidth = buttonMonoPickText.getLocalBounds().width;
    float buttonMonoPickTextHeight = buttonMonoPickText.getLocalBounds().height;
    buttonMonoPickText.setFont( font );
    buttonMonoPickText.setStyle( sf::Text::Regular );
    buttonMonoPickText.setString( "PICK" );
    buttonMonoPickText.setFillColor( sf::Color::Black );
    buttonMonoPickText.setCharacterSize( 55 );
    buttonMonoPickText.setPosition(sf::Vector2f(595,480));
    
    //button back
    sf::Texture backButton;
    sf::Sprite backButtonImage;
    if ( !backButton.loadFromFile( resourcePath() + "iconButtonBack.png" ) )
        std::cout << "Can't find the image" << std::endl;
    float backButtonWidth = backButtonImage.getLocalBounds().width;
    float backButtonHeight = backButtonImage.getLocalBounds().height;
    backButtonImage.setPosition( backButtonWidth, backButtonHeight );
    
    backButtonImage.setTexture( backButton );
    
    //button start battle
    sf::Texture startButton;
    sf::Sprite startButtonImage;
    if ( !startButton.loadFromFile( resourcePath() + "battleButton.png" ) )
        std::cout << "Can't find the image" << std::endl;
    startButtonImage.setPosition( 700, 20 );
    startButtonImage.setTexture( startButton );
    
    //dino background sprite
    //DINOS BACKGROUND SPRITE
    sf::Texture backgroundTextureForDinos;
    if ( !backgroundTextureForDinos.loadFromFile( resourcePath() + "dinoAssets/dinosBackground.jpg" ) )
        std::cout << "Can't find the image" << std::endl;
    
    //dino sprite
    //Kuro SPRITE
    sf::Texture dinoKuroTexture;
    if ( !dinoKuroTexture.loadFromFile( resourcePath() + "dinoAssets/Kuro/idle.png" ) )
        std::cout << "Can't find the image" << std::endl;
    sf::Sprite dinoKuroSprite(dinoKuroTexture,sf::IntRect(0,0,24,24));
    dinoKuroSprite.setPosition(50, 230);
    dinoKuroSprite.setScale(sf::Vector2f(7.0f,7.0f));
    sf::Sprite backgroundKuroSpriteForDinos(backgroundTextureForDinos,sf::IntRect(0,0,24,24));
    backgroundKuroSpriteForDinos.setPosition(70, 230);
    backgroundKuroSpriteForDinos.setScale(sf::Vector2f(6.0f,7.0f));
    sf::Text kuroTextName("Kuro ", font);
    kuroTextName.setCharacterSize(70);
    kuroTextName.setFillColor(sf::Color(0,197,208,230));
    kuroTextName.setStyle(sf::Text::Bold);
    kuroTextName.setPosition(85, 150);
    
    sf::Text kuroCharacteristicsText ("STRENGTH - " + std::to_string(Kuro().STRENGTH) + "\nDEXTERITY - " + std::to_string(Kuro().DEXTERITY) + "\nINTELLIGENCE - " + std::to_string(Kuro().INTELLIGENCE),font);
    kuroCharacteristicsText.setCharacterSize(25);
    kuroCharacteristicsText.setFillColor(sf::Color::White);
    kuroCharacteristicsText.setPosition(75, 400);
    
    //COLE SPRITE
    sf::Texture dinoLokiTexture;
    if ( !dinoLokiTexture.loadFromFile( resourcePath() + "dinoAssets/Loki/idle.png" ) )
        std::cout << "Can't find the image" << std::endl;
    sf::Sprite dinoLokiSprite(dinoLokiTexture,sf::IntRect(0,0,24,24));
    dinoLokiSprite.setPosition(305, 230);
    dinoLokiSprite.setScale(sf::Vector2f(7.0f,7.0f));
    sf::Text lokiTextName("Loki ", font);
    lokiTextName.setCharacterSize(70);
    lokiTextName.setFillColor(sf::Color(0,197,208,230));
    lokiTextName.setStyle(sf::Text::Bold);
    lokiTextName.setPosition(340, 150);
    sf::Sprite backgroundLokiSpriteForDinos(backgroundTextureForDinos,sf::IntRect(0,0,24,24));
    backgroundLokiSpriteForDinos.setPosition(325, 230);
    backgroundLokiSpriteForDinos.setScale(sf::Vector2f(6.0f,7.0f));
    sf::Text lokiCharacteristicsText ("STRENGTH - " + std::to_string(Loki().STRENGTH) + "\nDEXTERITY - " + std::to_string(Loki().DEXTERITY) + "\nINTELLIGENCE - " + std::to_string(Loki().INTELLIGENCE),font);
    lokiCharacteristicsText.setCharacterSize(25);
    lokiCharacteristicsText.setFillColor(sf::Color::White);
    lokiCharacteristicsText.setPosition(330, 400);
    
    //sprite MONO
    sf::Texture dinoMonoTexture;
    if ( !dinoMonoTexture.loadFromFile( resourcePath() + "dinoAssets/Mono/idle.png" ) )
        std::cout << "Can't find the image" << std::endl;
    sf::Sprite dinoMonoSprite(dinoMonoTexture,sf::IntRect(0,0,24,24));
    dinoMonoSprite.setPosition(550, 230);
    dinoMonoSprite.setScale(sf::Vector2f(7.0f,7.0f));
    sf::Sprite backgroundMonoSpriteForDinos(backgroundTextureForDinos,sf::IntRect(0,0,24,24));
    sf::Text monoTextName("Mono ", font);
    monoTextName.setCharacterSize(70);
    monoTextName.setFillColor(sf::Color(0,197,208,230));
    monoTextName.setStyle(sf::Text::Bold);
    monoTextName.setPosition(585, 150);
    backgroundMonoSpriteForDinos.setPosition(570, 230);
    backgroundMonoSpriteForDinos.setScale(sf::Vector2f(6.0f,7.0f));
    sf::Text monoCharacteristicsText ("STRENGTH - " + std::to_string(Mono().STRENGTH) + "\nDEXTERITY - " + std::to_string(Mono().DEXTERITY) + "\nINTELLIGENCE - " + std::to_string(Mono().INTELLIGENCE),font);
    monoCharacteristicsText.setCharacterSize(25);
    monoCharacteristicsText.setFillColor(sf::Color::White);
    monoCharacteristicsText.setPosition(575, 400);
    
    
    //counter text
    int dinoCounter = 0;
    sf::Text counterText (std::to_string(dinoCounter) + "/3",font);
    counterText.setFillColor(sf::Color(0,197,208,230));
    counterText.setCharacterSize(30);
    counterText.setStyle( sf::Text::Bold );
    counterText.setPosition(730, 550);
    
    while (battleWindow.isOpen()) {
        
        
        sf::Event event;
        battleWindow.clear();
        battleWindow.draw(spriteBackground);
        battleWindow.draw(backgroundKuroSpriteForDinos);
        battleWindow.draw(backgroundLokiSpriteForDinos);
        battleWindow.draw(backgroundMonoSpriteForDinos);
        battleWindow.draw(kuroTextName);
        battleWindow.draw(kuroCharacteristicsText);
        battleWindow.draw(lokiTextName);
        battleWindow.draw(lokiCharacteristicsText);
        battleWindow.draw(monoTextName);
        battleWindow.draw(monoCharacteristicsText);
        battleWindow.draw(backButtonImage);
        battleWindow.draw(buttonKuroPickText);
        battleWindow.draw(buttonLokiPickText);
        battleWindow.draw(buttonMonoPickText);
        
        
        battleWindow.draw(counterText);
        
        
        std::string outInventory;
        selectInventory(outInventory);
        std::string outputStr;
        
        std::stringstream ss(outInventory);
        
        
        while (std::getline(ss, outputStr, ' ')) {
            
            vector.push_back(outputStr);
        }
        
        for (int i = 0; i < vector.size(); i++) {
            if (vector[i] == "Kuro") {
                battleWindow.draw(dinoKuroSprite);
            }
            
            if (vector[i] == "Loki") {
                battleWindow.draw(dinoLokiSprite);
            }
            
            if (vector[i] == "Mono") {
                battleWindow.draw(dinoMonoSprite);
            }
            
        }
        if (dinoCounter == 3) {
            battleWindow.draw(startButtonImage);
        }
        battleWindow.draw(titleBattle);
        battleWindow.display();
        sf::Event Event;
        
        while (battleWindow.pollEvent(Event)) {
            
            switch (Event.type) {
                case sf::Event::MouseMoved:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( battleWindow );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    
                    //if for exit button
                    if ( backButtonImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        backButtonImage.setColor( sf::Color( 250, 255, 255, 150 ) );
                    }
                    else
                    {
                        backButtonImage.setColor( sf::Color( 255, 255, 255 ) );
                    }
                    
                    //if for battle button
                    if (startButtonImage.getGlobalBounds().contains(mousePosF))
                    {
                        startButtonImage.setColor(sf::Color( 255, 255, 255, 150 ));
                    }
                    else
                    {
                        startButtonImage.setColor( sf::Color( 255, 255, 255 ) );
                    }
                    
                    //if for KIRA button
                    if ( buttonKuroPickText.getGlobalBounds().contains( mousePosF ) && buttonKuroPickText.getString() == "PICK")
                    {
                        buttonKuroPickText.setFillColor( sf::Color( 0, 0, 0, 150 ) );
                    }
                    else if (buttonKuroPickText.getString() == "Picked")
                    {
                        buttonKuroPickText.setFillColor( sf::Color::Red);
                    }
                    else
                    {
                        buttonKuroPickText.setFillColor( sf::Color::Black );
                    }
                    
                    //if for COLE button
                    if ( buttonLokiPickText.getGlobalBounds().contains( mousePosF ) && buttonLokiPickText.getString() == "PICK")
                    {
                        buttonLokiPickText.setFillColor( sf::Color( 0, 0, 0, 150 ) );
                    }
                    else if (buttonLokiPickText.getString() == "Picked")
                    {
                        buttonLokiPickText.setFillColor( sf::Color::Red);
                    }
                    else
                    {
                        buttonLokiPickText.setFillColor( sf::Color::Black );
                    }
                    //if for MONO button
                    if ( buttonMonoPickText.getGlobalBounds().contains( mousePosF ) && buttonMonoPickText.getString() == "PICK")
                    {
                        buttonMonoPickText.setFillColor( sf::Color( 0, 0, 0, 150 ) );
                    }
                    else if (buttonMonoPickText.getString() == "Picked")
                    {
                        buttonMonoPickText.setFillColor( sf::Color::Red);
                    }
                    else
                    {
                        buttonMonoPickText.setFillColor( sf::Color::Black );
                    }
                }
                    break;
                case sf::Event::MouseButtonPressed:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( battleWindow );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    
                    //if for exit button
                    if ( backButtonImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        battleWindow.close();
                        menuWindowPrint();
                    }
                    //if for pick kira
                    if (buttonKuroPickText.getGlobalBounds().contains(mousePosF) && buttonKuroPickText.getString() == "PICK") {
                        dinoCounter++;
                        counterText.setString(std::to_string(dinoCounter) + "/3");
                        buttonKuroPickText.setFillColor(sf::Color::Red);
                        buttonKuroPickText.setString("Picked");
                        battleWindow.draw(counterText);
                        battleWindow.display();
                        vectorDinosReady.push_back(Kuro().name);
                    }
                    //if for pick cole
                    if (buttonLokiPickText.getGlobalBounds().contains(mousePosF) && buttonLokiPickText.getString() == "PICK") {
                        dinoCounter++;
                        counterText.setString(std::to_string(dinoCounter) + "/3");
                        buttonLokiPickText.setFillColor(sf::Color::Red);
                        buttonLokiPickText.setString("Picked");
                        battleWindow.draw(counterText);
                        battleWindow.display();
                        vectorDinosReady.push_back(Loki().name);
                    }
                    //if for pick mono
                    if (buttonMonoPickText.getGlobalBounds().contains(mousePosF) && buttonMonoPickText.getString() == "PICK") {
                        dinoCounter++;
                        counterText.setString(std::to_string(dinoCounter) + "/3");
                        buttonMonoPickText.setFillColor(sf::Color::Red);
                        buttonMonoPickText.setString("Picked");
                        battleWindow.draw(counterText);
                        battleWindow.display();
                        vectorDinosReady.push_back(Mono().name);
                    }
                    
                    //entering battle
                    if (startButtonImage.getGlobalBounds().contains(mousePosF)) {
                        battleWindow.close();
                        battleMenu();
                    }
                }
                    break;
            }
        }
    }
}
void idleAnimation(sf::Sprite &sprite, std::string output){
    sprite.setTexture(AssetManager::GetTexture(resourcePath() +
                                               "dinoAssets/"+ output +"/idle.png"));
}

void battleMenu(){
    
    int killCounter = 0;

start:
    sf::RenderWindow showBattleWindow (sf::VideoMode(800,600,60), "Dino Wars",sf::Style::Resize);
    
    //hp icon
    sf::Texture hpIcon;
    sf::Sprite hpIconSprite;
    if ( !hpIcon.loadFromFile( resourcePath() + "greenbar.png" ) )
        std::cout << "Can't find the image" << std::endl;
    hpIconSprite.setPosition( 100, 250 );
    hpIconSprite.setTexture( hpIcon );
    
    //font
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "blackberry.otf")) {
        return EXIT_FAILURE;
    }
    
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
    sf::Text kuroCharacteristicsText ("STRENGTH - " + std::to_string(Kuro().STRENGTH) + "\nDEXTERITY - " + std::to_string(Kuro().DEXTERITY) + "\nINTELLIGENCE - " + std::to_string(Kuro().INTELLIGENCE),font);
    kuroCharacteristicsText.setCharacterSize(25);
    kuroCharacteristicsText.setFillColor(sf::Color::White);
    
    //cole characteristics
    sf::Text lokiCharacteristicsText ("STRENGTH - " + std::to_string(Loki().STRENGTH) + "\nDEXTERITY - " + std::to_string(Loki().DEXTERITY) + "\nINTELLIGENCE - " + std::to_string(Loki().INTELLIGENCE),font);
    lokiCharacteristicsText.setCharacterSize(25);
    lokiCharacteristicsText.setFillColor(sf::Color::White);
    
    //mono characteristics
    sf::Text monoCharacteristicsText ("STRENGTH - " + std::to_string(Mono().STRENGTH) + "\nDEXTERITY - " + std::to_string(Mono().DEXTERITY) + "\nINTELLIGENCE - " + std::to_string(Mono().INTELLIGENCE),font);
    monoCharacteristicsText.setCharacterSize(25);
    monoCharacteristicsText.setFillColor(sf::Color::White);
    
    //background
    sf::Texture textureBackgroundPlain;
    if (!textureBackgroundPlain.loadFromFile(resourcePath() + "plainBackground.jpg")) {
        return 0;
    }
    sf::Texture textureBackgroundMountain;
    if (!textureBackgroundMountain.loadFromFile(resourcePath() + "background.jpg")) {
        return 0;
    }
    sf::Texture textureBackgroundRiver;
    if (!textureBackgroundRiver.loadFromFile(resourcePath() + "riverBackground.jpg")) {
        return 0;
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
DeathMyDino:
    std::string myDinoOutput = vectorDinosReady[rand()%vectorDinosReady.size()];
    sf::Vector2i spriteSize(24,24);
    sf::Sprite myDino;
    myDino.setScale(6, 6);
    myDino.setPosition(100,300);
    int frameNum = 3;
    float animationDuration = 0.5;
    
    
    //enemyDino Sprite
DeathEnemyDino:
    idleAnimation(myDino, myDinoOutput);
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
    
    //title
    sf::Text battleTitle("Press enter to smash!",font);
    battleTitle.setFillColor(sf::Color::Red);
    battleTitle.setPosition(180, 60);
    battleTitle.setCharacterSize(70);
    
    //battle algorithm
    Kuro kuro = Kuro();
    Kuro kuroEnemy = Kuro();
    Loki loki = Loki();
    Loki lokiEnemy = Loki();
    Mono mono = Mono();
    Mono monoEnemy = Mono();
    bool needToDrawEnemy = true;
    if ( killCounter == 3) {
        showBattleWindow.close();
        winnerWindowPrint();
    }
    if (vectorDinosReady.size() == 0) {
    loose:
        showBattleWindow.close();
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
                showBattleWindow.draw(kuroCharacteristicsText);
                myDinoPicked = "Kuro";
                kuroCharacteristicsText.setPosition(100, 450);
                break;
            case 1:
                showBattleWindow.draw(lokiCharacteristicsText);
                myDinoPicked = "Loki";
                lokiCharacteristicsText.setPosition(100, 450);
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
                                if (myDinoPicked == "Kuro") {
                                    kuroEnemy.HP = kuroEnemy.HP - kuro.damage(randomTerrain);
                                    kuro.HP = kuro.HP - kuroEnemy.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(kuroEnemy.HP/100, 1);
                                    greenLineSprite.setScale(kuro.HP/100, 1);
                                    myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ myDinoOutput +"/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ enemyDinoOutput +"/hurt.png"));
                                }
                                if (myDinoPicked == "Loki") {
                                    kuroEnemy.HP = kuroEnemy.HP - loki.damage(randomTerrain);
                                    loki.HP = loki.HP - kuroEnemy.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(kuroEnemy.HP/100, 1);
                                    greenLineSprite.setScale(loki.HP/100, 1);
                                    myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ myDinoOutput +"/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ enemyDinoOutput +"/hurt.png"));
                                }
                                if (myDinoPicked == "Mono") {
                                    kuroEnemy.HP = kuroEnemy.HP - mono.damage(randomTerrain);
                                    mono.HP = mono.HP - kuroEnemy.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(kuroEnemy.HP/100, 1);
                                    greenLineSprite.setScale(mono.HP/100, 1);
                                    myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ myDinoOutput +"/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ enemyDinoOutput +"/hurt.png"));
                                }
                            }
                            else
                            {
                                ++killCounter;
                                goto DeathEnemyDino;
                            }
                            if (greenLineSprite.getScale().x == greenLineSpriteEnemy.getScale().x && greenLineSprite.getScale().x < 0.25) {
                                ++killCounter;
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
                                    vectorDinosReady.erase( std::remove(vectorDinosReady.begin(), vectorDinosReady.end(), myDinoPicked), vectorDinosReady.end() );
                                }
                                goto DeathMyDino;
                            }
                            
                            break;
                        case 1:
                            if (greenLineSpriteEnemy.getScale().x > 0.28 && greenLineSprite.getScale().x > 0.25)
                            {
                                if (myDinoPicked == "Kuro") {
                                    lokiEnemy.HP = lokiEnemy.HP - kuro.damage(randomTerrain);
                                    kuro.HP = kuro.HP - lokiEnemy.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(lokiEnemy.HP/100, 1);
                                    greenLineSprite.setScale(kuro.HP/100, 1);
                                    myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ myDinoOutput +"/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ enemyDinoOutput +"/hurt.png"));
                                }
                                if (myDinoPicked == "Loki") {
                                    lokiEnemy.HP = lokiEnemy.HP - loki.damage(randomTerrain);
                                    loki.HP = loki.HP - lokiEnemy.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(lokiEnemy.HP/100, 1);
                                    greenLineSprite.setScale(loki.HP/100, 1);
                                    myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ myDinoOutput +"/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ enemyDinoOutput +"/hurt.png"));
                                }
                                if (myDinoPicked == "Mono") {
                                    lokiEnemy.HP = lokiEnemy.HP - mono.damage(randomTerrain);
                                    mono.HP = mono.HP - lokiEnemy.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(lokiEnemy.HP/100, 1);
                                    greenLineSprite.setScale(mono.HP/100, 1);
                                    myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ myDinoOutput +"/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ enemyDinoOutput +"/hurt.png"));
                                }
                            }
                            else
                            {
                                ++killCounter;
                                goto DeathEnemyDino;
                            }
                            if (greenLineSprite.getScale().x == greenLineSpriteEnemy.getScale().x && greenLineSprite.getScale().x < 0.25) {
                                ++killCounter;
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
                                    vectorDinosReady.erase( std::remove(vectorDinosReady.begin(), vectorDinosReady.end(), myDinoPicked), vectorDinosReady.end() );
                                }
                                goto DeathMyDino;
                            }
                            
                            
                            break;
                        case 2:
                            if (greenLineSpriteEnemy.getScale().x > 0.28 && greenLineSprite.getScale().x > 0.25)
                            {
                                if (myDinoPicked == "Kuro") {
                                    monoEnemy.HP = monoEnemy.HP - kuro.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(monoEnemy.HP/100, 1);
                                    kuro.HP = kuro.HP - monoEnemy.damage(randomTerrain);
                                    greenLineSprite.setScale(kuro.HP/100, 1);
                                    myDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ myDinoOutput +"/hurt.png"));
                                    enemyDino.setTexture(AssetManager::GetTexture(resourcePath() + "dinoAssets/"+ enemyDinoOutput +"/hurt.png"));
                                }
                                if (myDinoPicked == "Loki") {
                                    monoEnemy.HP = monoEnemy.HP - loki.damage(randomTerrain);
                                    greenLineSpriteEnemy.setScale(monoEnemy.HP/100, 1);
                                    loki.HP = loki.HP - monoEnemy.damage(randomTerrain);
                                    greenLineSprite.setScale(loki.HP/100, 1);
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
                                goto DeathEnemyDino;
                            }
                            if (greenLineSprite.getScale().x == greenLineSpriteEnemy.getScale().x && greenLineSprite.getScale().x < 0.25) {
                                ++killCounter;
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

