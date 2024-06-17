#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>>

class Dinosaur { // класс дино
public:
    std::string name;
    std::string terrainType;
    int strength;
    int health;
    int price;
    sf::Texture texture;
    sf::Sprite sprite;

    Dinosaur() : name(""), terrainType(""), strength(0), health(0), price(0) {}

    Dinosaur(const std::string& n, const std::string& t, int s, int h, int p)
        : name(n), terrainType(t), strength(s), health(h), price(p) {}

    bool operator==(const Dinosaur& other) const {
        return name == other.name && terrainType == other.terrainType &&
            strength == other.strength && health == other.health &&
            price == other.price;
    }

    void setTexture(const std::string& filepath) {
        if (!texture.loadFromFile(filepath)) {
            std::cerr << "Failed to load texture from " << filepath << std::endl;
        }
        else {
            sprite.setTexture(texture);
        }
    }

    void loadTextureFromType() {
        std::string base_path = "C:/Users/fedorov.daniil/Documents/dinorep/";
        if (name == "Trex") setTexture(base_path + "trex.png");
        else if (name == "Triceratops") setTexture(base_path + "tricer.png");
        else if (name == "Pterodactyl") setTexture(base_path + "ptero.png");
        else if (name == "Brachiosaurus") setTexture(base_path + "brahio.png");
        else if (name == "Archeopteryx") setTexture(base_path + "arche.png");
        else if (name == "Dimetrodon") setTexture(base_path + "dime.png");
    }

    void printInfo() const {
        std::cout << "Name: " << name << "\n"
            << "Terrain Type: " << terrainType << "\n"
            << "Strength: " << strength << "\n"
            << "Health: " << health << "\n"
            << "Price: " << price << "\n";
    }
};


class ActiveDinoSlot {
public:
    std::string name;
    Dinosaur dino;
    bool empty;

    ActiveDinoSlot() : name("Empty"), empty(true) {}

    void setDinosaur(const Dinosaur& d) {
        dino = d;
        name = d.name;
        dino.loadTextureFromType();  // Загружаем текстуру при установке динозавра
        empty = false;
    }

    void clear() {
        name = "Empty";
        empty = true;
    }

    void loadDinosaur(const std::string& dinoName, const std::vector<Dinosaur>& dinoTypes) {
        auto it = std::find_if(dinoTypes.begin(), dinoTypes.end(),
            [&dinoName](const Dinosaur& d) { return d.name == dinoName; });
        if (it != dinoTypes.end()) {
            setDinosaur(*it);
        }
    }
};

class Player {
public:
    std::vector<Dinosaur> dinosaurs;
    std::vector<ActiveDinoSlot> activeDinoSlots;
    int money;

    Player() : money(1000) {
        activeDinoSlots.resize(3); // Инициализация трех ячеек
    }

    void clear() {
        dinosaurs.clear();
        for (auto& slot : activeDinoSlots) {
            slot.clear();
        }
    }

    void addDinosaur(const Dinosaur& dino) {
        dinosaurs.push_back(dino);
    }

    void removeDeadDinos() {
        dinosaurs.erase(std::remove_if(dinosaurs.begin(), dinosaurs.end(), [](const Dinosaur& dino) {
            return dino.health <= 0;
            }), dinosaurs.end());
    }

    bool hasActiveDinos() const {
        return std::any_of(activeDinoSlots.begin(), activeDinoSlots.end(),
            [](const ActiveDinoSlot& slot) { return !slot.empty; });
    }
};



std::vector<Dinosaur> dinoTypes = {
    Dinosaur("Trex", "Mountains", 100, 200, 500),
    Dinosaur("Triceratops", "Mountains", 80, 250, 400),
    Dinosaur("Pterodactyl", "Plain", 70, 180, 300),
    Dinosaur("Brachiosaurus", "Plain", 120, 350, 700),
    Dinosaur("Archeopteryx", "River", 60, 150, 250),
    Dinosaur("Dimetrodon", "River", 90, 220, 450)
};

void addButtonLabel(sf::RenderWindow& window, sf::RectangleShape& button, sf::Text& label, const std::string& text, sf::Font& font) { // Текст на кнопку фигарим
    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(24);
    label.setFillColor(sf::Color::White);

    sf::FloatRect textRect = label.getLocalBounds();
    label.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    label.setPosition(button.getPosition().x + button.getSize().x / 2.0f, button.getPosition().y + button.getSize().y / 2.0f);
}



void exitGame(sf::RenderWindow& window);

class AfterGameMenu {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text moneyText;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture exitButtonTexture;
    sf::Sprite exitButtonSprite;
    sf::Texture winTexture;
    sf::Sprite winSprite;

    void loadBackground(const std::string& filepath) {
        if (!backgroundTexture.loadFromFile(filepath)) {
            std::cerr << "Failed to load background texture!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        );
    }

public:
    AfterGameMenu(sf::RenderWindow& win, const std::string& message) : window(win) {
        if (!font.loadFromFile("arialmt.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }

        moneyText.setFont(font);
        moneyText.setString("+300 money");
        moneyText.setCharacterSize(36);
        moneyText.setFillColor(sf::Color::Black);
        moneyText.setPosition(300, 350);

        if (!winTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/won.png")) {
            std::cerr << "Failed to load win texture!" << std::endl;
        }
        winSprite.setTexture(winTexture);
        winSprite.setPosition(200, 150);

        if (!exitButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/exitbutton.png")) {
            std::cerr << "Failed to load exit button texture!" << std::endl;
        }
        exitButtonSprite.setTexture(exitButtonTexture);
        exitButtonSprite.setPosition(300, 400);

        loadBackground("C:/Users/fedorov.daniil/Documents/dinorep/aftergamebackground.png");  // Путь к фону
    }

    void draw() {
        window.draw(backgroundSprite);
        window.draw(winSprite);
        window.draw(moneyText);
        window.draw(exitButtonSprite);
    }

    bool isExitButtonClicked(sf::Vector2f pos) {
        return exitButtonSprite.getGlobalBounds().contains(pos);
    }
};

class BattleMenu {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text titleText;
    sf::Text turnText;
    sf::Text mapText;
    sf::Text endText;
    sf::Text logText;
    sf::Texture exitButtonTexture;
    sf::Sprite exitButtonSprite;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture activeDinoIndicatorTexture;
    sf::Sprite activeDinoIndicatorSprite;
    std::vector<Dinosaur> playerDinosaurs;
    std::vector<Dinosaur> enemyDinosaurs;
    Player& player;
    std::vector<sf::RectangleShape> playerDinoShapes;
    std::vector<sf::RectangleShape> enemyDinoShapes;
    std::vector<sf::Text> playerDinoTexts;
    std::vector<sf::Text> enemyDinoTexts;
    size_t currentPlayerDinoIndex;
    size_t currentEnemyDinoIndex;
    bool playerTurn;
    bool gameEnded;

    std::string currentLog;
    std::string mapType;

    void loadMapType() {
        std::vector<std::string> maps = { "River", "Plain", "Mountains" };
        mapType = maps[rand() % maps.size()];

        if (!backgroundTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/" + mapType + ".png")) {
            std::cerr << "Failed to load map background texture for " + mapType + "!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        );
    }

    void resetBattle() {
        playerTurn = true;
        gameEnded = false;
        currentPlayerDinoIndex = 0;
        currentEnemyDinoIndex = 0;

        // Генерация случайной карты
        loadMapType();

        // Генерация случайных динозавров для врага
        std::vector<Dinosaur> allEnemyDinos = {
            Dinosaur("Trex", "Mountains", 100, 200, 500),
            Dinosaur("Triceratops", "Mountains", 80, 250, 400),
            Dinosaur("Pterodactyl", "Plain", 70, 180, 300),
            Dinosaur("Brachiosaurus", "Plain", 120, 350, 700),
            Dinosaur("Archeopteryx", "River", 60, 150, 250),
            Dinosaur("Dimetrodon", "River", 90, 220, 450)
        };

        enemyDinosaurs.clear();
        int numEnemies = 1 + rand() % 3; // Количество врагов от 1 до 3
        for (int i = 0; i < numEnemies; ++i) {
            int index = rand() % allEnemyDinos.size();
            Dinosaur enemyDino = allEnemyDinos[index];
            enemyDino.loadTextureFromType();
            enemyDinosaurs.push_back(enemyDino);
        }

        // Копируем активных динозавров игрока в пул для боя
        playerDinosaurs.clear();
        for (const auto& slot : player.activeDinoSlots) {
            if (!slot.empty) {
                playerDinosaurs.push_back(slot.dino);
            }
        }

        currentLog = "Battle starts on " + mapType + " map.";
        updateBattlefield();
    }

    void updateBattlefield() {
        // Расположение активных динозавров игрока
        for (size_t i = 0; i < playerDinosaurs.size(); ++i) {
            if (i < playerDinoShapes.size()) { // Проверка границ вектора
                Dinosaur& dino = playerDinosaurs[i];
                playerDinoShapes[i].setPosition(100, 200 + i * 75); // Расположение сверху вниз
                dino.sprite.setScale(0.5f, 0.5f);
                dino.sprite.setPosition(playerDinoShapes[i].getPosition().x, playerDinoShapes[i].getPosition().y);
                playerDinoTexts[i].setString(dino.name + " HP: " + std::to_string(dino.health));
                playerDinoTexts[i].setFillColor(sf::Color::Black);
                playerDinoTexts[i].setPosition(playerDinoShapes[i].getPosition().x + 10, playerDinoShapes[i].getPosition().y + 60);

                if (i == currentPlayerDinoIndex) {
                    activeDinoIndicatorSprite.setPosition(dino.sprite.getPosition().x - 20, dino.sprite.getPosition().y + 20);
                }
            }
        }

        // Расположение врагов
        for (size_t i = 0; i < enemyDinosaurs.size(); ++i) {
            if (i < enemyDinoShapes.size()) { // Проверка границ вектора
                enemyDinoShapes[i].setPosition(500, 200 + i * 75); // Расположение сверху вниз
                enemyDinosaurs[i].sprite.setScale(0.5f, 0.5f);
                enemyDinosaurs[i].sprite.setPosition(enemyDinoShapes[i].getPosition().x, enemyDinoShapes[i].getPosition().y);
                enemyDinoTexts[i].setString(enemyDinosaurs[i].name + " HP: " + std::to_string(enemyDinosaurs[i].health));
                enemyDinoTexts[i].setFillColor(sf::Color::Black);
                enemyDinoTexts[i].setPosition(enemyDinoShapes[i].getPosition().x + 10, enemyDinoShapes[i].getPosition().y + 60);
            }
        }

        logText.setString(currentLog);
        mapText.setString("Map: " + mapType);

        if (gameEnded) {
            if (playerDinosaurs.empty()) {
                endText.setString("You Lost! Don't give up! Press Exit to return to menu.");
            }
            else {
                endText.setString("You Won!\n+300 money\nPress Exit to return to menu.");
                player.money += 300;
            }
            turnText.setString("");
        }
        else {
            if (playerTurn) {
                turnText.setString("Player's Turn");
            }
            else {
                turnText.setString("Enemy's Turn");
            }
        }
    }

    void executeBattleStep(size_t targetIndex) {
        bool critical = false;
        if (playerTurn && !enemyDinosaurs.empty() && !playerDinosaurs.empty()) {
            Dinosaur& attacker = playerDinosaurs[currentPlayerDinoIndex];
            Dinosaur& defender = enemyDinosaurs[targetIndex];
            int damage = attacker.strength;
            if (attacker.terrainType == mapType) {
                damage *= 2;
                critical = true;
            }
            defender.health -= damage;
            if (defender.health <= 0) {
                enemyDinosaurs.erase(enemyDinosaurs.begin() + targetIndex);
            }
            currentLog = "Enemy " + attacker.name + " attacks friendly " + defender.name + "\n";
            if (critical) {
                currentLog += "and deals CRITICAL " + std::to_string(damage) + " damage";
            }
            else {
                currentLog += "and deals " + std::to_string(damage) + " damage";
            }

            if (enemyDinosaurs.empty()) {
                gameEnded = true;
            }
            else {
                currentPlayerDinoIndex = (currentPlayerDinoIndex + 1) % playerDinosaurs.size();
            }
        }
        else if (!playerTurn && !enemyDinosaurs.empty() && !playerDinosaurs.empty()) {
            Dinosaur& attacker = enemyDinosaurs[currentEnemyDinoIndex];
            Dinosaur& defender = playerDinosaurs[currentPlayerDinoIndex];
            int damage = attacker.strength;
            if (attacker.terrainType == mapType) {
                damage *= 2;
                critical = true;
            }
            defender.health -= damage;
            if (defender.health <= 0) {
                playerDinosaurs.erase(playerDinosaurs.begin() + currentPlayerDinoIndex);
            }
            currentLog = "Enemy " + attacker.name + " attacks friendly " + defender.name + "\n";
            if (critical) {
                currentLog += "and deals CRITICAL " + std::to_string(damage) + " damage";
            }
            else {
                currentLog += "and deals " + std::to_string(damage) + " damage";
            }

            if (playerDinosaurs.empty()) {
                gameEnded = true;
            }
            else {
                currentEnemyDinoIndex = (currentEnemyDinoIndex + 1) % enemyDinosaurs.size();
            }
        }

        if (!gameEnded) {
            playerTurn = !playerTurn;
        }

        updateBattlefield();
    }

public:
    BattleMenu(sf::RenderWindow& win, Player& p)
        : window(win), player(p), currentPlayerDinoIndex(0), currentEnemyDinoIndex(0) {
        if (!font.loadFromFile("arialmt.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }

        titleText.setFont(font);
        titleText.setString("Battle!");
        titleText.setCharacterSize(36);
        titleText.setFillColor(sf::Color::Black);
        titleText.setPosition(350, 50);

        turnText.setFont(font);
        turnText.setCharacterSize(24);
        turnText.setFillColor(sf::Color::Black);
        turnText.setPosition(350, 100);

        logText.setFont(font);
        logText.setCharacterSize(24);
        logText.setFillColor(sf::Color::Black);
        logText.setPosition(250, 10);

        mapText.setFont(font);
        mapText.setCharacterSize(24);
        mapText.setFillColor(sf::Color::Black);
        mapText.setPosition(10, 550);

        endText.setFont(font);
        endText.setCharacterSize(24);
        endText.setFillColor(sf::Color::Black);
        endText.setPosition(150, 500);

        if (!exitButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/exitbutton.png")) {
            std::cerr << "Failed to load exit button texture!" << std::endl;
        }
        exitButtonSprite.setTexture(exitButtonTexture);
        exitButtonSprite.setPosition(50, 550);

        if (!activeDinoIndicatorTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/dot.png")) {
            std::cerr << "Failed to load active dino indicator texture!" << std::endl;
        }
        activeDinoIndicatorSprite.setTexture(activeDinoIndicatorTexture);
        activeDinoIndicatorSprite.setScale(0.5f, 0.5f);

        for (size_t i = 0; i < 3; ++i) {
            sf::RectangleShape shape;
            shape.setSize(sf::Vector2f(100, 50));
            shape.setFillColor(sf::Color::Transparent);

            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(16);
            text.setFillColor(sf::Color::Black);

            playerDinoShapes.push_back(shape);
            playerDinoTexts.push_back(text);

            sf::RectangleShape enemyShape;
            enemyShape.setSize(sf::Vector2f(100, 50));
            enemyShape.setFillColor(sf::Color::Transparent);

            sf::Text enemyText;
            enemyText.setFont(font);
            enemyText.setCharacterSize(16);
            enemyText.setFillColor(sf::Color::Black);

            enemyDinoShapes.push_back(enemyShape);
            enemyDinoTexts.push_back(enemyText);
        }

        resetBattle();
    }

    void draw() {
        window.draw(backgroundSprite);

        window.draw(titleText);
        window.draw(turnText);
        window.draw(logText);
        window.draw(mapText);

        for (size_t i = 0; i < playerDinosaurs.size(); ++i) {
            window.draw(playerDinoShapes[i]);
            window.draw(playerDinoTexts[i]);
            window.draw(playerDinosaurs[i].sprite);
        }

        for (size_t i = 0; i < enemyDinosaurs.size(); ++i) {
            window.draw(enemyDinoShapes[i]);
            window.draw(enemyDinoTexts[i]);
            window.draw(enemyDinosaurs[i].sprite);
        }

        if (gameEnded) {
            window.draw(endText);
            window.draw(exitButtonSprite);
        }

        window.draw(activeDinoIndicatorSprite);
    }

    void handleMouseClick(sf::Vector2f pos, bool& inBattleMenu, bool& inGameMenu, bool& inAfterGameMenu, AfterGameMenu*& afterGameMenu) {
        if (gameEnded) {
            if (exitButtonSprite.getGlobalBounds().contains(pos)) {
                inBattleMenu = false;
                inAfterGameMenu = true;
            }
            return;
        }

        if (playerTurn) {
            for (size_t i = 0; i < enemyDinoShapes.size(); ++i) {
                if (enemyDinoShapes[i].getGlobalBounds().contains(pos)) {
                    executeBattleStep(i);
                    if (!gameEnded) {
                        playerTurn = false;
                        executeBattleStep(currentPlayerDinoIndex);
                        playerTurn = true;
                    }
                    break;
                }
            }
        }
    }

    bool isGameEnded() const {
        return gameEnded;
    }
};

class MainMenu { // меню при запуске
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Texture playButtonTexture;
    sf::Texture loadButtonTexture;
    sf::Texture exitButtonTexture;
    sf::Sprite backgroundSprite;
    sf::Sprite playButtonSprite;
    sf::Sprite loadButtonSprite;
    sf::Sprite exitButtonSprite;

public:
    MainMenu(sf::RenderWindow& win) : window(win) {
        if (!font.loadFromFile("arialmt.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }

        if (!backgroundTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/fon.png")) {
            std::cerr << "Failed to load background texture!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);

        if (!playButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/playbutton.png")) {
            std::cerr << "Failed to load play button texture!" << std::endl;
        }
        playButtonSprite.setTexture(playButtonTexture);
        playButtonSprite.setPosition(300, 150);

        if (!loadButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/load.png")) {
            std::cerr << "Failed to load load button texture!" << std::endl;
        }
        loadButtonSprite.setTexture(loadButtonTexture);
        loadButtonSprite.setPosition(300, 250);

        if (!exitButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/exitbutton.png")) {
            std::cerr << "Failed to load exit button texture!" << std::endl;
        }
        exitButtonSprite.setTexture(exitButtonTexture);
        exitButtonSprite.setPosition(300, 350);
    }

    void draw() {
        window.draw(backgroundSprite);
        window.draw(playButtonSprite);
        window.draw(loadButtonSprite);
        window.draw(exitButtonSprite);
    }

    bool isButtonPlayClicked(sf::Vector2f pos) {
        return playButtonSprite.getGlobalBounds().contains(pos);
    }

    bool isButtonLoadClicked(sf::Vector2f pos) {
        return loadButtonSprite.getGlobalBounds().contains(pos);
    }

    bool isButtonExitClicked(sf::Vector2f pos) {
        return exitButtonSprite.getGlobalBounds().contains(pos);
    }
};

void saveGame(const Player& player) {
    std::ofstream file("savefile.txt");

    if (!file.is_open()) {
        std::cerr << "Unable to open file for saving!" << std::endl;
        return;
    }

    file << "Money: " << player.money << std::endl;

    file << "ActiveDinoSlots:" << std::endl;
    for (const auto& slot : player.activeDinoSlots) {
        file << (slot.empty ? "Empty" : slot.dino.name) << std::endl;
    }

    file << "InventoryDinos:" << std::endl;
    for (const Dinosaur& dino : player.dinosaurs) {
        file << dino.name << " " << dino.terrainType << " " << dino.strength
            << " " << dino.health << " " << dino.price << std::endl;
    }

    file.close();
}

void loadGame(Player& player, const std::vector<Dinosaur>& dinoTypes) {
    std::ifstream file("savefile.txt");

    if (!file.is_open()) {
        std::cerr << "Unable to open file for loading!" << std::endl;
        return;
    }

    player.clear();

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("Money:") != std::string::npos) {
            player.money = std::stoi(line.substr(line.find("Money:") + 7));
        }
        else if (line.find("ActiveDinoSlots:") != std::string::npos) {
            for (auto& slot : player.activeDinoSlots) {
                if (std::getline(file, line)) {
                    if (line == "Empty") {
                        slot.clear();
                    }
                    else {
                        slot.loadDinosaur(line, dinoTypes);
                        slot.dino.loadTextureFromType();
                    }
                }
            }
        }
        else if (line.find("InventoryDinos:") != std::string::npos) {
            while (std::getline(file, line) && !line.empty()) {
                std::istringstream iss(line);
                std::string name, terrain;
                int strength, health, price;

                if (iss >> name >> terrain >> strength >> health >> price) {
                    auto it = std::find_if(dinoTypes.begin(), dinoTypes.end(),
                        [&name](const Dinosaur& d) { return d.name == name; });
                    if (it != dinoTypes.end()) {
                        Dinosaur dinoCopy = *it;
                        dinoCopy.terrainType = terrain;
                        dinoCopy.strength = strength;
                        dinoCopy.health = health;
                        dinoCopy.price = price;
                        dinoCopy.loadTextureFromType();
                        player.addDinosaur(dinoCopy);
                    }
                }
                else {
                    std::cerr << "Error reading InventoryDinos line: " << line << std::endl;
                }
            }
        }
    }

    file.close();
}

class GameMenu {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Texture battleButtonTexture;
    sf::Texture shopButtonTexture;
    sf::Texture saveButtonTexture;
    sf::Texture yourDinosButtonTexture;
    sf::Texture gameSavedTexture;
    sf::Sprite backgroundSprite;
    sf::Sprite battleButtonSprite;
    sf::Sprite shopButtonSprite;
    sf::Sprite saveButtonSprite;
    sf::Sprite yourDinosButtonSprite;
    sf::Sprite gameSavedSprite;
    sf::Clock savedTextClock;

public:
    GameMenu(sf::RenderWindow& win) : window(win) {
        if (!font.loadFromFile("arialmt.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }

        // Загрузка фонового изображения
        if (!backgroundTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/gamemenu.jpg")) {
            std::cerr << "Failed to load background texture!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);

        // Загрузка текстур кнопок
        if (!battleButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/battlebutton.png")) {
            std::cerr << "Failed to load battle button texture!" << std::endl;
        }
        battleButtonSprite.setTexture(battleButtonTexture);
        battleButtonSprite.setScale(200.f / battleButtonTexture.getSize().x, 50.f / battleButtonTexture.getSize().y);

        if (!shopButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/storebutton.png")) {
            std::cerr << "Failed to load shop button texture!" << std::endl;
        }
        shopButtonSprite.setTexture(shopButtonTexture);
        shopButtonSprite.setScale(200.f / shopButtonTexture.getSize().x, 50.f / shopButtonTexture.getSize().y);

        if (!saveButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/savebutton.png")) {
            std::cerr << "Failed to load save button texture!" << std::endl;
        }
        saveButtonSprite.setTexture(saveButtonTexture);
        saveButtonSprite.setScale(200.f / saveButtonTexture.getSize().x, 85.f / saveButtonTexture.getSize().y);

        if (!yourDinosButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/yourdinos.png")) {
            std::cerr << "Failed to load your dinos button texture!" << std::endl;
        }
        yourDinosButtonSprite.setTexture(yourDinosButtonTexture);
        yourDinosButtonSprite.setScale(200.f / yourDinosButtonTexture.getSize().x, 50.f / yourDinosButtonTexture.getSize().y);

        // Загрузка текстуры для изображения "Game was saved"
        if (!gameSavedTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/gamewas.png")) {
            std::cerr << "Failed to load game was saved texture!" << std::endl;
        }
        gameSavedSprite.setTexture(gameSavedTexture);
        gameSavedSprite.setScale(0.5f, 0.5f);
        gameSavedSprite.setPosition(window.getSize().x - gameSavedSprite.getGlobalBounds().width - 10, 10); \

            sf::Color color = gameSavedSprite.getColor();
        color.a = 0;
        gameSavedSprite.setColor(color);

        float center_x = (window.getSize().x - 200) / 2.f;
        float start_y = window.getSize().y - 320;
        float spacing_y = 70.f;


        battleButtonSprite.setPosition(center_x, start_y);
        shopButtonSprite.setPosition(center_x, start_y + spacing_y);
        saveButtonSprite.setPosition(center_x, start_y + 2 * spacing_y);
        yourDinosButtonSprite.setPosition(center_x, start_y + 3 * spacing_y);
    }

    void draw() {
        window.draw(backgroundSprite);
        window.draw(battleButtonSprite);
        window.draw(shopButtonSprite);
        window.draw(saveButtonSprite);
        window.draw(yourDinosButtonSprite);

        // Появление изображения "Game was saved" на короткое время
        if (gameSavedSprite.getColor().a > 0) {
            window.draw(gameSavedSprite);

            if (savedTextClock.getElapsedTime().asSeconds() > 3.0f) {
                sf::Color color = gameSavedSprite.getColor();
                color.a = 0;
                gameSavedSprite.setColor(color);
            }
        }
    }

    void showSavedText() {
        sf::Color color = gameSavedSprite.getColor();
        color.a = 255;
        gameSavedSprite.setColor(color);

        savedTextClock.restart();
    }

    bool isButtonBattleClicked(sf::Vector2f pos) {
        return battleButtonSprite.getGlobalBounds().contains(pos);
    }

    bool isButtonShopClicked(sf::Vector2f pos) {
        return shopButtonSprite.getGlobalBounds().contains(pos);
    }

    bool isButtonSaveClicked(sf::Vector2f pos) {
        return saveButtonSprite.getGlobalBounds().contains(pos);
    }

    bool isButtonYourDinosClicked(sf::Vector2f pos) {
        return yourDinosButtonSprite.getGlobalBounds().contains(pos);
    }

    void handleButtonClicks(sf::Vector2f pos, Player& player, bool& inGameMenu, bool& inShopMenu, bool& inDinoSelectMenu, bool& inBattleMenu, BattleMenu*& battleMenu) {
        if (isButtonBattleClicked(pos)) {
            if (player.hasActiveDinos()) {
                battleMenu = new BattleMenu(window, player);
                inGameMenu = false;
                inBattleMenu = true;
            }
            else {
                std::cerr << "You don't have any active dinos" << std::endl;
            }
        }
        else if (isButtonShopClicked(pos)) {
            inGameMenu = false;
            inShopMenu = true;
        }
        else if (isButtonSaveClicked(pos)) {
            saveGame(player);
            showSavedText();
        }
        else if (isButtonYourDinosClicked(pos)) {
            inGameMenu = false;
            inDinoSelectMenu = true;
        }
    }
};


class DinoInfo {
public:
    static Dinosaur trex;
    static Dinosaur tricer;
    static Dinosaur ptero;
    static Dinosaur brahio;
    static Dinosaur arche;
    static Dinosaur dime;

    static int trexPrice;
    static int tricerPrice;
    static int brahioPrice;
    static int pteroPrice;
    static int archePrice;
    static int dimePrice;

    static void initializeTextures() {

        trex.setTexture("C:/Users/fedorov.daniil/Documents/dinorep/trex.png");
        tricer.setTexture("C:/Users/fedorov.daniil/Documents/dinorep/tricer.png");
        ptero.setTexture("C:/Users/fedorov.daniil/Documents/dinorep/ptero.png");
        brahio.setTexture("C:/Users/fedorov.daniil/Documents/dinorep/brahio.png");
        arche.setTexture("C:/Users/fedorov.daniil/Documents/dinorep/arche.png");
        dime.setTexture("C:/Users/fedorov.daniil/Documents/dinorep/dime.png");
    }
};

// Инициализация объектов динозавров
Dinosaur DinoInfo::trex = Dinosaur("Trex", "Mountains", 100, 200, 500);
Dinosaur DinoInfo::tricer = Dinosaur("Triceratops", "Mountains", 80, 250, 400);
Dinosaur DinoInfo::ptero = Dinosaur("Pterodactyl", "Plain", 70, 180, 300);
Dinosaur DinoInfo::brahio = Dinosaur("Brachiosaurus", "Plain", 120, 350, 700);
Dinosaur DinoInfo::arche = Dinosaur("Archeopteryx", "River", 60, 150, 250);
Dinosaur DinoInfo::dime = Dinosaur("Dimetrodon", "River", 90, 220, 450);


// Инициализация цен динозавров
int DinoInfo::trexPrice = 500;
int DinoInfo::tricerPrice = 400;
int DinoInfo::brahioPrice = 700;
int DinoInfo::pteroPrice = 300;
int DinoInfo::archePrice = 250;
int DinoInfo::dimePrice = 450;




class ShopMenu {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture backgroundTexture; // Фон
    sf::Texture titleTexture; // Изображение фона шопа
    sf::Texture dinoInfoBackgroundTexture; // Новый фон для информации о динозавре
    sf::Sprite backgroundSprite;
    sf::Sprite titleSprite;
    sf::Sprite dinoInfoBackgroundSprite; // Спрайт для фона информации о динозавре
    sf::Text dinoInfoText;
    sf::Text moneyText;
    sf::Text errorMessage;
    sf::Texture backButtonTexture;
    sf::Texture nextButtonTexture;
    sf::Texture buyButtonTexture;
    sf::Texture exitButtonTexture;
    sf::Sprite backButtonSprite;
    sf::Sprite nextButtonSprite;
    sf::Sprite buyButtonSprite;
    sf::Sprite exitButtonSprite;

    std::vector<Dinosaur> dinosaurs;
    size_t currentIndex;
    Player& player;

public:
    ShopMenu(sf::RenderWindow& win, Player& p)
        : window(win), player(p), currentIndex(0) {
        if (!font.loadFromFile("arialmt.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }

        // Загрузка фона
        if (!backgroundTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/shopfon.png")) {
            std::cerr << "Failed to load background texture!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);

        // Загрузка нового фона для информации о динозавре
        if (!dinoInfoBackgroundTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/shoprep.png")) {
            std::cerr << "Failed to load dino info background texture!" << std::endl;
        }
        dinoInfoBackgroundSprite.setTexture(dinoInfoBackgroundTexture);
        dinoInfoBackgroundSprite.setPosition(-30, 76);

        dinosaurs.push_back(DinoInfo::trex);
        dinosaurs.push_back(DinoInfo::tricer);
        dinosaurs.push_back(DinoInfo::ptero);
        dinosaurs.push_back(DinoInfo::brahio);
        dinosaurs.push_back(DinoInfo::arche);
        dinosaurs.push_back(DinoInfo::dime);

        // Настройка текста информации о динозавре
        dinoInfoText.setFont(font);
        dinoInfoText.setCharacterSize(24);
        dinoInfoText.setFillColor(sf::Color::Black);
        dinoInfoText.setStyle(sf::Text::Bold);
        dinoInfoText.setPosition(35, 130);

        // Настройка текста количества денег
        moneyText.setFont(font);
        moneyText.setCharacterSize(30);
        moneyText.setFillColor(sf::Color::Black);
        moneyText.setStyle(sf::Text::Bold);
        moneyText.setPosition(20, 20);

        errorMessage.setFont(font);
        errorMessage.setCharacterSize(18);
        errorMessage.setFillColor(sf::Color::Red);
        errorMessage.setPosition(50, 500);
        errorMessage.setString("");

        if (!backButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/backbutton.png")) {
            std::cerr << "Failed to load back button texture!" << std::endl;
        }
        backButtonSprite.setTexture(backButtonTexture);
        backButtonSprite.setPosition(100, 500);

        if (!nextButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/nextbutton.png")) {
            std::cerr << "Failed to load next button texture!" << std::endl;
        }
        nextButtonSprite.setTexture(nextButtonTexture);
        nextButtonSprite.setPosition(400, 500);

        if (!buyButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/buybutton.png")) {
            std::cerr << "Failed to load buy button texture!" << std::endl;
        }
        buyButtonSprite.setTexture(buyButtonTexture);
        buyButtonSprite.setPosition(250, 500);
        buyButtonSprite.setScale(1.f, 1.f);

        if (!exitButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/exitbutton.png")) {
            std::cerr << "Failed to load exit button texture!" << std::endl;
        }
        exitButtonSprite.setTexture(exitButtonTexture);
        exitButtonSprite.setPosition(window.getSize().x - exitButtonSprite.getGlobalBounds().width - 20, 20); // Положение в правом верхнем углу

        updateDinoInfoText();
        updateMoneyText();
    }

    void draw() {
        window.draw(backgroundSprite);
        window.draw(titleSprite); // Рисуем заголовок "Shop"
        window.draw(dinoInfoBackgroundSprite); // Рисуем фон под текст информации о динозавре
        window.draw(backButtonSprite);
        window.draw(nextButtonSprite);
        window.draw(buyButtonSprite);
        window.draw(exitButtonSprite);
        window.draw(dinoInfoText);
        window.draw(moneyText);
        window.draw(errorMessage);

        // Отрисовываем текущего динозавра в центре
        Dinosaur currentDino = dinosaurs[currentIndex];
        currentDino.sprite.setScale(2.f, 2.f); // Увеличение изображения динозавра
        currentDino.sprite.setPosition((window.getSize().x - currentDino.sprite.getGlobalBounds().width) / 2, 200); // Положение спрайта динозавра
        window.draw(currentDino.sprite);
    }

    bool isBackButtonClicked(sf::Vector2f pos) {
        return backButtonSprite.getGlobalBounds().contains(pos);
    }

    bool isNextButtonClicked(sf::Vector2f pos) {
        return nextButtonSprite.getGlobalBounds().contains(pos);
    }

    bool isBuyButtonClicked(sf::Vector2f pos) {
        return buyButtonSprite.getGlobalBounds().contains(pos);
    }

    bool isExitButtonClicked(sf::Vector2f pos) {
        return exitButtonSprite.getGlobalBounds().contains(pos);
    }

    void updateDinoInfoText() {
        Dinosaur currentDino = dinosaurs[currentIndex];
        std::string infoText = "Name: " + currentDino.name + "\n";
        infoText += "Terrain: " + currentDino.terrainType + "\n";
        infoText += "Strength: " + std::to_string(currentDino.strength) + "\n";
        infoText += "Health: " + std::to_string(currentDino.health) + "\n";
        infoText += "Price: " + std::to_string(currentDino.price) + "\n";

        dinoInfoText.setString(infoText);
    }

    void updateMoneyText() {
        moneyText.setString("Money: " + std::to_string(player.money));
    }

    void showErrorMessage(const std::string& message) {
        errorMessage.setString(message);
    }

    void handleButtonClicks(sf::Vector2f pos) {
        if (isBackButtonClicked(pos)) {
            currentIndex = (currentIndex == 0) ? dinosaurs.size() - 1 : currentIndex - 1;
            updateDinoInfoText();
        }
        else if (isNextButtonClicked(pos)) {
            currentIndex = (currentIndex + 1) % dinosaurs.size();
            updateDinoInfoText();
        }
        else if (isBuyButtonClicked(pos)) {
            if (player.money >= dinosaurs[currentIndex].price) {
                player.money -= dinosaurs[currentIndex].price;
                player.addDinosaur(dinosaurs[currentIndex]);
                updateMoneyText(); // Обновляем отображение денег после покупки
            }
            else {
                showErrorMessage("Not enough money to buy this dinosaur!");
            }
        }
        else if (isExitButtonClicked(pos)) {
            return;
        }
    }
};


class DinoSelectMenu {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Texture exitButtonTexture;
    sf::Texture nextButtonTexture;
    sf::Texture backButtonTexture;
    sf::Texture chooseButtonTexture;
    sf::Sprite backgroundSprite;
    sf::Sprite exitButtonSprite;
    sf::Sprite nextButtonSprite;
    sf::Sprite backButtonSprite;
    sf::Sprite chooseButtonSprite;
    sf::Text selectedDinosText;
    sf::Text inventoryWarningText;
    Player& player;
    std::vector<sf::RectangleShape> activeDinoSlots;
    size_t currentIndex;

    void updateSelectedDinosText() {
        std::string infoText = "Active Dinosaurs:";
        for (const auto& slot : player.activeDinoSlots) {
            infoText += "\n" + slot.name;
        }
        selectedDinosText.setString(infoText);
    }

    void updateActiveDinoSlots() {
        for (size_t i = 0; i < activeDinoSlots.size(); ++i) {
            if (!player.activeDinoSlots[i].empty) {
                sf::RectangleShape& slotShape = activeDinoSlots[i];
                Dinosaur& dino = player.activeDinoSlots[i].dino;
                dino.sprite.setPosition(
                    slotShape.getPosition().x + (slotShape.getSize().x - dino.sprite.getGlobalBounds().width) / 2,
                    slotShape.getPosition().y + (slotShape.getSize().y - dino.sprite.getGlobalBounds().height) / 2
                );
            }
        }
    }

    void updateViewport() {
        if (currentIndex >= player.dinosaurs.size()) {
            currentIndex = 0;
        }
        if (!player.dinosaurs.empty()) {
            Dinosaur& currentDino = player.dinosaurs[currentIndex];
            currentDino.sprite.setPosition(550, 200);
            currentDino.sprite.setScale(2.f, 2.f);
        }
    }

public:
    DinoSelectMenu(sf::RenderWindow& win, Player& p)
        : window(win), player(p), currentIndex(0) {
        if (!font.loadFromFile("arialmt.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }

        // Загрузка фонового изображения
        if (!backgroundTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/yourdinosfon.png")) {
            std::cerr << "Failed to load background texture!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);

        // Загрузка кнопок
        if (!exitButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/exitbutton.png")) {
            std::cerr << "Failed to load exit button texture!" << std::endl;
        }
        exitButtonSprite.setTexture(exitButtonTexture);
        exitButtonSprite.setPosition(520, 10);

        if (!nextButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/nextbutton.png")) {
            std::cerr << "Failed to load next button texture!" << std::endl;
        }
        nextButtonSprite.setTexture(nextButtonTexture);
        nextButtonSprite.setPosition(600, 500);

        if (!backButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/backbutton.png")) {
            std::cerr << "Failed to load back button texture!" << std::endl;
        }
        backButtonSprite.setTexture(backButtonTexture);
        backButtonSprite.setPosition(420, 500);

        if (!chooseButtonTexture.loadFromFile("C:/Users/fedorov.daniil/Documents/dinorep/choosebutton.png")) {
            std::cerr << "Failed to load choose button texture!" << std::endl;
        }
        chooseButtonSprite.setTexture(chooseButtonTexture);
        chooseButtonSprite.setPosition(270, 500);

        selectedDinosText.setFont(font);
        selectedDinosText.setCharacterSize(24);
        selectedDinosText.setFillColor(sf::Color::Black);
        selectedDinosText.setPosition(50, 50);

        inventoryWarningText.setFont(font);
        inventoryWarningText.setCharacterSize(24);
        inventoryWarningText.setFillColor(sf::Color::Black);
        inventoryWarningText.setPosition(520, 70);


        for (size_t i = 0; i < 3; ++i) {
            sf::RectangleShape slot;
            slot.setSize(sf::Vector2f(150, 150));
            slot.setFillColor(sf::Color(50, 205, 50));
            slot.setPosition(50, 150 + i * 170);
            activeDinoSlots.push_back(slot);
        }

        updateActiveDinoSlots();
        updateSelectedDinosText();
        updateViewport();
    }

    void draw() {
        window.draw(backgroundSprite);
        window.draw(exitButtonSprite);
        window.draw(nextButtonSprite);
        window.draw(backButtonSprite);
        window.draw(chooseButtonSprite);
        window.draw(selectedDinosText);
        window.draw(inventoryWarningText);

        for (size_t i = 0; i < activeDinoSlots.size(); ++i) {
            window.draw(activeDinoSlots[i]);
            if (!player.activeDinoSlots[i].empty) {
                window.draw(player.activeDinoSlots[i].dino.sprite);
            }
        }

        if (!player.dinosaurs.empty()) {
            window.draw(player.dinosaurs[currentIndex].sprite);
        }
    }

    bool isExitButtonClicked(sf::Vector2f pos) {
        return exitButtonSprite.getGlobalBounds().contains(pos);
    }

    bool isNextButtonClicked(sf::Vector2f pos) {
        return nextButtonSprite.getGlobalBounds().contains(pos);
    }

    bool isBackButtonClicked(sf::Vector2f pos) {
        return backButtonSprite.getGlobalBounds().contains(pos);
    }

    bool isChooseButtonClicked(sf::Vector2f pos) {
        return chooseButtonSprite.getGlobalBounds().contains(pos);
    }

    bool isSlotClicked(sf::Vector2f pos, size_t& index) {
        for (size_t i = 0; i < activeDinoSlots.size(); ++i) {
            if (activeDinoSlots[i].getGlobalBounds().contains(pos)) {
                index = i;
                return true;
            }
        }
        return false;
    }

    void handleButtonClicks(sf::Vector2f pos) {
        if (isExitButtonClicked(pos)) {
            return;
        }

        if (player.dinosaurs.empty()) {
            inventoryWarningText.setString("You don't have any dinos in inventory.");
            return;
        }
        else {
            inventoryWarningText.setString("");
        }

        size_t index;
        if (isSlotClicked(pos, index)) {
            if (!player.activeDinoSlots[index].empty) {
                std::swap(player.activeDinoSlots[index].dino, player.dinosaurs[currentIndex]);
                player.activeDinoSlots[index].setDinosaur(player.dinosaurs[currentIndex]);
                std::rotate(player.dinosaurs.begin(), player.dinosaurs.begin() + 1, player.dinosaurs.end());
            }
            else {
                player.activeDinoSlots[index].setDinosaur(player.dinosaurs[currentIndex]);
                player.dinosaurs.erase(player.dinosaurs.begin() + currentIndex);
            }
            updateActiveDinoSlots();
            updateSelectedDinosText();
            updateViewport();
        }
        else if (isNextButtonClicked(pos)) {
            currentIndex = (currentIndex + 1) % player.dinosaurs.size();
            updateViewport();
        }
        else if (isBackButtonClicked(pos)) {
            if (currentIndex == 0) {
                currentIndex = player.dinosaurs.size() - 1;
            }
            else {
                --currentIndex;
            }
            updateViewport();
        }
        else if (isChooseButtonClicked(pos)) {
            for (size_t i = 0; i < player.activeDinoSlots.size(); ++i) {
                if (player.activeDinoSlots[i].empty) {
                    player.activeDinoSlots[i].setDinosaur(player.dinosaurs[currentIndex]);
                    player.dinosaurs.erase(player.dinosaurs.begin() + currentIndex);
                    updateActiveDinoSlots();
                    updateSelectedDinosText();
                    updateViewport();
                    break;
                }
            }
        }
    }
};



void exitGame(sf::RenderWindow& window) {
    window.close();
}


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dino Game");

    Player player;

    // Инициализация текстур для динозавров
    DinoInfo::initializeTextures();

    // Список доступных типов динозавров
    std::vector<Dinosaur> dinoTypes = {
    Dinosaur("Trex", "Mountains", 100, 200, 500),
    Dinosaur("Triceratops", "Mountains", 80, 250, 400),
    Dinosaur("Pterodactyl", "Plain", 70, 180, 300),
    Dinosaur("Brachiosaurus", "Plain", 120, 350, 700),
    Dinosaur("Archeopteryx", "River", 60, 150, 250),
    Dinosaur("Dimetrodon", "River", 90, 220, 450)
    };

    MainMenu mainMenu(window);
    GameMenu gameMenu(window);
    ShopMenu shopMenu(window, player);
    DinoSelectMenu dinoSelectMenu(window, player);
    BattleMenu* battleMenu = nullptr;
    AfterGameMenu* afterGameMenu = nullptr;

    bool inMainMenu = true;
    bool inGameMenu = false;
    bool inShopMenu = false;
    bool inDinoSelectMenu = false;
    bool inBattleMenu = false;
    bool inAfterGameMenu = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (inMainMenu) {
                    if (mainMenu.isButtonPlayClicked(mousePos)) {
                        inMainMenu = false;
                        inGameMenu = true;
                    }
                    else if (mainMenu.isButtonLoadClicked(mousePos)) {
                        loadGame(player, dinoTypes);
                        inMainMenu = false;
                        inGameMenu = true;
                    }
                    else if (mainMenu.isButtonExitClicked(mousePos)) {
                        window.close();
                    }
                }
                else if (inGameMenu) {
                    gameMenu.handleButtonClicks(mousePos, player, inGameMenu, inShopMenu, inDinoSelectMenu, inBattleMenu, battleMenu);
                }
                else if (inShopMenu) {
                    if (shopMenu.isExitButtonClicked(mousePos)) {
                        inShopMenu = false;
                        inGameMenu = true;
                    }
                    else {
                        shopMenu.handleButtonClicks(mousePos);
                        shopMenu.updateMoneyText();
                    }
                }
                else if (inDinoSelectMenu) {
                    if (dinoSelectMenu.isExitButtonClicked(mousePos)) {
                        inDinoSelectMenu = false;
                        inGameMenu = true;
                    }
                    else {
                        dinoSelectMenu.handleButtonClicks(mousePos);
                    }
                }
                else if (inBattleMenu) {
                    battleMenu->handleMouseClick(mousePos, inBattleMenu, inGameMenu, inAfterGameMenu, afterGameMenu);
                    if (battleMenu->isGameEnded()) {
                        inBattleMenu = false;
                        inAfterGameMenu = true;
                        std::string message = player.hasActiveDinos() ? "Nice! You won and earned yourself 300 money!" : "You lost, but don't give up! Try one more time";
                        afterGameMenu = new AfterGameMenu(window, message);
                    }
                }
                else if (inAfterGameMenu) {
                    if (afterGameMenu->isExitButtonClicked(mousePos)) {
                        inAfterGameMenu = false;
                        inGameMenu = true;
                        delete afterGameMenu;
                        afterGameMenu = nullptr;
                    }
                }
            }
        }

        window.clear();

        if (inMainMenu) {
            mainMenu.draw();
        }
        else if (inGameMenu) {
            gameMenu.draw();
        }
        else if (inShopMenu) {
            shopMenu.draw();
        }
        else if (inDinoSelectMenu) {
            dinoSelectMenu.draw();
        }
        else if (inBattleMenu && battleMenu != nullptr) {
            battleMenu->draw();
        }
        else if (inAfterGameMenu && afterGameMenu != nullptr) {
            afterGameMenu->draw();
        }

        window.display();
    }

    delete battleMenu;
    delete afterGameMenu;

    return 0;
}
