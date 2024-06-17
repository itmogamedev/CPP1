#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <conio.h>
#include <memory>
#include <SFML/Graphics.hpp>




int Random(int n)
{
    std::random_device randVal;  // �������� ��������� �����
    std::mt19937 generator(randVal()); // ��������� ��������� ��������

    std::uniform_int_distribution<> disInt(1, n);// ����������� ������������� �� 1 �� 5 ���
    int time = disInt(generator); // ��������� ���������� �������

    return time;
}

enum Terrain { Plain, River, Mountain };

class Dino
{
    friend class DinoManager;
protected:
    int STR;							// ���� 10 - 30
    int DEX;							// �������� 10 - 30
    int INT;							// ��������� 10 - 30
    int HP = 100;
    std::string name;
    std::string loc;
    int cost;
    bool Attacking = 0;
    bool Attacked = 0;
public:
    Dino() {}
    Dino(int STR, int DEX, int INT, int cost, int HP, std::string name, std::string loc) : STR(STR), DEX(DEX), INT(INT), cost(cost), HP(HP), name(name), loc(loc) {}

    // �������������� ����. ����� ��� ������ �������� �������
    virtual int damage(Terrain terrain) = 0;
    virtual ~Dino() = default;

    virtual std::string GetName() { return name; }
    virtual int GetSTR() { return STR; }
    virtual int GetDEX() { return DEX; }
    virtual int GetINT() { return INT; }
    virtual int GetCost() { return cost; }
    virtual std::string GetLoc() { return loc; }
    virtual int GetHP() { return HP; }
    virtual bool GetAttacking() { return Attacking; }
    virtual bool GetAttacked() { return Attacked; }

    virtual void SetAttacking(bool a) { Attacking = a; }
    virtual void SetAttacked(bool a) { Attacked = a; }
    virtual void setHP(int a) { HP = a; }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class DinoStr : public Dino
{
public:
    DinoStr(int STR, int DEX, int INT, int cost, int HP, const std::string& name, const std::string& loc) : Dino(STR, DEX, INT, cost, HP, name, loc) {}
    virtual int damage(Terrain terrain) override
    {
        return terrain == Terrain::Plain ? 2 * STR : (terrain == Terrain::River ? DEX : INT);
    }
    virtual ~DinoStr() = default;

    std::string GetName() { return name; }
    int GetSTR() { return STR; }
    int GetDEX() { return DEX; }
    int GetINT() { return INT; }
    int GetCost() { return cost; }
    std::string GetLoc() { return loc; }
    int GetHP() { return HP; }
    bool GetAttacking() { return Attacking; }
    bool GetAttacked() { return Attacked; }

    void SetAttacking(bool a) { Attacking = a; }
    void SetAttacked(bool a) { Attacked = a; }

    void setHP(int hp) { HP = hp; }
};

class DinoDex : public Dino
{
public:
    DinoDex(int STR, int DEX, int INT, int cost, int HP, const std::string& name, const std::string& loc) : Dino(STR, DEX, INT, cost, HP, name, loc) {}
    virtual int damage(Terrain terrain) override
    {
        return terrain == Terrain::River ? 2 * DEX : (terrain == Terrain::Plain ? STR : INT);
    }
    virtual ~DinoDex() = default;

    std::string GetName() { return name; }
    int GetSTR() { return STR; }
    int GetDEX() { return DEX; }
    int GetINT() { return INT; }
    int GetCost() { return cost; }
    std::string GetLoc() { return loc; }
    int GetHP() { return HP; }
    bool GetAttacking() { return Attacking; }
    bool GetAttacked() { return Attacked; }

    void SetAttacking(bool a) { Attacking = a; }
    void SetAttacked(bool a) { Attacked = a; }

    void setHP(int hp) { HP = hp; }
};

class DinoInt : public Dino
{
public:
    DinoInt(int STR, int DEX, int INT, int cost, int HP, const std::string& name, const std::string& loc) : Dino(STR, DEX, INT, cost, HP, name, loc) {}
    virtual int damage(Terrain terrain) override
    {
        return terrain == Terrain::Mountain ? 2 * INT : (terrain == Terrain::Plain ? STR : DEX);
    }
    virtual ~DinoInt() = default;

    std::string GetName() { return name; }
    int GetSTR() { return STR; }
    int GetDEX() { return DEX; }
    int GetINT() { return INT; }
    int GetCost() { return cost; }
    std::string GetLoc() { return loc; }
    int GetHP() { return HP; }
    bool GetAttacking() { return Attacking; }
    bool GetAttacked() { return Attacked; }

    void SetAttacking(bool a) { Attacking = a; }
    void SetAttacked(bool a) { Attacked = a; }

    void setHP(int hp) { HP = hp; }
};


class DinoManager
{
public:
    std::vector<Dino*> collection;  // ��������� ���� ����������
    std::vector<Dino*> playerDinos;
    std::vector<Dino*> enemyDinos;


    void VectorPull(const Dino& dino, std::vector<Dino*>& vector) // push ���� � ������
    {
        Dino* copy = nullptr;
        if (dino.loc == "Plain")
        {
            copy = new DinoStr(dino.STR, dino.DEX, dino.INT, dino.cost, dino.HP, dino.name, dino.loc);
        }
        else if (dino.loc == "River")
        {
            copy = new DinoDex(dino.STR, dino.DEX, dino.INT, dino.cost, dino.HP, dino.name, dino.loc);
        }
        else if (dino.loc == "Mountain")
        {
            copy = new DinoInt(dino.STR, dino.DEX, dino.INT, dino.cost, dino.HP, dino.name, dino.loc);
        }
        vector.push_back(copy);
    }




    void ImportDB()
    {
        std::ifstream input("DinoBD.txt");
        if (input.is_open())
        {
            std::string line;
            while (std::getline(input, line))
            {
                std::string name, loc;
                int STR, DEX, INT, cost, HP;
                std::istringstream iss(line);
                iss >> STR >> DEX >> INT >> cost >> HP >> name >> loc;


                if (loc == "Plain")
                {
                    DinoStr* dino = new DinoStr(STR, DEX, INT, cost, HP, name, loc);
                    collection.push_back(dino);
                }
                else if (loc == "River")
                {
                    DinoDex* dino = new DinoDex(STR, DEX, INT, cost, HP, name, loc);
                    collection.push_back(dino);
                }
                else if (loc == "Mountain")
                {
                    DinoInt* dino = new DinoInt(STR, DEX, INT, cost, HP, name, loc);
                    collection.push_back(dino);
                }

            }
            input.close();
        }
    }

    void ClearPlayer()
    {
        std::ofstream outputPlayer("tempPlayer.txt", std::ios::trunc); /// �������� � ��������� 
        outputPlayer.close();
    }

    void ExportPlayer()
    {
        std::ofstream outputPlayer("tempPlayer.txt", std::ios::trunc); /// �������� ���������� ����� ������ � ������ � ���� ���� 

        for (auto i : playerDinos)
        {
            outputPlayer << i->STR << " " << i->DEX << " " << i->INT << " " << i->cost << " " << i->HP << " " << i->name << " " << i->loc << " " << "0" << std::endl;
        }
        outputPlayer.close();
    }

    void ExportMoney(int& money) /// ������� �����
    {
        std::ofstream outputMoney("money.txt");
        outputMoney.clear();
        int m = money;
        outputMoney << m;
        outputMoney.close();
    }

    void ImportMoney(int& money) /// ������ �����
    {
        std::ifstream outputMoney("money.txt");
        int m;
        outputMoney >> m;
        money = m;
        outputMoney.close();
    }

    void ImportPlayer(int& money)
    {

        std::ifstream outputPlayer("tempPlayer.txt");

        std::string line;
        while (std::getline(outputPlayer, line))
        {
            std::string name, loc;
            int STR, DEX, INT, cost, HP;
            std::istringstream iss(line);
            iss >> STR >> DEX >> INT >> cost >> HP >> name >> loc;


            if (loc == "Plain")
            {
                DinoStr* dino = new DinoStr(STR, DEX, INT, cost, HP, name, loc);
                playerDinos.push_back(dino);
            }
            else if (loc == "River")
            {
                DinoDex* dino = new DinoDex(STR, DEX, INT, cost, HP, name, loc);
                playerDinos.push_back(dino);
            }
            else if (loc == "Mountain")
            {
                DinoInt* dino = new DinoInt(STR, DEX, INT, cost, HP, name, loc);
                playerDinos.push_back(dino);
            }
        }
        outputPlayer.close();
    }

};





int main()
{


    sf::Font font;
    font.loadFromFile("fonts/Verdana.ttf");

    sf::Clock clock;
    float timeToSetAnotherFrame = 0;

    setlocale(LC_ALL, "ru");
    DinoManager manager;
    manager.ImportDB(); // ������ collection

    int money; /// ������
    bool isShop = 1; /// �������
    bool ableToPush = 1;

    bool isFightStart = 0; /// ���
    bool playerAttack = 0;
    bool nextAttackPlayer = 0;
    bool enemyAttack = 0;
    bool nextAttackEnemy = 0;
    bool delay = 0; /// ����� �� �������� ��� ��������
    int playerAttackIndex = 0;
    int enemyAttackIndex = 0;


    Terrain terr;

    /// ����� ������ ����������
    sf::Text terrText;
    terrText.setFont(font);
    terrText.setCharacterSize(15);
    terrText.setPosition(300, 50);

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "hdgh");

    // �������� ������� � ��������

    sf::Texture AllozavrIdleT, DeinonihIdleT, EdmontozavrIdleT, StegozavrIdleT, TirannozavrIdleT, TriceratopsIdleT; /// �������� ������� ������ ���� � ������ ����������
    sf::Texture AllozavrBiteT, DeinonihBiteT, EdmontozavrBiteT, StegozavrBiteT, TirannozavrBiteT, TriceratopsBiteT;
    sf::Texture AllozavrDeadT, DeinonihDeadT, EdmontozavrDeadT, StegozavrDeadT, TirannozavrDeadT, TriceratopsDeadT;
    sf::Texture AllozavrHurtT, DeinonihHurtT, EdmontozavrHurtT, StegozavrHurtT, TirannozavrHurtT, TriceratopsHurtT;

    AllozavrIdleT.loadFromFile("images/Allozavr/idle.png");
    AllozavrBiteT.loadFromFile("images/Allozavr/bite.png");
    AllozavrDeadT.loadFromFile("images/Allozavr/dead.png");
    AllozavrHurtT.loadFromFile("images/Allozavr/hurt.png");

    DeinonihIdleT.loadFromFile("images/Deinonih/idle.png");
    DeinonihBiteT.loadFromFile("images/Deinonih/bite.png");
    DeinonihDeadT.loadFromFile("images/Deinonih/dead.png");
    DeinonihHurtT.loadFromFile("images/Deinonih/hurt.png");

    EdmontozavrIdleT.loadFromFile("images/Edmontozavr/idle.png");
    EdmontozavrBiteT.loadFromFile("images/Edmontozavr/bite.png");
    EdmontozavrDeadT.loadFromFile("images/Edmontozavr/dead.png");
    EdmontozavrHurtT.loadFromFile("images/Edmontozavr/hurt.png");

    StegozavrIdleT.loadFromFile("images/Stegozavr/idle.png");
    StegozavrBiteT.loadFromFile("images/Stegozavr/bite.png");
    StegozavrDeadT.loadFromFile("images/Stegozavr/dead.png");
    StegozavrHurtT.loadFromFile("images/Stegozavr/hurt.png");

    TirannozavrIdleT.loadFromFile("images/Tirannozavr/idle.png");
    TirannozavrBiteT.loadFromFile("images/Tirannozavr/bite.png");
    TirannozavrDeadT.loadFromFile("images/Tirannozavr/dead.png");
    TirannozavrHurtT.loadFromFile("images/Tirannozavr/hurt.png");

    TriceratopsIdleT.loadFromFile("images/Triceratops/idle.png");
    TriceratopsBiteT.loadFromFile("images/Triceratops/bite.png");
    TriceratopsDeadT.loadFromFile("images/Triceratops/dead.png");
    TriceratopsHurtT.loadFromFile("images/Triceratops/hurt.png");

    sf::Sprite shopAllozavr(AllozavrIdleT), shopDeinonih(DeinonihIdleT), shopEdmontozavr(EdmontozavrIdleT), shopStegozavr(StegozavrIdleT), shopTirannozavr(TirannozavrIdleT), shopTriceratops(TriceratopsIdleT);

    shopAllozavr.setPosition(1000, 100); shopAllozavr.scale(sf::Vector2f(5, 5));
    shopDeinonih.setPosition(1000, 250); shopDeinonih.scale(sf::Vector2f(5, 5));
    shopEdmontozavr.setPosition(1000, 400); shopEdmontozavr.scale(sf::Vector2f(5, 5));
    shopStegozavr.setPosition(1300, 100); shopStegozavr.scale(sf::Vector2f(5, 5));
    shopTirannozavr.setPosition(1300, 250); shopTirannozavr.scale(sf::Vector2f(5, 5));
    shopTriceratops.setPosition(1300, 400); shopTriceratops.scale(sf::Vector2f(5, 5));




    // 

    manager.ImportMoney(money);
    manager.ImportPlayer(money);

    /// ������� � ��������
    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && isShop && manager.playerDinos.size() < 3)
            {
                int cost;
                sf::Vector2i mousePos = sf::Mouse::getPosition(window); // �������� ������� ������� ����
                if (shopAllozavr.getGlobalBounds().contains(mousePos.x, mousePos.y)) // ���������, ��� �� ������ �� ������-���� ����
                {
                    manager.VectorPull(*manager.collection[0], manager.playerDinos);
                    cost = manager.collection[0]->GetCost();
                    money -= cost;
                }
                else if (shopDeinonih.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    manager.VectorPull(*manager.collection[5], manager.playerDinos);
                    cost = manager.collection[5]->GetCost();
                    money -= cost;
                }
                else if (shopEdmontozavr.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    manager.VectorPull(*manager.collection[2], manager.playerDinos);
                    cost = manager.collection[2]->GetCost();
                    money -= cost;
                }
                else if (shopStegozavr.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    manager.VectorPull(*manager.collection[1], manager.playerDinos);
                    cost = manager.collection[1]->GetCost();
                    money -= cost;
                }
                else if (shopTirannozavr.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    manager.VectorPull(*manager.collection[3], manager.playerDinos);
                    cost = manager.collection[3]->GetCost();
                    money -= cost;
                }
                else if (shopTriceratops.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    manager.VectorPull(*manager.collection[4], manager.playerDinos);
                    cost = manager.collection[4]->GetCost();
                    money -= cost;
                }

            }

            if (manager.playerDinos.size() != 0 and ableToPush) /// �������� �� ������� ������� ���� ������
            {
                if (event.key.code == sf::Keyboard::Numpad1 and isShop)
                {
                    manager.playerDinos.erase(manager.playerDinos.begin()); // �������� [0] ����
                    ableToPush = 0; /// ������ ���������� �������
                }
                else if (event.key.code == sf::Keyboard::Numpad2 and isShop and manager.playerDinos.size() >= 2)
                {
                    manager.playerDinos.erase(manager.playerDinos.begin() + 1); // �������� [1] ����
                    ableToPush = 0;
                }
                else if (event.key.code == sf::Keyboard::Numpad3 and isShop and manager.playerDinos.size() >= 3)
                {
                    manager.playerDinos.erase(manager.playerDinos.begin() + 2); // �������� [2] ����
                    ableToPush = 0;
                }
            }

            if (event.key.code == sf::Keyboard::Enter and isShop and ableToPush and !manager.playerDinos.empty()) /// ���� ����� ����� �� ������ ����� (���-��, �������-���)
            {
                isShop = 0; /// ��������� �������
                isFightStart = 1; /// ��������� ���
            }

            if (event.type == sf::Event::KeyReleased) /// ��� ������� ������� ���������� ������� �������
            {
                ableToPush = 1; /// ����� �� ������
            }
        }


        window.clear();



        if (isShop) /// �������
        {
            std::string shopText;
            sf::Text sfShopText;

            /// ��������� �������� ���� � �� ������
            window.draw(shopAllozavr);
            shopText = manager.collection[0]->GetName() + "  " + manager.collection[0]->GetLoc() + "\nSTR: " + std::to_string(manager.collection[0]->GetSTR()) + "  DEX: " + std::to_string(manager.collection[0]->GetDEX()) + "  INT: " + std::to_string(manager.collection[0]->GetINT()) + "\n" + "cost: " + std::to_string(manager.collection[0]->GetCost());
            sfShopText.setString(shopText);
            sfShopText.setFont(font);
            sfShopText.setCharacterSize(10);
            sfShopText.setPosition(shopAllozavr.getPosition().x, shopAllozavr.getPosition().y + 110);
            window.draw(sfShopText);


            window.draw(shopDeinonih);
            shopText = manager.collection[5]->GetName() + "  " + manager.collection[5]->GetLoc() + "\nSTR: " + std::to_string(manager.collection[5]->GetSTR()) + "  DEX: " + std::to_string(manager.collection[5]->GetDEX()) + "  INT: " + std::to_string(manager.collection[5]->GetINT()) + "\n" + "cost: " + std::to_string(manager.collection[5]->GetCost());
            sfShopText.setString(shopText);
            sfShopText.setFont(font);
            sfShopText.setCharacterSize(10);
            sfShopText.setPosition(shopDeinonih.getPosition().x, shopDeinonih.getPosition().y + 110);
            window.draw(sfShopText);


            window.draw(shopEdmontozavr);
            shopText = manager.collection[2]->GetName() + "  " + manager.collection[2]->GetLoc() + "\nSTR: " + std::to_string(manager.collection[2]->GetSTR()) + "  DEX: " + std::to_string(manager.collection[2]->GetDEX()) + "  INT: " + std::to_string(manager.collection[2]->GetINT()) + "\n" + "cost: " + std::to_string(manager.collection[2]->GetCost());
            sfShopText.setString(shopText);
            sfShopText.setFont(font);
            sfShopText.setCharacterSize(10);
            sfShopText.setPosition(shopEdmontozavr.getPosition().x, shopEdmontozavr.getPosition().y + 110);
            window.draw(sfShopText);


            window.draw(shopStegozavr);
            shopText = manager.collection[1]->GetName() + "  " + manager.collection[1]->GetLoc() + "\nSTR: " + std::to_string(manager.collection[1]->GetSTR()) + "  DEX: " + std::to_string(manager.collection[1]->GetDEX()) + "  INT: " + std::to_string(manager.collection[1]->GetINT()) + "\n" + "cost: " + std::to_string(manager.collection[1]->GetCost());
            sfShopText.setString(shopText);
            sfShopText.setFont(font);
            sfShopText.setCharacterSize(10);
            sfShopText.setPosition(shopStegozavr.getPosition().x, shopStegozavr.getPosition().y + 110);
            window.draw(sfShopText);


            window.draw(shopTirannozavr);
            shopText = manager.collection[3]->GetName() + "  " + manager.collection[3]->GetLoc() + "\nSTR: " + std::to_string(manager.collection[3]->GetSTR()) + "  DEX: " + std::to_string(manager.collection[3]->GetDEX()) + "  INT: " + std::to_string(manager.collection[3]->GetINT()) + "\n" + "cost: " + std::to_string(manager.collection[3]->GetCost());
            sfShopText.setString(shopText);
            sfShopText.setFont(font);
            sfShopText.setCharacterSize(10);
            sfShopText.setPosition(shopTirannozavr.getPosition().x, shopDeinonih.getPosition().y + 110);
            window.draw(sfShopText);


            window.draw(shopTriceratops);
            shopText = manager.collection[4]->GetName() + "  " + manager.collection[4]->GetLoc() + "\nSTR: " + std::to_string(manager.collection[4]->GetSTR()) + "  DEX: " + std::to_string(manager.collection[4]->GetDEX()) + "  INT: " + std::to_string(manager.collection[4]->GetINT()) + "\n" + "cost: " + std::to_string(manager.collection[4]->GetCost());
            sfShopText.setString(shopText);
            sfShopText.setFont(font);
            sfShopText.setCharacterSize(10);
            sfShopText.setPosition(shopTriceratops.getPosition().x, shopTriceratops.getPosition().y + 110);
            window.draw(sfShopText);

            shopText = "You can delete Dinos with Numpad1, Numpad2 and Numpad3";
            sfShopText.setString(shopText);
            sfShopText.setFont(font);
            sfShopText.setCharacterSize(15);
            sfShopText.setPosition(1400, 1000);
            window.draw(sfShopText);
        }


        if (isFightStart)
        {


            int randTer = Random(3);
            switch (randTer)
            {
            case 1:
                terr = Plain;
                terrText.setString("Plain");
                break;
            case 2:
                terr = River;
                terrText.setString("River");
                break;
            case 3:
                terr = Mountain;
                terrText.setString("Mountain");
                break;
            }

            // ��� ����� 
            int rand3 = Random(3);
            int k = 0;
            while (k < rand3) // 1-3 �����
            {
                manager.VectorPull(*manager.collection[Random(6) - 1], manager.enemyDinos); // ��������� ���� �� collection � enemyDinos
                k++;
            }


            isFightStart = 0;
            playerAttack = 1;

        }

        if (playerAttack)
        {

            int defenderIndex = Random(manager.enemyDinos.size()) - 1; /// ������ ���������� ����
            int damage = manager.playerDinos[playerAttackIndex]->damage(terr); /// ���� ���������� ����

            int eHP = manager.enemyDinos[defenderIndex]->GetHP() - damage;
            if (eHP < 0) { eHP = 0; } /// ������ ��� �������������� �� ���

            manager.enemyDinos[defenderIndex]->setHP(eHP); /// ������������� ����� �� ����� �����


            manager.playerDinos[playerAttackIndex]->SetAttacking(1);
            manager.enemyDinos[defenderIndex]->SetAttacked(1);



            playerAttackIndex++; /// ��������� ������ �������� ���� ������
            if (playerAttackIndex == manager.playerDinos.size()) /// ���� ������ ���� ������ �������� �� �� ������ ���� �� ����� ����� � ��������� ����
            {
                nextAttackPlayer = 0;
                playerAttackIndex = 0; /// �������� ������ ������� ��� ��������� ����� ���� ������
                playerAttack = 0;
                nextAttackEnemy = 1;
            }
            else                                                 /// ���� �� �������� ��� �� �� ���� ���� ������ �� ������ ���� ��� ������� ����� �������� �����
            {
                nextAttackEnemy = 0;
                playerAttack = 0;
                nextAttackPlayer = 1;
            }
        }

        else if (enemyAttack)
        {

            int defenderIndex = Random(manager.playerDinos.size()) - 1; /// ������ ���� ������
            int damage = manager.enemyDinos[enemyAttackIndex]->damage(terr); /// ���� ���������� ����

            int eHP = manager.playerDinos[defenderIndex]->GetHP() - damage;
            if (eHP < 0)
            {
                eHP = 0;
            }

            manager.playerDinos[defenderIndex]->setHP(eHP); /// ������������� ����� �� ����� �����

            manager.enemyDinos[enemyAttackIndex]->SetAttacking(1);
            manager.playerDinos[defenderIndex]->SetAttacked(1);

            enemyAttackIndex++;
            if (enemyAttackIndex == manager.enemyDinos.size()) /// ���� ������ ���� ����� �������� �� �� ������ ���� �� ����� ������ � ��������� ����
            {
                nextAttackEnemy = 0;
                enemyAttackIndex = 0; /// �������� ������ ������ ��� ��������� ����� ���� �����
                enemyAttack = 0;
                nextAttackPlayer = 1;
            }
            else                                                 /// ���� �� �������� ��� �� �� ���� ���� ����� �� ������ ���� ��� ������� ���� �������� �����
            {
                nextAttackPlayer = 0;
                enemyAttack = 0;
                nextAttackEnemy = 1;
            }
        }



        //////////////////////////////////////////////////////////////////////////////////////////
        int x = 100, y = 100;
        sf::Text hpNametext;
        std::string str;
        for (auto d : manager.playerDinos) /// ��������� ���� ������
        {
            //
            sf::Texture bufTexture;
            if (d->GetHP() == 0) /// ���� ����
            {
                bufTexture.loadFromFile("images/" + d->GetName() + "/dead.png");
                delay = 1;
            }
            else if (d->GetAttacking()) /// ���� ������
            {
                bufTexture.loadFromFile("images/" + d->GetName() + "/bite.png");
                delay = 1;
            }
            else if (d->GetAttacked()) /// ���� ������� ����
            {
                bufTexture.loadFromFile("images/" + d->GetName() + "/hurt.png");
                delay = 1;
            }
            else
                bufTexture.loadFromFile("images/" + d->GetName() + "/idle.png");
            //


            sf::Sprite bufSprite(bufTexture);
            bufSprite.scale(sf::Vector2f(5, 5));
            bufSprite.setPosition(x, y);
            window.draw(bufSprite);
            y += 150;

            str = d->GetName() + " " + std::to_string(d->GetHP());
            hpNametext.setString(str);
            hpNametext.setFont(font);
            hpNametext.setCharacterSize(10);
            hpNametext.setPosition(bufSprite.getPosition().x, bufSprite.getPosition().y + 110);
            window.draw(hpNametext);
        }

        x = 400, y = 100;
        for (auto d : manager.enemyDinos) /// ��������� ���� �����
        {
            sf::Texture bufTexture;
            if (d->GetHP() == 0) /// ���� ����
            {
                bufTexture.loadFromFile("images/" + d->GetName() + "/dead.png");
                delay = 1;
            }
            else if (d->GetAttacking()) /// ���� ������
            {
                bufTexture.loadFromFile("images/" + d->GetName() + "/bite.png");
                delay = 1;
            }
            else if (d->GetAttacked()) /// ���� ������� ����
            {
                bufTexture.loadFromFile("images/" + d->GetName() + "/hurt.png");
                delay = 1;
            }
            else
                bufTexture.loadFromFile("images/" + d->GetName() + "/idle.png");
            //

            sf::Sprite bufSprite(bufTexture);
            bufSprite.scale(sf::Vector2f(5, 5));
            bufSprite.setPosition(x, y);
            window.draw(bufSprite);
            y += 150;

            str = d->GetName() + " " + std::to_string(d->GetHP());
            hpNametext.setString(str);
            hpNametext.setFont(font);
            hpNametext.setCharacterSize(10);
            hpNametext.setPosition(bufSprite.getPosition().x, bufSprite.getPosition().y + 110);
            window.draw(hpNametext);
        }
        ////////////////////////////////////////////////////////////

        if (delay)
        {

            window.draw(terrText);
            timeToSetAnotherFrame += time * 0.005; /// ����������� �����
            if (timeToSetAnotherFrame >= 6) /// ���� ����� ��������� �� ���������� ��� �����
            {
                timeToSetAnotherFrame = 0;
                delay = 0;
                for (auto d : manager.playerDinos)
                {
                    d->SetAttacked(0);
                    d->SetAttacking(0);
                }
                for (auto d : manager.enemyDinos)
                {
                    d->SetAttacked(0);
                    d->SetAttacking(0);
                }
                /// �������
                if (nextAttackEnemy)
                    enemyAttack = 1;

                else if (nextAttackPlayer)
                    playerAttack = 1;


                for (auto d : manager.playerDinos)
                {
                    if (d->GetHP() == 0) /// ���� ���� �����
                    {
                        auto it = std::find(manager.playerDinos.begin(), manager.playerDinos.end(), d);
                        manager.playerDinos.erase(it);
                        if (manager.playerDinos.size() == 0) /// ���� ������ ������ ������
                        {
                            money = 185;
                            manager.ClearPlayer();
                            manager.ExportMoney(money);
                            /// ������������� ������
                            manager.enemyDinos.clear();
                            isFightStart = 0;
                            playerAttack = 0;
                            nextAttackPlayer = 0;
                            enemyAttack = 0;
                            nextAttackEnemy = 0;
                            delay = 0;
                            playerAttackIndex = 0;
                            enemyAttackIndex = 0;
                            ///
                            isShop = 1; /// � ������� �������
                        }
                    }
                }

                for (auto d : manager.enemyDinos)
                {
                    if (d->GetHP() == 0) /// ���� ���� ����
                    {
                        money += (d->GetCost() * 2 / 3);
                        auto it = std::find(manager.enemyDinos.begin(), manager.enemyDinos.end(), d);
                        manager.enemyDinos.erase(it);
                        if (manager.enemyDinos.size() == 0) /// ���� ������ ��� �����
                        {
                            manager.ExportPlayer();
                            manager.ExportMoney(money);
                            /// ������������� ������
                            isFightStart = 0;
                            playerAttack = 0;
                            nextAttackPlayer = 0;
                            enemyAttack = 0;
                            nextAttackEnemy = 0;
                            delay = 0;
                            playerAttackIndex = 0;
                            enemyAttackIndex = 0;
                            ///
                            isShop = 1; /// � ������� �������
                        }
                    }
                }
            }
        }
        sf::Text moneyText;
        std::string s = std::to_string(money);
        moneyText.setString("money: " + s);
        moneyText.setCharacterSize(15);
        moneyText.setFont(font);
        moneyText.setPosition(50, 50);
        window.draw(moneyText);

        window.display();
    }
}
//