#include <SFML/Graphics.hpp>
#include "Dino.h"
#include "Player.h"
#include "Graphics.h"

using namespace sf;



void dinoBattle(Player& player, Graphics& graphics, RenderWindow& window, int& pageID)
{
    bool exit = false;
    // Choosing battle terrain
    Terrain battleTerrain;
    switch (rand() % 3)
    {
    case 0:
        battleTerrain = Terrain::Plain;
        graphics.battleLocationText.setString("Battle terrain: Plain");
        graphics.battleBackgroundSprite = graphics.plainBGSprite;
        break;

    case 1:
        battleTerrain = Terrain::River;
        graphics.battleLocationText.setString("Battle terrain: River");
        graphics.battleBackgroundSprite = graphics.riverBGSprite;
        break;

    case 2:
        battleTerrain = Terrain::Mountain;
        graphics.battleLocationText.setString("Battle terrain: Mountain");
        graphics.battleBackgroundSprite = graphics.mountainBGSprite;
        break;
    }


    //The number of dinosaurs participating in the battle:  1 - 3
    const int dinoBattleCount = rand() % 3 + 1;

    std::vector<int> playerDinoNums = { 0, 0, 0 };
    Dino** playerDinoList = new Dino * [dinoBattleCount];

    std::vector<int> enemyDinoNums = { 0, 0, 0 };
    Dino** enemyDinoList = new Dino * [dinoBattleCount];


    //Generating enemies dinos
    for (int i = 0; i < dinoBattleCount; i++)
    {
        int enemyDinoID = rand() % 5 + 1;

        switch (enemyDinoID)
        {
        case 1:
            enemyDinoList[i] = new DinoSpin;
            break;

        case 2:
            enemyDinoList[i] = new DinoDipl;
            break;

        case 3:
            enemyDinoList[i] = new DinoSteg;
            break;

        case 4:
            enemyDinoList[i] = new DinoBrach;
            break;

        case 5:
            enemyDinoList[i] = new DinoTyran;
            break;
        }
    }

    bool isDinosSelected = false;
    int selectedDinosCount = 0;
    std::list<int> selectedDinosNums;

    for (int i = 0; i < 15; ++i)
    {
        graphics.selectedDinos[i] = false;
    }

    while (true)
    {
        Vector2i mousePos = Mouse::getPosition(window);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        //Displaying enemies dinos
        std::string tmpStr = "Enemy dinos count: ";
        tmpStr += std::to_string(dinoBattleCount);
        graphics.enemyDinosCountText.setString(tmpStr);
        if (dinoBattleCount == 1)
        {
            std::string str1 = "1. ";
            str1 += enemyDinoList[0]->getDinoName();
            graphics.enemy1DinoText.setString(str1);
            graphics.enemy2DinoText.setString("");
            graphics.enemy3DinoText.setString("");
        }
        else if (dinoBattleCount == 2)
        {
            std::string str1 = "1. ";
            str1 += enemyDinoList[0]->getDinoName();
            graphics.enemy1DinoText.setString(str1);
            str1 = "2. ";
            str1 += enemyDinoList[1]->getDinoName();
            graphics.enemy2DinoText.setString(str1);
            graphics.enemy3DinoText.setString("");
        }
        else
        {
            std::string str1 = "1. ";
            str1 += enemyDinoList[0]->getDinoName();
            graphics.enemy1DinoText.setString(str1);
            str1 = "2. ";
            str1 += enemyDinoList[1]->getDinoName();
            graphics.enemy2DinoText.setString(str1);
            str1 = "3. ";
            str1 += enemyDinoList[1]->getDinoName();
            graphics.enemy3DinoText.setString(str1);
        }

        std::string dinosList = "";
        for (int i = 0; i < player.dinoCount; ++i)
        {
            dinosList += std::to_string(i + 1) + ".  " + player.playerDinos[i]->getDinoName() + "\n";
        }
        graphics.dinosListBattleText.setString(dinosList);

        window.draw(graphics.battleBackgroundSprite);
        window.draw(graphics.battleLocationText);

        window.draw(graphics.enemyDinosCountText);
        window.draw(graphics.chooseYourDinosText);

        window.draw(graphics.enemy1DinoText);
        window.draw(graphics.enemy2DinoText);
        window.draw(graphics.enemy3DinoText);

        window.draw(graphics.dinosListBattleText);
        for (int i = 0; i < player.dinoCount; ++i)
        {
            if (!graphics.selectedDinos[i])
                graphics.selectDinoButton[i].setTexture(graphics.selectDinoButtonTexture);
            else graphics.selectDinoButton[i].setTexture(graphics.unselectDinoButtonTexture);
        }

        window.draw(graphics.backToMainMenuButton);

        for (int i = 0; i < player.dinoCount; ++i)
        {
            if (Mouse::isButtonPressed(Mouse::Left) && graphics.selectDinoButton[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                if (!graphics.selectedDinos[i])
                {
                    graphics.selectedDinos[i] = true;
                    selectedDinosCount++;
                    selectedDinosNums.push_back(i + 1);
                    waitForSeconds(1);
                }
                else
                {
                    graphics.selectedDinos[i] = false;
                    selectedDinosCount--;
                    selectedDinosNums.remove(i + 1);
                    waitForSeconds(1);
                }
            }
        }

        if (selectedDinosCount == dinoBattleCount)
        {
            for (int i = 0; i < player.dinoCount; ++i)
            {
                if (graphics.selectedDinos[i])
                {
                    window.draw(graphics.selectDinoButton[i]);
                }
            }
            window.draw(graphics.startBattleButton);
        }
        else
        {
            for (int i = 0; i < player.dinoCount; ++i)
            {
                window.draw(graphics.selectDinoButton[i]);
            }
        }

        if (Mouse::isButtonPressed(Mouse::Left) && graphics.backToMainMenuButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            pageID = 0;
            exit = true;
            break;
        }

        if (selectedDinosCount == dinoBattleCount && Mouse::isButtonPressed(Mouse::Left) && graphics.startBattleButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            break;
        }

        window.display();
    }

    if (exit)
    {
        for (int i = 0; i < dinoBattleCount; i++)
        {
            delete enemyDinoList[i];
        }
        delete[] enemyDinoList;
        return;
    }

    int tmp = 0;
    for (auto element : selectedDinosNums)
    {
        playerDinoNums[tmp] = element;
        tmp++;
    }

    for (int i = 0; i < dinoBattleCount; ++i)
    {
        playerDinoList[i] = player.playerDinos[playerDinoNums[i]-1];
    }

    // Choosing dinos for battle

    Dino* currentPlayerDino = playerDinoList[0];
    Dino* currentEnemyDino = enemyDinoList[0];

    int playerDinoNumber = 0;
    int enemyDinoNumber = 0;

    bool playerWin = false;
    bool playerLose = false;

    graphics.playerDinoSprite.setTexture(graphics.dinoTexture[currentPlayerDino->dinoID - 1], false);
    graphics.enemyDinoSprite.setTexture(graphics.dinoTexture[currentEnemyDino->dinoID - 1], false);

    graphics.enemyDinoSprite.setScale(1.5f, 1.5f);
    graphics.playerDinoSprite.setScale(1.5f, 1.5f);
    graphics.enemyDinoSprite.setPosition(1000, 200);
    graphics.playerDinoSprite.setPosition(100, 200);


    auto rect = graphics.playerDinoSprite.getTextureRect();
    if (rect.width >= 0)
    {
        rect.left += rect.width;
        rect.width = -rect.width;
        graphics.playerDinoSprite.setTextureRect(rect);
    }

    for (int i = 0; i < dinoBattleCount; ++i)
    {
        playerDinoList[i]->updateHP(playerDinoList[i]->getMaxHP());
    }


    // Starting battle
    while (true)
    {
        Vector2i mousePos = Mouse::getPosition(window);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (playerWin == true || playerLose == true)
        {
            window.clear();
            window.draw(graphics.battleBackgroundSprite);
            window.draw(graphics.backToMainMenuButton);

            if (playerWin && playerLose)
                window.draw(graphics.drawText);

            else if (playerWin)
                window.draw(graphics.winText);
            else window.draw(graphics.loseText);

            if (Mouse::isButtonPressed(Mouse::Left) && graphics.backToMainMenuButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                pageID = 0;
                break;
            }

            window.display();
        }

        else
        {
            graphics.playerDinoSprite.setTexture(graphics.dinoTexture[currentPlayerDino->dinoID - 1], false);
            graphics.enemyDinoSprite.setTexture(graphics.dinoTexture[currentEnemyDino->dinoID - 1], false);
            graphics.playerDinoSprite.setPosition(550, 200);
            graphics.playerDinoSprite.setScale(1.5f, 1.5f);
            graphics.enemyDinoSprite.setPosition(1000, 200);
            graphics.enemyDinoSprite.setScale(1.5f, 1.5f);

            window.draw(graphics.battleBackgroundSprite);
            window.draw(graphics.enemyDinoSprite);
            window.draw(graphics.playerDinoSprite);

            if (currentEnemyDino != NULL || currentPlayerDino != NULL)
            {
                currentEnemyDino->updateHP(currentEnemyDino->getHP() - currentPlayerDino->damage(battleTerrain));
                graphics.punchSound.play();

                graphics.SetText(graphics.playerHPText, "HP: " + std::to_string(currentPlayerDino->getHP()), 50, Color::White, 410, 800);
                graphics.SetText(graphics.enemyHPText, "HP: " + std::to_string(currentEnemyDino->getHP()), 50, Color::White, 1250, 800);

                graphics.SetText(graphics.playerDinosLeftText, "Dinos left: " + std::to_string(dinoBattleCount - playerDinoNumber), 50, Color::White, 400, 200);
                graphics.SetText(graphics.enemyDinosLeftText, "Dinos left: " + std::to_string(dinoBattleCount - enemyDinoNumber), 50, Color::White, 1250, 200);

                window.draw(graphics.playerHPText);
                window.draw(graphics.enemyHPText);
                window.draw(graphics.playerDinosLeftText);
                window.draw(graphics.enemyDinosLeftText);

                int rand2 = rand() % 5;
                window.draw(graphics.damageSprite[rand2 + 5]);

                if (currentEnemyDino->getHP() <= 0)
                {
                    graphics.deathSound.play();

                    enemyDinoNumber++;
                    currentEnemyDino = enemyDinoList[enemyDinoNumber];

                    if (enemyDinoNumber == dinoBattleCount)
                        playerWin = true;

                    window.draw(graphics.getDamageSprite[3]);
                    window.draw(graphics.getDamageSprite[4]);
                    window.draw(graphics.getDamageSprite[5]);
                }

                window.display();
                waitForSeconds(1);
                window.clear();

                if (!playerWin)
                {
                    graphics.playerDinoSprite.setTexture(graphics.dinoTexture[currentPlayerDino->dinoID - 1], false);
                    graphics.enemyDinoSprite.setTexture(graphics.dinoTexture[currentEnemyDino->dinoID - 1], false);
                    graphics.enemyDinoSprite.setPosition(1000, 200);
                    graphics.enemyDinoSprite.setScale(1.5f, 1.5f);
                    graphics.playerDinoSprite.setPosition(100, 200);
                    graphics.playerDinoSprite.setScale(1.5f, 1.5f);

                    window.draw(graphics.battleBackgroundSprite);
                    window.draw(graphics.enemyDinoSprite);
                    window.draw(graphics.playerDinoSprite);

                    graphics.SetText(graphics.playerHPText, "HP: " + std::to_string(currentPlayerDino->getHP()), 50, Color::White, 410, 800);
                    graphics.SetText(graphics.enemyHPText, "HP: " + std::to_string(currentEnemyDino->getHP()), 50, Color::White, 1250, 800);

                    graphics.SetText(graphics.playerDinosLeftText, "Dinos left: " + std::to_string(dinoBattleCount - playerDinoNumber), 50, Color::White, 400, 200);
                    graphics.SetText(graphics.enemyDinosLeftText, "Dinos left: " + std::to_string(dinoBattleCount - enemyDinoNumber), 50, Color::White, 1250, 200);

                    window.draw(graphics.playerHPText);
                    window.draw(graphics.enemyHPText);
                    window.draw(graphics.playerDinosLeftText);
                    window.draw(graphics.enemyDinosLeftText);

                    window.display();
                    waitForSeconds(1);
                }

                if (!playerWin)
                {
                    graphics.playerDinoSprite.setTexture(graphics.dinoTexture[currentPlayerDino->dinoID - 1], false);
                    graphics.enemyDinoSprite.setTexture(graphics.dinoTexture[currentEnemyDino->dinoID - 1], false);
                    graphics.enemyDinoSprite.setPosition(550, 200);
                    graphics.enemyDinoSprite.setScale(1.5f, 1.5f);
                    graphics.playerDinoSprite.setPosition(100, 200);
                    graphics.playerDinoSprite.setScale(1.5f, 1.5f);

                    window.draw(graphics.battleBackgroundSprite);
                    window.draw(graphics.enemyDinoSprite);
                    window.draw(graphics.playerDinoSprite);

                    currentPlayerDino->updateHP(currentPlayerDino->getHP() - currentEnemyDino->damage(battleTerrain));
                    graphics.punchSound.play();

                    graphics.SetText(graphics.playerHPText, "HP: " + std::to_string(currentPlayerDino->getHP()), 50, Color::White, 410, 800);
                    graphics.SetText(graphics.enemyHPText, "HP: " + std::to_string(currentEnemyDino->getHP()), 50, Color::White, 1250, 800);

                    graphics.SetText(graphics.playerDinosLeftText, "Dinos left: " + std::to_string(dinoBattleCount - playerDinoNumber), 50, Color::White, 400, 200);
                    graphics.SetText(graphics.enemyDinosLeftText, "Dinos left: " + std::to_string(dinoBattleCount - enemyDinoNumber), 50, Color::White, 1250, 200);

                    window.draw(graphics.playerHPText);
                    window.draw(graphics.enemyHPText);
                    window.draw(graphics.playerDinosLeftText);
                    window.draw(graphics.enemyDinosLeftText);

                    int rand1 = rand() % 5;
                    window.draw(graphics.damageSprite[rand1]);

                    if (currentPlayerDino->getHP() <= 0)
                    {
                        graphics.deathSound.play();

                        currentPlayerDino->updateHP(currentPlayerDino->getMaxHP());
                        playerDinoNumber++;
                        currentPlayerDino = playerDinoList[playerDinoNumber];

                        if (playerDinoNumber == dinoBattleCount)
                            playerLose = true;

                        window.draw(graphics.getDamageSprite[0]);
                        window.draw(graphics.getDamageSprite[1]);
                        window.draw(graphics.getDamageSprite[2]);
                    }

                    window.display();
                    waitForSeconds(1);
                    window.clear();

                    if (!playerLose)
                    {
                        graphics.playerDinoSprite.setTexture(graphics.dinoTexture[currentPlayerDino->dinoID - 1], false);
                        graphics.enemyDinoSprite.setTexture(graphics.dinoTexture[currentEnemyDino->dinoID - 1], false);
                        graphics.enemyDinoSprite.setPosition(1000, 200);
                        graphics.enemyDinoSprite.setScale(1.5f, 1.5f);
                        graphics.playerDinoSprite.setPosition(100, 200);
                        graphics.playerDinoSprite.setScale(1.5f, 1.5f);

                        window.draw(graphics.battleBackgroundSprite);
                        window.draw(graphics.enemyDinoSprite);
                        window.draw(graphics.playerDinoSprite);

                        graphics.SetText(graphics.playerHPText, "HP: " + std::to_string(currentPlayerDino->getHP()), 50, Color::White, 410, 800);
                        graphics.SetText(graphics.enemyHPText, "HP: " + std::to_string(currentEnemyDino->getHP()), 50, Color::White, 1250, 800);

                        graphics.SetText(graphics.playerDinosLeftText, "Dinos left: " + std::to_string(dinoBattleCount - playerDinoNumber), 50, Color::White, 400, 200);
                        graphics.SetText(graphics.enemyDinosLeftText, "Dinos left: " + std::to_string(dinoBattleCount - enemyDinoNumber), 50, Color::White, 1250, 200);

                        window.draw(graphics.playerHPText);
                        window.draw(graphics.enemyHPText);
                        window.draw(graphics.playerDinosLeftText);
                        window.draw(graphics.enemyDinosLeftText);

                        window.display();
                        waitForSeconds(1);
                    }
                }
            }

            if (playerWin == true || playerLose == true)
            {
                if (playerWin == true && playerLose == false)
                {
                    player.playerMoney += 500;
                }
            }
        }
    }

    for (int i = 0; i < dinoBattleCount; i++)
    {
        delete enemyDinoList[i];
    }
    delete[] enemyDinoList;
}



int main()
{
    srand(time(0));
    std::ifstream loadGame;
    loadGame.open("savedGameFile.txt", std::ios::binary | std::ios::app);
    Player player;

    // Loading game
    std::string str;
    std::string playerMoneyInput = "";
    std::string playerDinosInput = "";

    while (std::getline(loadGame, str))
    {
        if (playerMoneyInput == "") playerMoneyInput = str;
        else playerDinosInput = str;
    }

    player.playerMoney = std::stoi(playerMoneyInput);

    std::vector<std::string> playerDinosSplit = splitString(playerDinosInput);
    for (int i = 0; i < playerDinosSplit.size(); i++)
    {
        int dinoID = std::stoi(playerDinosSplit[i]);

        player.addDino(dinoID);
    }


    std::vector<int> dinoCost{ 1200, 1500, 2000, 2000, 2500 };

    RenderWindow window(VideoMode(1920, 1080), L"Dino Battle", Style::Default);

    int pageID = 0;

    Graphics graphics;

    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        Vector2i mousePos = Mouse::getPosition(window);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        
        window.clear();

        switch (pageID)
        {
        case 0:
        {
            window.draw(graphics.mainMenuBackgroundSprite);
            window.draw(graphics.battleButton);
            window.draw(graphics.shopButton);
            window.draw(graphics.dinoListButton);
            window.draw(graphics.quitButton);
        }
        break;

        case 1:
        {
            //window.draw(graphics.battleBackgroundSprite);
            //window.draw(graphics.backToMainMenuButton);
        }
        break;

        case 2:
        {
            std::string playerMoney = "Your money: ";
            playerMoney += std::to_string(player.playerMoney);
            graphics.playerMoneyShopText.setString(playerMoney);

            window.draw(graphics.shopMenuBackgroundSprite);

            window.draw(graphics.dino1BuySprite);
            window.draw(graphics.dino2BuySprite);
            window.draw(graphics.dino3BuySprite);
            window.draw(graphics.dino4BuySprite);
            window.draw(graphics.dino5BuySprite);

            window.draw(graphics.buy1Button);
            window.draw(graphics.buy2Button);
            window.draw(graphics.buy3Button);
            window.draw(graphics.buy4Button);
            window.draw(graphics.buy5Button);

            window.draw(graphics.playerMoneyShopText);

            window.draw(graphics.backToMainMenuButton);

            if (event.type == Event::MouseButtonPressed)
            {
                if (graphics.buy1Button.getGlobalBounds().contains(mousePos.x, mousePos.y) && player.playerMoney >= dinoCost[0])
                {
                    player.playerMoney -= dinoCost[0];
                    player.addDino(1);
                    waitForSeconds(2);
                }

                if (graphics.buy2Button.getGlobalBounds().contains(mousePos.x, mousePos.y) && player.playerMoney >= dinoCost[1])
                {
                    player.playerMoney -= dinoCost[1];
                    player.addDino(2);
                    waitForSeconds(2);
                }

                if (graphics.buy3Button.getGlobalBounds().contains(mousePos.x, mousePos.y) && player.playerMoney >= dinoCost[2])
                {
                    player.playerMoney -= dinoCost[2];
                    player.addDino(3);
                    waitForSeconds(2);
                }

                if (graphics.buy4Button.getGlobalBounds().contains(mousePos.x, mousePos.y) && player.playerMoney >= dinoCost[3])
                {
                    player.playerMoney -= dinoCost[3];
                    player.addDino(4);
                    waitForSeconds(2);
                }

                if (graphics.buy5Button.getGlobalBounds().contains(mousePos.x, mousePos.y) && player.playerMoney >= dinoCost[4])
                {
                    player.playerMoney -= dinoCost[4];
                    player.addDino(5);
                    waitForSeconds(2);
                }
            }
        }
        break;

        case 3:
        {
            window.draw(graphics.shopMenuBackgroundSprite);

            window.draw(graphics.yourDinosText);

            std::string dinosList = "";
            for (int i = 0; i < player.dinoCount; ++i)
            {
                dinosList += std::to_string(i+1) + ".  " + player.playerDinos[i]->getDinoName() + "\n";
            }
            graphics.dinosListText.setString(dinosList);
            window.draw(graphics.dinosListText);

            window.draw(graphics.backToMainMenuButton);
        }
        break;
        }
        window.display();


        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (graphics.battleButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && pageID == 0)
            {
                window.clear();
                pageID = 1;
                dinoBattle(player, graphics, window, pageID);
            }

            if (graphics.shopButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && pageID == 0)
            {
                window.clear();
                pageID = 2;
            }

            if (graphics.dinoListButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && pageID == 0)
            {
                window.clear();
                pageID = 3;
            }

            if (graphics.quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && pageID == 0)
            {
                // Saving game
                std::ofstream saveGame;
                saveGame.open("savedGameFile.txt");
                saveGame << player.playerMoney << std::endl;
                for (int i = 0; i < player.dinoCount; i++)
                {
                    if (i == player.dinoCount - 1)
                        saveGame << player.playerDinos[i]->dinoID;

                    else saveGame << player.playerDinos[i]->dinoID << " ";
                }

                window.close();
            }

            if (pageID != 0)
            {
                if (graphics.backToMainMenuButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    window.clear();
                    pageID = 0;
                }
            }
        }
    }
    return 0;
}