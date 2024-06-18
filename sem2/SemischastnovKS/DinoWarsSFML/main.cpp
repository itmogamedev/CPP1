#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Converters.h"
#include "Dino.h"


std::ifstream readFile;
std::ofstream writeFile;

std::string line;
std::string terrain;
int x = 0;

char botDino;
int botDamage;
int bothp = 100;

char playerDino;
int playerDamage;
Player player;

DinoStr trex;
DinoStr trice;
DinoDex stego;
DinoInt diplo;
DinoInt brahi;

int HPClamp(int hp) {
    if (hp < 0) {
        return 0;
    }
    return hp;
}

int charToDmg(char n, const std::string &ter) {
    switch (n) {
        case 'b':
            return brahi.damage(ter);
        case 'd':
            return diplo.damage(ter);
        case 's':
            return stego.damage(ter);
        case 'r':
            return trex.damage(ter);
        case 't':
            return trice.damage(ter);
        default:
            return 0;
    }
}

void makeDinos() {
    trex.setSTR(30);
    trex.setDEX(15);
    trex.setINT(12);
    trex.setName("Tyrannosaurus");

    trice.setSTR(20);
    trice.setDEX(18);
    trice.setINT(15);
    trice.setName("Triceratops");

    stego.setSTR(15);
    stego.setDEX(30);
    stego.setINT(12);
    stego.setName("Stegosaurus");

    diplo.setSTR(20);
    diplo.setDEX(17);
    diplo.setINT(24);
    diplo.setName("Diplodocus");

    brahi.setSTR(15);
    brahi.setDEX(12);
    brahi.setINT(30);
    brahi.setName("Brachiosaurus");
}

std::string chooseTerrain() {
    x++;
    int n = (rand() - x) % 3;
    if (n == 0) {
        return "plain";
    }
    if (n == 1) {
        return "mountain";
    }
    if (n == 2) {
        return "river";
    }
    return "";
}

char randDino() {
    int n = (rand() + 1)% 5;
    switch (n) {
        case 0:
            return 'b';
        case 1:
            return 'd';
        case 2:
            return 's';
        case 3:
            return 'r';
        case 4:
            return 't';
        default:
            return 'n';
    }
}

void readData() {
    readFile.open("dino_data.txt");
    if (std::getline(readFile, line)) {
        player.setList(0,line[0]);
        player.setList(1,line[2]);
        player.setList(2,line[4]);
        player.setMoney(std::stoi(line.substr(6)));
    }
    readFile.close();
}

void writeData() {
    writeFile.open("dino_data.txt");
    writeFile << player.getList(0) << ' ' << player.getList(1) << ' ' << player.getList(2) << ' ' << player.getMoney();
    writeFile.close();
}

int main()
{
    makeDinos();
    readData();

    sf::RenderWindow window(sf::VideoMode(1000, 700), "Dino Wars");

    sf::Clock clock;
    float timer = 0;

    sf::Font font;
    font.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/ArialRegular.ttf");



    // MENU

    bool isMenu = true;
    int menuNum = 0;

    sf::Text moneyText("You have " + std::to_string(player.getMoney()) + " money", font, 36);
    moneyText.setFillColor(sf::Color::Black);
    moneyText.setPosition(50, 110);
    moneyText.setStyle(sf::Text::Bold);

    sf::Text dinosText("Your dinos:", font, 36);
    dinosText.setFillColor(sf::Color::Black);
    dinosText.setPosition(50, 180);
    dinosText.setStyle(sf::Text::Bold);

    sf::Text dino1Text("", font, 26);
    dino1Text.setFillColor(sf::Color::Black);
    dino1Text.setPosition(50, 230);
    dino1Text.setStyle(sf::Text::Bold);

    sf::Text dino2Text("", font, 26);
    dino2Text.setFillColor(sf::Color::Black);
    dino2Text.setPosition(50, 260);
    dino2Text.setStyle(sf::Text::Bold);

    sf::Text dino3Text("", font, 26);
    dino3Text.setFillColor(sf::Color::Black);
    dino3Text.setPosition(50, 290);
    dino3Text.setStyle(sf::Text::Bold);

    sf::Texture battleButton, shopButton, saveButton, exitButton;
    battleButton.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/battle.png");
    shopButton.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/shop.png");
    saveButton.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/save.png");
    exitButton.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/exit.png");
    sf::Sprite battle(battleButton), shop(shopButton), save(saveButton), exit(exitButton);
    battle.setPosition(625, 100);
    shop.setPosition(625, 200);
    save.setPosition(625, 300);
    exit.setPosition(625,400);



    // BATTLE

    bool isBattle = false;
    bool isFight = false;
    bool pTakeDamage = false;
    int is1TakingDamage = 0;
    int is2TakingDamage = 0;

    sf::Text battleText("In battle", font, 48);
    battleText.setOutlineColor(sf::Color::White);
    battleText.setOutlineThickness(2);
    battleText.setFillColor(sf::Color::Black);
    battleText.setPosition(50, 110);
    battleText.setStyle(sf::Text::Bold);

    sf::Text hp1Text("100", font, 48);
    hp1Text.setOutlineColor(sf::Color::White);
    hp1Text.setOutlineThickness(2);
    hp1Text.setFillColor(sf::Color::Black);
    hp1Text.setPosition(200, 500);
    hp1Text.setStyle(sf::Text::Bold);

    sf::Text hp2Text("100", font, 48);
    hp2Text.setOutlineColor(sf::Color::White);
    hp2Text.setOutlineThickness(2);
    hp2Text.setFillColor(sf::Color::Black);
    hp2Text.setPosition(700, 500);
    hp2Text.setStyle(sf::Text::Bold);

    sf::Texture dino1T, dino2T, terrainT;
    terrainT.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/plain.jpg");
    dino1T.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/" + charToFName('b'));
    dino2T.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/" + charToFName('d'));
    sf::Sprite dino1(dino1T), dino2(dino2T), terrainS(terrainT);
    terrainS.setPosition(0, 0);
    dino1.setPosition(50, 220);
    dino2.setPosition(550, 220);



    // WIN

    bool isPlayerWin = false;
    bool isBotWin = false;

    sf::Text pW("Player wins, earns 20 money", font, 50);
    pW.setOutlineColor(sf::Color::White);
    pW.setOutlineThickness(2);
    pW.setFillColor(sf::Color::Black);
    pW.setPosition(170, 300);
    pW.setStyle(sf::Text::Bold);

    sf::Text bW("Bot wins", font, 50);
    bW.setOutlineColor(sf::Color::White);
    bW.setOutlineThickness(2);
    bW.setFillColor(sf::Color::Black);
    bW.setPosition(400, 300);
    bW.setStyle(sf::Text::Bold);



    // SHOP

    bool isShop = false;
    int shopNum = 0;
    int curDinoNum = 0;

    sf::Text nameText(toName(curDinoNum), font, 30);
    nameText.setFillColor(sf::Color::Black);
    nameText.setPosition(770, 160);
    nameText.setStyle(sf::Text::Bold);

    sf::Text costText(toCost(curDinoNum), font, 25);
    costText.setFillColor(sf::Color::Black);
    costText.setPosition(800, 200);
    costText.setStyle(sf::Text::Bold);

    sf::Text strText(toSTR(curDinoNum), font, 20);
    strText.setFillColor(sf::Color::Black);
    strText.setPosition(800, 260);
    strText.setStyle(sf::Text::Bold);

    sf::Text intText(toINT(curDinoNum), font, 20);
    intText.setFillColor(sf::Color::Black);
    intText.setPosition(800, 290);
    intText.setStyle(sf::Text::Bold);

    sf::Text dexText(toDEX(curDinoNum), font, 20);
    dexText.setFillColor(sf::Color::Black);
    dexText.setPosition(800, 320);
    dexText.setStyle(sf::Text::Bold);

    sf::Texture curDinoImage, nextButton, buyButton, menuButton;
    curDinoImage.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/" + toFName(curDinoNum));
    nextButton.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/next.png");
    buyButton.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/buy.png");
    menuButton.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/menu.png");
    sf::Sprite curDino(curDinoImage), next(nextButton), buy(buyButton), menu(menuButton);
    curDino.setPosition(50, 180);
    next.setPosition(50, 580);
    buy.setPosition(350, 580);
    menu.setPosition(650, 580);



    // BUYING

    bool isBuying = false;
    int buyNum = 0;

    sf::Texture FButton, SButton, TButton;
    FButton.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/first.png");
    SButton.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/second.png");
    TButton.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/third.png");
    sf::Sprite first(FButton), second(SButton), third(TButton);
    first.setPosition(50, 580);
    second.setPosition(350, 580);
    third.setPosition(650, 580);

    while (window.isOpen())
    {
        window.clear(sf::Color(100,200,160));
        sf::Event event{};

        float time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
        clock.restart();
        time = time / 600;
        timer += time;
        if (timer > 10000) {
            timer -= 10000;
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (isMenu) {
                        if (menuNum == 1) {
                            isMenu = false;
                            isBattle = true;
                            player.setHP(100);
                            bothp = 100;
                            playerDino = player.getList(rand() % 3);
                            playerDamage = charToDmg(playerDino, terrain);
                            botDino = randDino();
                            botDamage = charToDmg(botDino, terrain);
                            hp1Text.setString(std::to_string(player.getHP()));
                            hp2Text.setString(std::to_string(bothp));
                            hp1Text.setFillColor(sf::Color::Black);
                            hp2Text.setFillColor(sf::Color::Black);
                            dino1.setPosition(50, 220);
                            dino2.setPosition(550, 220);
                        }
                        if (menuNum == 2) {
                            isMenu = false;
                            isShop = true;

                        }
                        if (menuNum == 3) {
                            writeData();
                        }
                        if (menuNum == 4) {
                            window.close();
                            isMenu = false;
                        }
                    }

                    if (isShop) {
                        if (shopNum == 1) {
                            curDinoNum = (curDinoNum + 1) % 5;
                            curDinoImage.loadFromFile(
                                    "/Users/elbias/CLionProjects/DInoWarsSFML/images/" + toFName(curDinoNum));
                            nameText.setString(toName(curDinoNum));
                            costText.setString("Cost: " + toCost(curDinoNum));
                            strText.setString(toSTR(curDinoNum));
                            intText.setString(toINT(curDinoNum));
                            dexText.setString(toDEX(curDinoNum));
                        }
                        if (shopNum == 2) {
                            isShop = false;
                            isBuying = true;
                        }
                        if (shopNum == 3) {
                            isShop = false;
                            isMenu = true;
                        }
                    }

                    if (isBuying) {
                        if (buyNum == 1) {
                            player.buyDino(std::stoi(toCost(curDinoNum)), toFName(curDinoNum)[0], 0);
                            isBuying = false;
                            isShop = true;
                        }
                        if (buyNum == 2) {
                            player.buyDino(std::stoi(toCost(curDinoNum)), toFName(curDinoNum)[0], 1);
                            isBuying = false;
                            isShop = true;
                        }
                        if (buyNum == 3) {
                            player.buyDino(std::stoi(toCost(curDinoNum)), toFName(curDinoNum)[0], 2);
                            isBuying = false;
                            isShop = true;
                        }
                    }
                }
            }
        }

        if (isMenu) {
            moneyText.setString("You have " + std::to_string(player.getMoney()) + " money");

            menuNum = 0;
            shopNum = 0;
            buyNum = 0;

            dino1Text.setString(toInfo(player.getList(0)));
            dino2Text.setString(toInfo(player.getList(1)));
            dino3Text.setString(toInfo(player.getList(2)));

            if (sf::IntRect(625, 100, 350, 80).contains(sf::Mouse::getPosition(window))) { menuNum = 1; }
            if (sf::IntRect(625, 200, 350, 80).contains(sf::Mouse::getPosition(window))) { menuNum = 2; }
            if (sf::IntRect(625, 300, 350, 80).contains(sf::Mouse::getPosition(window))) { menuNum = 3; }
            if (sf::IntRect(625, 400, 350, 80).contains(sf::Mouse::getPosition(window))) { menuNum = 4; }

            window.draw(moneyText);
            window.draw(dinosText);
            window.draw(dino1Text);
            window.draw(dino2Text);
            window.draw(dino3Text);

            window.draw(battle);
            window.draw(shop);
            window.draw(save);
            window.draw(exit);

            window.display();
        }

        if (isBattle) {
            if (terrain.empty()) {
                terrain = chooseTerrain();
            }
            if (timer > 3000) {
                isBattle = false;
                isFight = true;
                timer = 0;
            }
            terrainT.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/" + terrain + ".jpg");
            dino1T.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/" + charToFName(playerDino));
            dino2T.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/" + charToFName(botDino));

            window.draw(terrainS);

            window.draw(battleText);
            window.draw(hp1Text);
            window.draw(hp2Text);

            window.draw(dino1);
            window.draw(dino2);

            window.display();
        }

        if (isFight) {
            if (pTakeDamage and is1TakingDamage == 0 and timer > 1000) {
                is1TakingDamage = 1;
                timer = 0;
            }
            if (pTakeDamage and is1TakingDamage == 1 and timer > 200) {
                player.setHP(HPClamp(player.getHP() - botDamage));
                is1TakingDamage = 2;
                timer = 0;
                hp1Text.setFillColor(sf::Color::Red);
                dino2.setPosition(350, 220);
                hp1Text.setString(std::to_string(player.getHP()));
            }
            if (pTakeDamage and is1TakingDamage == 2 and timer > 400) {
                is1TakingDamage = 0;
                timer = 0;
                hp1Text.setFillColor(sf::Color::Black);
                dino2.setPosition(550, 220);
                pTakeDamage = false;
            }

            if (not pTakeDamage and is2TakingDamage == 0 and timer > 1000) {
                is2TakingDamage = 1;
                timer = 0;
            }
            if (not pTakeDamage and is2TakingDamage == 1 and timer > 200) {
                bothp = HPClamp(bothp - playerDamage);
                is2TakingDamage = 2;
                timer = 0;
                hp2Text.setFillColor(sf::Color::Red);
                dino1.setPosition(250, 220);
                hp2Text.setString(std::to_string(bothp));
            }
            if (not pTakeDamage and is2TakingDamage == 2 and timer > 400) {
                is2TakingDamage = 0;
                timer = 0;
                hp2Text.setFillColor(sf::Color::Black);
                dino1.setPosition(50, 220);
                pTakeDamage = true;
            }

            if (bothp <= 0) {
                dino2T.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/death.png");
                player.setMoney(player.getMoney() + 20);
                isFight = false;
                isPlayerWin = true;
            }
            if (player.getHP() <= 0) {
                dino1T.loadFromFile("/Users/elbias/CLionProjects/DInoWarsSFML/images/death.png");
                isFight = false;
                isBotWin = true;
            }

            window.draw(terrainS);

            window.draw(battleText);
            window.draw(hp1Text);
            window.draw(hp2Text);

            window.draw(dino1);
            window.draw(dino2);

            window.display();
        }

        if (isPlayerWin) {
            if (timer > 5000) {
                isPlayerWin = false;
                isMenu = true;
                terrain = "";
                timer = 0;
            }

            window.draw(battleText);
            window.draw(hp1Text);
            window.draw(hp2Text);

            window.draw(dino1);
            window.draw(dino2);

            window.draw(pW);

            window.display();
        }

        if (isBotWin) {
            if (timer > 5000) {
                isBotWin = false;
                isMenu = true;
                terrain = "";
                timer = 0;
            }

            window.draw(battleText);
            window.draw(hp1Text);
            window.draw(hp2Text);

            window.draw(dino1);
            window.draw(dino2);

            window.draw(bW);

            window.display();
        }

        if (isShop) {
            menuNum = 0;
            shopNum = 0;
            buyNum = 0;

            moneyText.setString("You have " + std::to_string(player.getMoney()) + " money");

            if (sf::IntRect(50, 580, 250, 80).contains(sf::Mouse::getPosition(window))) { shopNum = 1; }
            if (sf::IntRect(350, 580, 250, 80).contains(sf::Mouse::getPosition(window))) { shopNum = 2; }
            if (sf::IntRect(650, 580, 250, 80).contains(sf::Mouse::getPosition(window))) { shopNum = 3; }

            window.draw(moneyText);
            window.draw(nameText);
            window.draw(costText);
            window.draw(strText);
            window.draw(intText);
            window.draw(dexText);

            window.draw(curDino);
            window.draw(next);
            window.draw(buy);
            window.draw(menu);

            window.display();
        }

        if (isBuying) {
            menuNum = 0;
            shopNum = 0;
            buyNum = 0;

            moneyText.setString("Which slot?");

            if (sf::IntRect(50, 580, 250, 80).contains(sf::Mouse::getPosition(window))) { buyNum = 1; }
            if (sf::IntRect(350, 580, 250, 80).contains(sf::Mouse::getPosition(window))) { buyNum = 2; }
            if (sf::IntRect(650, 580, 250, 80).contains(sf::Mouse::getPosition(window))) { buyNum = 3; }

            window.draw(moneyText);
            window.draw(nameText);
            window.draw(costText);
            window.draw(strText);
            window.draw(intText);
            window.draw(dexText);

            window.draw(curDino);
            window.draw(first);
            window.draw(second);
            window.draw(third);

            window.display();
        }

    }
    writeData();
}