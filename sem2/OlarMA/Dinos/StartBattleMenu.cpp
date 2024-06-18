#include "Graphics.h"
#include "DatabaseFunc.h"

AssetManager manager;
bool needToDrawEnemyGrave = false;
bool needToDrawMyGrave = false;

void idleAnimation(sf::Sprite &sprite, std::string output) {
    sprite.setTexture(
            AssetManager::GetTexture("C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" + output + "/idle.png"));
}

auto callback = []() {
    std::cout << "Timer expired!" << std::endl;
};

void startingBattleWindowPrint() {

    int killCounter = 0;
    sf::RenderWindow battleWindow(sf::VideoMode(800, 600, 60), "DinoBattle", sf::Style::Resize);

    //vectors to post and pull from inventory
    std::vector<std::string> vector;
    std::vector<std::string> vectorDinosReady;

    //background
    sf::Texture textureBackground;
    if (!textureBackground.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/Resources/background.jpg")) {
        return;
    }
    sf::Sprite spriteBackground(textureBackground);


    //font
    sf::Font font;
    if (!font.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/Resources/blackberry.otf")) {
        return;
    }

    //TITLE
    sf::Text titleBattle("Choose your dino's", font);
    titleBattle.setFillColor(sf::Color::White);
    titleBattle.setCharacterSize(60);
    titleBattle.setPosition(sf::Vector2f(175, 20));
    titleBattle.setStyle(sf::Text::Bold);


    //dino button
    //BUTTON FOR KIRA
    sf::Text buttonKiraPickText;
    float buttonKiraPickTextWidth = buttonKiraPickText.getLocalBounds().width;
    float buttonKiraPickTextHeight = buttonKiraPickText.getLocalBounds().height;
    buttonKiraPickText.setFont(font);
    buttonKiraPickText.setStyle(sf::Text::Regular);
    buttonKiraPickText.setString("PICK");
    buttonKiraPickText.setFillColor(sf::Color::Black);
    buttonKiraPickText.setCharacterSize(55);
    buttonKiraPickText.setPosition(sf::Vector2f(85, 480));

    //BUTTON FOR COLE
    sf::Text buttonColePickText;
    float buttonColePickTextWidth = buttonColePickText.getLocalBounds().width;
    float buttonColePickTextTextHeight = buttonColePickText.getLocalBounds().height;
    buttonColePickText.setFont(font);
    buttonColePickText.setStyle(sf::Text::Regular);
    buttonColePickText.setString("PICK");
    buttonColePickText.setFillColor(sf::Color::Black);
    buttonColePickText.setCharacterSize(55);
    buttonColePickText.setPosition(sf::Vector2f(345, 480));

    //BUTTON FOR MONO
    sf::Text buttonMonoPickText;
    float buttonMonoPickTextWidth = buttonMonoPickText.getLocalBounds().width;
    float buttonMonoPickTextHeight = buttonMonoPickText.getLocalBounds().height;
    buttonMonoPickText.setFont(font);
    buttonMonoPickText.setStyle(sf::Text::Regular);
    buttonMonoPickText.setString("PICK");
    buttonMonoPickText.setFillColor(sf::Color::Black);
    buttonMonoPickText.setCharacterSize(55);
    buttonMonoPickText.setPosition(sf::Vector2f(595, 480));

    //button back
    sf::Texture backButton;
    sf::Sprite backButtonImage;
    if (!backButton.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/Resources/iconButtonBack.png"))
        std::cout << "Can't find the image" << std::endl;
    float backButtonWidth = backButtonImage.getLocalBounds().width;
    float backButtonHeight = backButtonImage.getLocalBounds().height;
    backButtonImage.setPosition(backButtonWidth, backButtonHeight);

    backButtonImage.setTexture(backButton);

    //button start battle
    sf::Texture startButton;
    sf::Sprite startButtonImage;
    if (!startButton.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/Resources/battleButton.png"))
        std::cout << "Can't find the image" << std::endl;
    startButtonImage.setPosition(700, 20);
    startButtonImage.setTexture(startButton);

    //dino background sprite
    //DINOS BACKGROUND SPRITE
    sf::Texture backgroundTextureForDinos;
    if (!backgroundTextureForDinos.loadFromFile(
            "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/dinosBackground.jpg"))
        std::cout << "Can't find the image" << std::endl;

    //dino sprite
    //KIRA SPRITE
    sf::Texture dinoKiraTexture;
    if (!dinoKiraTexture.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/Kira/idle.png"))
        std::cout << "Can't find the image" << std::endl;
    sf::Sprite dinoKiraSprite(dinoKiraTexture, sf::IntRect(0, 0, 24, 24));
    dinoKiraSprite.setPosition(50, 230);
    dinoKiraSprite.setScale(sf::Vector2f(7.0f, 7.0f));
    sf::Sprite backgroundKiraSpriteForDinos(backgroundTextureForDinos, sf::IntRect(0, 0, 24, 24));
    sf::Text kiraTextName("Kira ", font);
    kiraTextName.setCharacterSize(70);
    kiraTextName.setFillColor(sf::Color(0, 197, 208, 230));
    kiraTextName.setStyle(sf::Text::Bold);
    kiraTextName.setPosition(85, 150);
    backgroundKiraSpriteForDinos.setPosition(70, 230);
    backgroundKiraSpriteForDinos.setScale(sf::Vector2f(6.0f, 7.0f));
    sf::Text kiraCharacteristicsText(
            "STRENGTH - " + std::to_string(Kira().STRENGTH) + "\nDEXTERITY - " + std::to_string(Kira().DEXTERITY) +
            "\nINTELLIGENCE - " + std::to_string(Kira().INTELLIGENCE), font);
    kiraCharacteristicsText.setCharacterSize(25);
    kiraCharacteristicsText.setFillColor(sf::Color::White);
    kiraCharacteristicsText.setPosition(75, 400);

    //COLE SPRITE
    sf::Texture dinoColeTexture;
    if (!dinoColeTexture.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/Cole/idle.png"))
        std::cout << "Can't find the image" << std::endl;
    sf::Sprite dinoColeSprite(dinoColeTexture, sf::IntRect(0, 0, 24, 24));
    dinoColeSprite.setPosition(305, 230);
    dinoColeSprite.setScale(sf::Vector2f(7.0f, 7.0f));
    sf::Text coleTextName("Cole ", font);
    coleTextName.setCharacterSize(70);
    coleTextName.setFillColor(sf::Color(0, 197, 208, 230));
    coleTextName.setStyle(sf::Text::Bold);
    coleTextName.setPosition(340, 150);
    sf::Sprite backgroundColeSpriteForDinos(backgroundTextureForDinos, sf::IntRect(0, 0, 24, 24));
    backgroundColeSpriteForDinos.setPosition(325, 230);
    backgroundColeSpriteForDinos.setScale(sf::Vector2f(6.0f, 7.0f));
    sf::Text coleCharacteristicsText(
            "STRENGTH - " + std::to_string(Cole().STRENGTH) + "\nDEXTERITY - " + std::to_string(Cole().DEXTERITY) +
            "\nINTELLIGENCE - " + std::to_string(Cole().INTELLIGENCE), font);
    coleCharacteristicsText.setCharacterSize(25);
    coleCharacteristicsText.setFillColor(sf::Color::White);
    coleCharacteristicsText.setPosition(330, 400);

    //sprite MONO
    sf::Texture dinoMonoTexture;
    if (!dinoMonoTexture.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/Mono/idle.png"))
        std::cout << "Can't find the image" << std::endl;
    sf::Sprite dinoMonoSprite(dinoMonoTexture, sf::IntRect(0, 0, 24, 24));
    dinoMonoSprite.setPosition(550, 230);
    dinoMonoSprite.setScale(sf::Vector2f(7.0f, 7.0f));
    sf::Sprite backgroundMonoSpriteForDinos(backgroundTextureForDinos, sf::IntRect(0, 0, 24, 24));
    sf::Text monoTextName("Mono ", font);
    monoTextName.setCharacterSize(70);
    monoTextName.setFillColor(sf::Color(0, 197, 208, 230));
    monoTextName.setStyle(sf::Text::Bold);
    monoTextName.setPosition(585, 150);
    backgroundMonoSpriteForDinos.setPosition(570, 230);
    backgroundMonoSpriteForDinos.setScale(sf::Vector2f(6.0f, 7.0f));
    sf::Text monoCharacteristicsText(
            "STRENGTH - " + std::to_string(Mono().STRENGTH) + "\nDEXTERITY - " + std::to_string(Mono().DEXTERITY) +
            "\nINTELLIGENCE - " + std::to_string(Mono().INTELLIGENCE), font);
    monoCharacteristicsText.setCharacterSize(25);
    monoCharacteristicsText.setFillColor(sf::Color::White);
    monoCharacteristicsText.setPosition(575, 400);


    //counter text
    int dinoCounter = 0;
    sf::Text counterText(std::to_string(dinoCounter) + "/3", font);
    counterText.setFillColor(sf::Color(0, 197, 208, 230));
    counterText.setCharacterSize(30);
    counterText.setStyle(sf::Text::Bold);
    counterText.setPosition(730, 550);

    while (battleWindow.isOpen()) {


        sf::Event event;
        battleWindow.clear();
        battleWindow.draw(spriteBackground);
        battleWindow.draw(backgroundKiraSpriteForDinos);
        battleWindow.draw(backgroundColeSpriteForDinos);
        battleWindow.draw(backgroundMonoSpriteForDinos);
        battleWindow.draw(kiraTextName);
        battleWindow.draw(kiraCharacteristicsText);
        battleWindow.draw(coleTextName);
        battleWindow.draw(coleCharacteristicsText);
        battleWindow.draw(monoTextName);
        battleWindow.draw(monoCharacteristicsText);
        battleWindow.draw(backButtonImage);
        battleWindow.draw(buttonKiraPickText);
        battleWindow.draw(buttonColePickText);
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
            if (vector[i] == "Kira") {
                battleWindow.draw(dinoKiraSprite);
            }

            if (vector[i] == "Cole") {
                battleWindow.draw(dinoColeSprite);
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
                case sf::Event::MouseMoved: {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(battleWindow);
                    sf::Vector2f mousePosF(static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ));

                    //if for exit button
                    if (backButtonImage.getGlobalBounds().contains(mousePosF)) {
                        backButtonImage.setColor(sf::Color(250, 20, 20));
                    } else {
                        backButtonImage.setColor(sf::Color(255, 255, 255));
                    }

                    //if for battle button
                    if (startButtonImage.getGlobalBounds().contains(mousePosF)) {
                        startButtonImage.setColor(sf::Color(250, 20, 20));
                    } else {
                        startButtonImage.setColor(sf::Color(255, 255, 255));
                    }

                    //if for KIRA button
                    if (buttonKiraPickText.getGlobalBounds().contains(mousePosF) &&
                        buttonKiraPickText.getString() == "PICK") {
                        buttonKiraPickText.setFillColor(sf::Color(250, 20, 20));
                    } else if (buttonKiraPickText.getString() == "Picked") {
                        buttonKiraPickText.setFillColor(sf::Color::Red);
                    } else {
                        buttonKiraPickText.setFillColor(sf::Color::Black);
                    }

                    //if for COLE button
                    if (buttonColePickText.getGlobalBounds().contains(mousePosF) &&
                        buttonColePickText.getString() == "PICK") {
                        buttonColePickText.setFillColor(sf::Color(250, 20, 20));
                    } else if (buttonColePickText.getString() == "Picked") {
                        buttonColePickText.setFillColor(sf::Color::Red);
                    } else {
                        buttonColePickText.setFillColor(sf::Color::Black);
                    }
                    //if for MONO button
                    if (buttonMonoPickText.getGlobalBounds().contains(mousePosF) &&
                        buttonMonoPickText.getString() == "PICK") {
                        buttonMonoPickText.setFillColor(sf::Color(250, 20, 20));
                    } else if (buttonMonoPickText.getString() == "Picked") {
                        buttonMonoPickText.setFillColor(sf::Color::Red);
                    } else {
                        buttonMonoPickText.setFillColor(sf::Color::Black);
                    }
                }
                    break;
                case sf::Event::MouseButtonPressed: {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(battleWindow);
                    sf::Vector2f mousePosF(static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ));

                    //if for exit button
                    if (backButtonImage.getGlobalBounds().contains(mousePosF)) {
                        battleWindow.close();
                        menuWindowPrint();
                    }
                    //if for pick kira
                    if (buttonKiraPickText.getGlobalBounds().contains(mousePosF) &&
                        buttonKiraPickText.getString() == "PICK") {
                        dinoCounter++;
                        counterText.setString(std::to_string(dinoCounter) + "/3");
                        buttonKiraPickText.setFillColor(sf::Color::Red);
                        buttonKiraPickText.setString("Picked");
                        battleWindow.draw(counterText);
                        battleWindow.display();
                        vectorDinosReady.push_back(Kira().name);
                    }
                    //if for pick cole
                    if (buttonColePickText.getGlobalBounds().contains(mousePosF) &&
                        buttonColePickText.getString() == "PICK") {
                        dinoCounter++;
                        counterText.setString(std::to_string(dinoCounter) + "/3");
                        buttonColePickText.setFillColor(sf::Color::Red);
                        buttonColePickText.setString("Picked");
                        battleWindow.draw(counterText);
                        battleWindow.display();
                        vectorDinosReady.push_back(Cole().name);
                    }
                    //if for pick mono
                    if (buttonMonoPickText.getGlobalBounds().contains(mousePosF) &&
                        buttonMonoPickText.getString() == "PICK") {
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
                        start:
                        battleWindow.close();
                        sf::RenderWindow showBattleWindow(sf::VideoMode(800, 600, 60), "DinoBattle", sf::Style::Resize);

                        //hp icon
                        sf::Texture hpIcon;
                        sf::Sprite hpIconSprite;
                        if (!hpIcon.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/Resources/greenbar.png"))
                            std::cout << "Can't find the image" << std::endl;
                        hpIconSprite.setPosition(100, 250);
                        hpIconSprite.setTexture(hpIcon);



                        //hp icon
                        sf::Texture hpIconEnemy;
                        sf::Sprite hpIconSpriteEnemy;
                        if (!hpIconEnemy.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/Resources/greenbar.png"))
                            std::cout << "Can't find the image" << std::endl;
                        hpIconSpriteEnemy.setPosition(570, 250);
                        hpIconSpriteEnemy.setTexture(hpIconEnemy);


                        //mapping for string vector
                        std::map<std::string, int> hash;
                        hash["Kira"] = 0;
                        hash["Cole"] = 1;
                        hash["Mono"] = 2;

                        //kira characteristics
                        sf::Text kiraCharacteristicsText(
                                "STRENGTH - " + std::to_string(Kira().STRENGTH) + "\nDEXTERITY - " +
                                std::to_string(Kira().DEXTERITY) + "\nINTELLIGENCE - " +
                                std::to_string(Kira().INTELLIGENCE), font);
                        kiraCharacteristicsText.setCharacterSize(25);
                        kiraCharacteristicsText.setFillColor(sf::Color::White);

                        //cole characteristics
                        sf::Text coleCharacteristicsText(
                                "STRENGTH - " + std::to_string(Cole().STRENGTH) + "\nDEXTERITY - " +
                                std::to_string(Cole().DEXTERITY) + "\nINTELLIGENCE - " +
                                std::to_string(Cole().INTELLIGENCE), font);
                        coleCharacteristicsText.setCharacterSize(25);
                        coleCharacteristicsText.setFillColor(sf::Color::White);

                        //mono characteristics
                        sf::Text monoCharacteristicsText(
                                "STRENGTH - " + std::to_string(Mono().STRENGTH) + "\nDEXTERITY - " +
                                std::to_string(Mono().DEXTERITY) + "\nINTELLIGENCE - " +
                                std::to_string(Mono().INTELLIGENCE), font);
                        monoCharacteristicsText.setCharacterSize(25);
                        monoCharacteristicsText.setFillColor(sf::Color::White);

                        //background
                        sf::Texture textureBackgroundPlain;
                        if (!textureBackgroundPlain.loadFromFile(
                                "C:/Users/mikhail/CLionProjects/Dinosaur/Resources/plainBackground.jpg")) {
                            return;
                        }
                        sf::Texture textureBackgroundMountain;
                        if (!textureBackgroundMountain.loadFromFile(
                                "C:/Users/mikhail/CLionProjects/Dinosaur/Resources/background.jpg")) {
                            return;
                        }
                        sf::Texture textureBackgroundRiver;
                        if (!textureBackgroundRiver.loadFromFile(
                                "C:/Users/mikhail/CLionProjects/Dinosaur/Resources/riverBackground.jpg")) {
                            return;
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
                        std::string myDinoOutput = vectorDinosReady[rand() % vectorDinosReady.size()];
                        sf::Vector2i spriteSize(24, 24);
                        sf::Sprite myDino;
                        myDino.setScale(6, 6);
                        myDino.setPosition(100, 300);
                        int frameNum = 3;
                        float animationDuration = 0.5;


                        //enemyDino Sprite
                        DeathEnemyDino:
                        idleAnimation(myDino, myDinoOutput);
                        std::string enemyDinoOutput = vectorDinosReady[rand() % vectorDinosReady.size()];
                        sf::Sprite enemyDino;
                        idleAnimation(enemyDino, enemyDinoOutput);
                        enemyDino.setScale(-6, 6);
                        enemyDino.setPosition(715, 300);

                        //hp green line
                        sf::Texture greenLine;
                        sf::Sprite greenLineSprite;
                        if (!greenLine.loadFromFile(
                                "C:/Users/mikhail/CLionProjects/Dinosaur/Resources/greenbarUpper.png"))
                            std::cout << "Can't find the image" << std::endl;
                        greenLineSprite.setPosition(100, 265);
                        greenLineSprite.setTexture(greenLine);

                        sf::Time elapsedTime;
                        sf::Clock clock;
                        //hp green line
                        sf::Texture greenLineEnemy;
                        sf::Sprite greenLineSpriteEnemy;
                        if (!greenLineEnemy.loadFromFile(
                                "C:/Users/mikhail/CLionProjects/Dinosaur/Resources/greenbarUpper.png"))
                            std::cout << "Can't find the image" << std::endl;
                        greenLineSpriteEnemy.setPosition(570, 265);
                        greenLineSpriteEnemy.setTexture(greenLineEnemy);

                        //font
                        sf::Font font;
                        if (!font.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/Resources/blackberry.otf")) {
                            return;
                        }
                        //title
                        sf::Text battleTitle("Press enter to smash!", font);
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
                        if (killCounter == 3) {
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

                            int animFrame = static_cast<int>((timeAsSecond / animationDuration) *
                                                             static_cast<float>(frameNum)) % frameNum;

                            myDino.setTextureRect(sf::IntRect(animFrame * spriteSize.x, 0, spriteSize.x, spriteSize.y));
                            enemyDino.setTextureRect(
                                    sf::IntRect(animFrame * spriteSize.x, 0, spriteSize.x, spriteSize.y));
                            showBattleWindow.draw(myDino);
                            if (animFrame == frameNum - 1 && timeAsSecond >= 1.25f) {
                                myDino.setTexture(AssetManager::GetTexture(
                                        "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" + myDinoOutput +
                                        "/idle.png"));
                                enemyDino.setTexture(AssetManager::GetTexture(
                                        "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" + enemyDinoOutput +
                                        "/idle.png"));
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
                                                if (greenLineSpriteEnemy.getScale().x > 0.28 &&
                                                    greenLineSprite.getScale().x > 0.25) {
                                                    if (myDinoPicked == "Kira") {
                                                        kiraEnemy.HP = kiraEnemy.HP - kira.damage(randomTerrain);
                                                        kira.HP = kira.HP - kiraEnemy.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(kiraEnemy.HP / 100, 1);
                                                        greenLineSprite.setScale(kira.HP / 100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                myDinoOutput +
                                                                "/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                enemyDinoOutput +
                                                                "/hurt.png"));
                                                    }
                                                    if (myDinoPicked == "Cole") {
                                                        kiraEnemy.HP = kiraEnemy.HP - cole.damage(randomTerrain);
                                                        cole.HP = cole.HP - kiraEnemy.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(kiraEnemy.HP / 100, 1);
                                                        greenLineSprite.setScale(cole.HP / 100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                myDinoOutput +
                                                                "/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                enemyDinoOutput +
                                                                "/hurt.png"));
                                                    }
                                                    if (myDinoPicked == "Mono") {
                                                        kiraEnemy.HP = kiraEnemy.HP - mono.damage(randomTerrain);
                                                        mono.HP = mono.HP - kiraEnemy.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(kiraEnemy.HP / 100, 1);
                                                        greenLineSprite.setScale(mono.HP / 100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                myDinoOutput +
                                                                "/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                enemyDinoOutput +
                                                                "/hurt.png"));
                                                    }
                                                } else {
                                                    ++killCounter;
                                                    needToDrawEnemyGrave = true;
                                                    goto DeathEnemyDino;
                                                }
                                                if (greenLineSprite.getScale().x == greenLineSpriteEnemy.getScale().x &&
                                                    greenLineSprite.getScale().x < 0.25) {
                                                    ++killCounter;
                                                    needToDrawMyGrave = true;
                                                    needToDrawEnemyGrave = true;
                                                    if (vectorDinosReady.size() != 0) {
                                                        vectorDinosReady.erase(std::remove(vectorDinosReady.begin(),
                                                                                           vectorDinosReady.end(),
                                                                                           myDinoPicked),
                                                                               vectorDinosReady.end());
                                                    }
                                                    if (vectorDinosReady.size() == 0) {
                                                        goto loose;
                                                    }
                                                    goto start;
                                                }

                                                if (greenLineSprite.getScale().x < 0.25) {
                                                    if (vectorDinosReady.size() != 0) {
                                                        needToDrawMyGrave = true;
                                                        vectorDinosReady.erase(std::remove(vectorDinosReady.begin(),
                                                                                           vectorDinosReady.end(),
                                                                                           myDinoPicked),
                                                                               vectorDinosReady.end());
                                                    }
                                                    goto DeathMyDino;
                                                }

                                                break;
                                            case 1:
                                                if (greenLineSpriteEnemy.getScale().x > 0.28 &&
                                                    greenLineSprite.getScale().x > 0.25) {
                                                    if (myDinoPicked == "Kira") {
                                                        coleEnemy.HP = coleEnemy.HP - kira.damage(randomTerrain);
                                                        kira.HP = kira.HP - coleEnemy.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(coleEnemy.HP / 100, 1);
                                                        greenLineSprite.setScale(kira.HP / 100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                myDinoOutput +
                                                                "/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                enemyDinoOutput +
                                                                "/hurt.png"));
                                                    }
                                                    if (myDinoPicked == "Cole") {
                                                        coleEnemy.HP = coleEnemy.HP - cole.damage(randomTerrain);
                                                        cole.HP = cole.HP - coleEnemy.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(coleEnemy.HP / 100, 1);
                                                        greenLineSprite.setScale(cole.HP / 100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                myDinoOutput +
                                                                "/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                enemyDinoOutput +
                                                                "/hurt.png"));
                                                    }
                                                    if (myDinoPicked == "Mono") {
                                                        coleEnemy.HP = coleEnemy.HP - mono.damage(randomTerrain);
                                                        mono.HP = mono.HP - coleEnemy.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(coleEnemy.HP / 100, 1);
                                                        greenLineSprite.setScale(mono.HP / 100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                myDinoOutput +
                                                                "/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                enemyDinoOutput +
                                                                "/hurt.png"));
                                                    }
                                                } else {
                                                    ++killCounter;
                                                    needToDrawEnemy = false;
                                                    needToDrawEnemyGrave = true;
                                                    goto DeathEnemyDino;
                                                }
                                                if (greenLineSprite.getScale().x == greenLineSpriteEnemy.getScale().x &&
                                                    greenLineSprite.getScale().x < 0.25) {
                                                    ++killCounter;
                                                    needToDrawMyGrave = true;
                                                    needToDrawEnemyGrave = true;
                                                    if (vectorDinosReady.size() != 0) {
                                                        vectorDinosReady.erase(std::remove(vectorDinosReady.begin(),
                                                                                           vectorDinosReady.end(),
                                                                                           myDinoPicked),
                                                                               vectorDinosReady.end());
                                                    }
                                                    if (vectorDinosReady.size() == 0) {
                                                        goto loose;
                                                    }
                                                    goto start;
                                                }
                                                if (greenLineSprite.getScale().x < 0.25) {
                                                    if (vectorDinosReady.size() != 0) {
                                                        needToDrawMyGrave = true;
                                                        vectorDinosReady.erase(std::remove(vectorDinosReady.begin(),
                                                                                           vectorDinosReady.end(),
                                                                                           myDinoPicked),
                                                                               vectorDinosReady.end());
                                                    }
                                                    goto DeathMyDino;
                                                }


                                                break;
                                            case 2:
                                                if (greenLineSpriteEnemy.getScale().x > 0.28 &&
                                                    greenLineSprite.getScale().x > 0.25) {
                                                    if (myDinoPicked == "Kira") {
                                                        monoEnemy.HP = monoEnemy.HP - kira.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(monoEnemy.HP / 100, 1);
                                                        kira.HP = kira.HP - monoEnemy.damage(randomTerrain);
                                                        greenLineSprite.setScale(kira.HP / 100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                myDinoOutput +
                                                                "/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                enemyDinoOutput +
                                                                "/hurt.png"));
                                                    }
                                                    if (myDinoPicked == "Cole") {
                                                        monoEnemy.HP = monoEnemy.HP - cole.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(monoEnemy.HP / 100, 1);
                                                        cole.HP = cole.HP - monoEnemy.damage(randomTerrain);
                                                        greenLineSprite.setScale(cole.HP / 100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                myDinoOutput +
                                                                "/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                enemyDinoOutput +
                                                                "/hurt.png"));
                                                    }
                                                    if (myDinoPicked == "Mono") {
                                                        monoEnemy.HP = monoEnemy.HP - mono.damage(randomTerrain);
                                                        greenLineSpriteEnemy.setScale(monoEnemy.HP / 100, 1);
                                                        mono.HP = mono.HP - monoEnemy.damage(randomTerrain);
                                                        greenLineSprite.setScale(mono.HP / 100, 1);
                                                        myDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                myDinoOutput +
                                                                "/hurt.png"));
                                                        enemyDino.setTexture(AssetManager::GetTexture(
                                                                "C:/Users/mikhail/CLionProjects/Dinosaur/dinoAssets/" +
                                                                enemyDinoOutput +
                                                                "/hurt.png"));
                                                    }
                                                } else {
                                                    ++killCounter;
                                                    needToDrawEnemy = false;
                                                    needToDrawEnemyGrave = true;
                                                    goto DeathEnemyDino;
                                                }
                                                if (greenLineSprite.getScale().x == greenLineSpriteEnemy.getScale().x &&
                                                    greenLineSprite.getScale().x < 0.25) {
                                                    ++killCounter;
                                                    needToDrawMyGrave = true;
                                                    needToDrawEnemyGrave = true;
                                                    if (vectorDinosReady.size() != 0) {
                                                        vectorDinosReady.erase(std::remove(vectorDinosReady.begin(),
                                                                                           vectorDinosReady.end(),
                                                                                           myDinoPicked),
                                                                               vectorDinosReady.end());
                                                    }
                                                    if (vectorDinosReady.size() == 0) {
                                                        goto loose;
                                                    }
                                                    goto start;
                                                }
                                                if (greenLineSprite.getScale().x < 0.25) {
                                                    if (vectorDinosReady.size() != 0) {
                                                        needToDrawMyGrave = true;
                                                        vectorDinosReady.erase(std::remove(vectorDinosReady.begin(),
                                                                                           vectorDinosReady.end(),
                                                                                           myDinoPicked),
                                                                               vectorDinosReady.end());
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
                }
                    break;
            }
        }
    }
}
