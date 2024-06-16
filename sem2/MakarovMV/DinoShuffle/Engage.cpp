#include "Engage.h"
#include "Structure.h"


std::vector<Dino*> getAllDinos() {
    return { new Tyranosaurus(), new Brahiosaurus(), new Diplodoc(), new Tryceraptops(), new Stegosaurus(), new Pterodactyl() };
}
std::vector<std::string> getnums() {
    std::vector<std::string> Dinomass;
    std::ifstream Dinostream("./Dinodata.data");
    std::string dino1;

    if (Dinostream.is_open()) {
        while (std::getline(Dinostream, dino1)) {
            Dinomass.push_back(dino1);
        }
        Dinostream.close();
    }

    return Dinomass;
}

std::vector<std::string> Nummass = getnums();

static std::vector<Dino*> owned = {};
std::vector<Dino*> getDinos() {
    std::vector<std::string> Nummass = getnums();
    std::vector<Dino*> owned;
    std::vector<Dino*> alldin = getAllDinos();

    for (const auto& num : Nummass) {
        int index = std::stoi(num);
        if (index >= 0 && index < alldin.size()) {
            owned.push_back(alldin[index]);
        }
    }
    return owned;
}
std::vector<Dino*> getoppDinos() {
    return { new Tyranosaurus(), new Brahiosaurus(), new Diplodoc(), new Tryceraptops(), new Stegosaurus(), new Pterodactyl() };
}


void handleDinoSelection(sf::RenderWindow& win, const sf::Vector2i& mousePoz, std::vector<int>& selectedDinos) {

    std::vector<Dino*> dinosaurus = getDinos();

    
    float x = 350.0f, y = 150.0f;
    for (auto& dino : dinosaurus) {
        dino->setPosition(x, y);
        win.draw(dino->getSprite());
        x += 500.0f; 
        if (x > win.getSize().x - 200) { 
            x = 100.0f;
            y += 400.0f;
        }
    }

    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for (int i = 0; i < dinosaurus.size(); ++i) {
            if (dinosaurus[i]->getSprite().getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                if ((selectedDinos.size() < 3) && (std::find(selectedDinos.begin(), selectedDinos.end(), i) == selectedDinos.end())) {
                    selectedDinos.push_back(i);
                    if (selectedDinos.size() == 3) {
                        break;
                    }
                }
            }
        }
    }
}




void Engage(sf::RenderWindow& win, const std::vector<int>& selectedDinos) {
    sf::Texture Texforback;
    sf::Texture TexEND;
    
    std::vector<Dino*> dinosaurus = getDinos();
    std::vector<Dino*> oppdinosaurus = getoppDinos();
    std::vector<Terrain> Terra{ Plain, River, Mountain };
    std::vector<std::string> Tr{ "Plain", "River", "Mountain" };
    float playerX=0; 
    float playerY = 0;
    float opponentX = 0;
    float opponentY = 0;
    int rnd = 0 + (std::rand() % (4));
    if (rnd == 0){
        if (!Texforback.loadFromFile("img/Field.jpg")) {
            std::cerr << "Error loading background texture" << std::endl;

        }
        playerX = 400.0f;
        playerY = 620.0f;
        opponentX = 1200.0f;
        opponentY = 620.0f;
    }
    if (rnd == 1) {
        if (!Texforback.loadFromFile("img/River.jpg")) {
            std::cerr << "Error loading background texture" << std::endl;

        }
        playerX = 400.0f;
        playerY = 500.0f;
        opponentX = 1200.0f;
        opponentY = 500.0f;
    }
    if (rnd == 2) {
        if (!Texforback.loadFromFile("img/Mountains.jpg")) {
            std::cerr << "Error loading background texture" << std::endl;
        }
        playerX = 400.0f; 
        playerY = 700.0f;
        opponentX = 1200.0f; 
        opponentY = 700.0f;
    }
    sf::RectangleShape background(sf::Vector2f(1920, 1080));
    background.setTexture(&Texforback);

    

    std::vector<int> dinopool = selectedDinos;
    std::vector<int> oppdinopool;

    for (int i = 0; i < 3; ++i) {
        int opponentIndex;
        do {
            opponentIndex = rand() % oppdinosaurus.size();
        } while ((std::find(oppdinopool.begin(), oppdinopool.end(), opponentIndex) != oppdinopool.end()) or (std::find(dinopool.begin(), dinopool.end(), opponentIndex) != dinopool.end()));
        oppdinopool.push_back(opponentIndex);
    }

    sf::Font juraFont;
    if (!juraFont.loadFromFile("Jura-Regular.ttf")) {
        std::cerr << "Error loading font\n";
    }

    sf::Font pressStart2PFont;
    if (!pressStart2PFont.loadFromFile("PressStart2P-Regular.ttf")) {
        std::cerr << "Error loading font\n";
    }

    sf::Text resultText;
    resultText.setFont(pressStart2PFont);
    resultText.setCharacterSize(50);
    resultText.setFillColor(sf::Color::White);
    resultText.setPosition(960.0f, 540.0f);
    resultText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::Text playerDinoText;
    playerDinoText.setFont(juraFont);
    playerDinoText.setCharacterSize(30);
    playerDinoText.setFillColor(sf::Color::Green);
    playerDinoText.setPosition(playerX, playerY - 50.0f);

    sf::Text opponentDinoText;
    opponentDinoText.setFont(juraFont);
    opponentDinoText.setCharacterSize(30);
    opponentDinoText.setFillColor(sf::Color::Red);
    opponentDinoText.setPosition(opponentX, opponentY - 50.0f);

    sf::Text TerraText;
    TerraText.setFont(juraFont);
    TerraText.setCharacterSize(35);
    TerraText.setFillColor(sf::Color::Green);
    TerraText.setPosition(100, 50);

    bool battleOver = false;
    std::string result;
    bool playerTurn = true;

    while (win.isOpen() && !battleOver) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                win.close();
            }
        }

        win.clear();
        TerraText.setString("Terra type: " + Tr[rnd]);

        win.draw(TerraText);
        win.draw(background);

        if (!dinopool.empty()) {
            Dino* playerDino = dinosaurus[dinopool[0]];

            playerDino->setPosition(playerX, playerY);
            int playerHP = playerDino->getHP() < 0 ? 0 : playerDino->getHP();
            playerDinoText.setString(playerDino->getinfo()[0] + " HP: " + std::to_string(playerHP));
            win.draw(playerDino->getSprite());
            win.draw(playerDinoText);
        }
        if (!oppdinopool.empty()) {
            Dino* oppDino = oppdinosaurus[oppdinopool[0]];
            oppDino->setPosition(opponentX, opponentY);

            
            oppDino->getSprite().setScale(-1.0f, 1.0f);

            int opponentHP = oppDino->getHP() < 0 ? 0 : oppDino->getHP();
            opponentDinoText.setString(oppDino->getinfo()[0] + " HP: " + std::to_string(opponentHP));

            win.draw(oppDino->getSprite());
            win.draw(opponentDinoText);
        }


        win.display();

        if (!dinopool.empty() && !oppdinopool.empty()) {
            Dino* playerDino = dinosaurus[dinopool[0]];
            Dino* oppDino = oppdinosaurus[oppdinopool[0]];

            if (playerTurn) {
                for (float dx = 0; dx <= 150; dx += 5) {
                    playerDino->setPosition(playerDino->getSprite().getPosition().x + 10, playerDino->getSprite().getPosition().y);
                    win.clear();
                    win.draw(background);
                    win.draw(TerraText);
                    win.draw(playerDinoText);
                    win.draw(opponentDinoText);
                    win.draw(playerDino->getSprite());
                    win.draw(oppDino->getSprite());
                    win.display();
                    sf::sleep(sf::milliseconds(10));
                }
                for (float dx = 0; dx <= 150; dx += 10) {
                    oppDino->setPosition(oppDino->getSprite().getPosition().x + 3, oppDino->getSprite().getPosition().y);
                    win.clear();
                    win.draw(background);
                    win.draw(TerraText);
                    win.draw(playerDinoText);
                    win.draw(opponentDinoText);
                    win.draw(playerDino->getSprite());
                    win.draw(oppDino->getSprite());
                    win.display();
                    sf::sleep(sf::milliseconds(10));
                }
                for (float dx = 0; dx <= 150; dx += 10) {
                    oppDino->setPosition(oppDino->getSprite().getPosition().x - 3, oppDino->getSprite().getPosition().y);
                    win.clear();
                    win.draw(background);
                    win.draw(TerraText);
                    win.draw(playerDinoText);
                    win.draw(opponentDinoText);
                    win.draw(playerDino->getSprite());
                    win.draw(oppDino->getSprite());
                    win.display();
                    sf::sleep(sf::milliseconds(10));
                }


                oppDino->reduceHP(playerDino->damage(Terra[rnd]));
                playerTurn = false;

                int opponentHP = oppDino->getHP() < 0 ? 0 : oppDino->getHP();
                opponentDinoText.setString(oppDino->getinfo()[0] + " HP: " + std::to_string(opponentHP));
                win.draw(opponentDinoText);

                for (float dx = 0; dx <= 150; dx += 5) {
                    playerDino->setPosition(playerDino->getSprite().getPosition().x - 10, playerDino->getSprite().getPosition().y);
                    win.clear();
                    win.draw(background);
                    win.draw(TerraText);
                    win.draw(playerDinoText);
                    win.draw(opponentDinoText);
                    win.draw(playerDino->getSprite());
                    win.draw(oppDino->getSprite());
                    win.display();
                    sf::sleep(sf::milliseconds(10));
                }

                if (oppDino->getHP() <= 0) {
                    oppDino->resetHP();
                    oppdinopool.erase(oppdinopool.begin());
                }
            }
            else {
                for (float dx = 0; dx <= 150; dx += 5) {
                    oppDino->setPosition(oppDino->getSprite().getPosition().x - 10, oppDino->getSprite().getPosition().y);
                    win.clear();
                    win.draw(background);
                    win.draw(TerraText);
                    win.draw(playerDinoText);
                    win.draw(opponentDinoText);
                    win.draw(playerDino->getSprite());
                    win.draw(oppDino->getSprite());
                    win.display();
                    sf::sleep(sf::milliseconds(10));
                }
                for (float dx = 0; dx <= 150; dx += 10) {
                    playerDino->setPosition(playerDino->getSprite().getPosition().x - 3, playerDino->getSprite().getPosition().y);
                    win.clear();
                    win.draw(background);
                    win.draw(TerraText);
                    win.draw(playerDinoText);
                    win.draw(opponentDinoText);
                    win.draw(playerDino->getSprite());
                    win.draw(oppDino->getSprite());
                    win.display();
                    sf::sleep(sf::milliseconds(10));
                }
                for (float dx = 0; dx <= 150; dx += 10) {
                    playerDino->setPosition(playerDino->getSprite().getPosition().x + 3, playerDino->getSprite().getPosition().y);
                    win.clear();
                    win.draw(background);
                    win.draw(TerraText);
                    win.draw(playerDinoText);
                    win.draw(opponentDinoText);
                    win.draw(playerDino->getSprite());
                    win.draw(oppDino->getSprite());
                    win.display();
                    sf::sleep(sf::milliseconds(10));
                }

                playerDino->reduceHP(oppDino->damage(Terra[rnd]));
                playerTurn = true;

                int playerHP = playerDino->getHP() < 0 ? 0 : playerDino->getHP();
                playerDinoText.setString(playerDino->getinfo()[0] + " HP: " + std::to_string(playerHP));
                win.draw(playerDinoText);

                for (float dx = 0; dx <= 150; dx += 5) {
                    oppDino->setPosition(oppDino->getSprite().getPosition().x + 10, oppDino->getSprite().getPosition().y);
                    win.clear();
                    win.draw(background);
                    win.draw(TerraText);
                    win.draw(playerDinoText);
                    win.draw(opponentDinoText);
                    win.draw(playerDino->getSprite());
                    win.draw(oppDino->getSprite());
                    win.display();
                    sf::sleep(sf::milliseconds(10));
                }
                if (playerDino->getHP() <= 0) {
                    playerDino->resetHP();
                    dinopool.erase(dinopool.begin());
                }
            }
        }

        sf::sleep(sf::seconds(1));
        
        if (!dinopool.empty() && oppdinopool.empty()) {
            result = "YOU WIN.\n\nYOU'VE GAINED\n\n 500 DINOBUCKS!!!";
            if (!TexEND.loadFromFile("img/Field.jpg")) {
                std::cerr << "Error loading background texture" << std::endl;

            }
                   
            int Moneyint = 0;
            std::ifstream money("./moneydata.data");
            std::string balance;

            if (money.is_open()) {
                while (std::getline(money, balance)) {
                    Moneyint = std::stoi(balance);
                }
                money.close();
            }
            std::ofstream filemon("moneydata.data", std::ios::trunc); 
            if (filemon.is_open()) {
                
                Moneyint = Moneyint+500;
                filemon << Moneyint; 
                
                filemon.close();
            }
            battleOver = true;
        }
        else if (dinopool.empty() && !oppdinopool.empty()) {
            result = "YOU LOSE.\n\nGOT NOTHING.";
            if (!TexEND.loadFromFile("img/Mountains.jpg")) {
                std::cerr << "Error loading background texture" << std::endl;

            }
            
            battleOver = true;
        }
    }

    if (battleOver) {
        resultText.setString(result);
        while (win.isOpen()) {
            sf::Event event;
            while (win.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    win.close();
                }
            }

            win.clear();
            sf::RectangleShape endbackground(sf::Vector2f(1920, 1080));
            endbackground.setTexture(&TexEND);
            win.draw(endbackground);
            win.draw(resultText);
            
            
            win.display();
            sf::sleep(sf::seconds(2));
            break;
        }
    }

    for (auto& dino : dinosaurus) {
        delete dino;
    }
    for (auto& oppDino : oppdinosaurus) {
        delete oppDino;
    }
}







