#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <windows.h>
#include <fstream>
#include <algorithm>
#include "Button.h"



enum Terrain { Plain, River, Mountain };
enum FightCharacteristic { STRENGTH, DEXTERITY, INTELLIGENCE };
enum DinoType { TRex, Brachio, Tryc };
enum GameOption
{ MainMenu, Shop_Start, Shop_Plain, Shop_River, Shop_Mountain, Fight, FightLobby, LowBalance, Win, Lose };



GameOption Current = MainMenu;
int Reward = 0;

class Dino {
protected:
    int STRENGTH;
    int DEXTERITY;
    int INTELLIGENCE;
    int Damage;
    
    int HP = 100;
    std::string name;
    int cost;
    sf::Sprite DinoSprite;
    int TerrainType;

    Terrain FavTerrain;
    DinoType Type;

    
    bool Chosen = false;
    sf::Texture DinoTexture;

public:
    
    Dino() {
        std::random_device random;
        STRENGTH = random() % 21 + 10;
        DEXTERITY = random() % 21 + 10;
        INTELLIGENCE = random() % 21 + 10;
        cost = STRENGTH + DEXTERITY + INTELLIGENCE;
        Type = DinoType(random() % 3);
        if (Type == TRex) {
            DinoTexture.loadFromFile("rex_l.png");
            DinoSprite.setTexture(DinoTexture);
            name = "TRex";
        };
        if (Type == Brachio) {
            DinoTexture.loadFromFile("brachio_l.png");
            DinoSprite.setTexture(DinoTexture);
            name = "Brachio";
        }
        if (Type == Tryc) {
            DinoTexture.loadFromFile("tryc_l.png");
            DinoTexture.loadFromFile("tryc_l.png");
            DinoSprite.setTexture(DinoTexture);
            name = "Tric";
        }
        HP = 100;
        Terrain FavTerrain = Terrain(random() % 3);
       
    };

    Dino(int Str, int Dex, int Int, int Cost, int type, int ft) {
        STRENGTH = Str;
        DEXTERITY = Dex;
        INTELLIGENCE = Int;
        cost = Cost;
        if (type == 0) { Type = TRex; name = "TRex"; DinoTexture.loadFromFile("rex_l.png"); DinoSprite.setTexture(DinoTexture); }
        else if (type == 1) { Type = Brachio; name = "Brachio"; DinoTexture.loadFromFile("brachio_l.png"); DinoSprite.setTexture(DinoTexture); }
        else if (type == 2) { Type = Tryc; name = "Tric"; DinoTexture.loadFromFile("tryc_l.png"); DinoSprite.setTexture(DinoTexture); }

        if (ft == 0) { FavTerrain = Plain; Damage = STRENGTH; }
        else if (ft == 1) { FavTerrain = River; Damage = DEXTERITY; }
        else if (ft == 2) { FavTerrain = Mountain; Damage = INTELLIGENCE; }

    }

   void setDamage(Terrain t) {
       if (t == FavTerrain) { Damage *= 2; }

    }

    int getStr() { return STRENGTH; }
    int getDex() { return DEXTERITY; }
    int getInt() { return INTELLIGENCE; }
    int getCost() { return cost; }
    int getHP() { return HP; }
    int getDMG() { return Damage; }
    bool isChosen(){ return Chosen; }
    std::string getName() { return name; }
    Terrain getFT() { return FavTerrain; }
    DinoType getType() { return Type; }
    sf::Sprite getSprite() { return DinoSprite; }

    std::string getInfo() {
        return (name + " HP:" + std::to_string(HP) + " STR:" + std::to_string(STRENGTH) + " DEX:" + std::to_string(DEXTERITY) + " INT:" + std::to_string(INTELLIGENCE) + "| Cost:" + std::to_string(cost));
    }

    std::string getStats() {

            return (name + " HP:" + std::to_string(HP) + " STR:" + std::to_string(STRENGTH) + " DEX:" + std::to_string(DEXTERITY) + " INT:" + std::to_string(INTELLIGENCE));
        
    }

    void setChosen(bool b) { Chosen = b; }
    void setStr(int n) { STRENGTH = n; }
    void setDex(int n) { DEXTERITY = n; }
    void setInt(int n) { INTELLIGENCE = n; }
    void setCost(int n) { cost = n; }
    void setHP(int n) { HP = n; }
    void setName(std::string n) { name = n; }
    void setFT(Terrain n) { FavTerrain = n; }
    void setDinoSprite() {
        if (Type == TRex) {
            DinoTexture.loadFromFile("rex_l.png");
            DinoSprite.setTexture(DinoTexture);
        }
        if (Type == Brachio) {
            DinoTexture.loadFromFile("brachio_l.png");
            DinoSprite.setTexture(DinoTexture);
        }
        if (Type == Tryc) {
            DinoTexture.loadFromFile("tryc_l.png");
            DinoSprite.setTexture(DinoTexture);
        }

    }
    void setEnemySprite() {
        if (Type == TRex) {
            DinoTexture.loadFromFile("rex_r.png");
            DinoSprite.setTexture(DinoTexture);
        }
        if (Type == Brachio) {
            DinoTexture.loadFromFile("brachio_r.png");
            DinoSprite.setTexture(DinoTexture);
        }
        if (Type == Tryc) {
            DinoTexture.loadFromFile("tryc_r.png");
            DinoSprite.setTexture(DinoTexture);
        }
    }
    void setType(DinoType n) {
        Type = n;
        if (Type == TRex) {
            DinoTexture.loadFromFile("rex_l.png");
            DinoSprite.setTexture(DinoTexture);
            
        };
        if (Type == Brachio) {
            DinoTexture.loadFromFile("brachio_l.png");
            DinoSprite.setTexture(DinoTexture);
        }
        if (Type == Tryc) {
            DinoTexture.loadFromFile("tryc_l.png");
            DinoSprite.setTexture(DinoTexture);
        }
    }
    void setSpritePos(sf::RenderWindow& window, float x, float y) {
        DinoSprite.setPosition(x, y);
    }

    void PrintInfo(sf::RenderWindow& window, float x, float y) {
        sf::Text text;
        sf::Font font;
        font.loadFromFile("arial.ttf");
        text.setFont(font);
        text.setFillColor(sf::Color::White);
        text.setString(getInfo());
        text.setCharacterSize(15);
        text.setPosition(x, y);
        window.draw(text);

    }

    void PrintStats(sf::RenderWindow& window, float x, float y) {
        sf::Text text;
        sf::Font font;
        font.loadFromFile("arial.ttf");
        text.setFont(font);
        text.setFillColor(sf::Color::White);
        text.setString(getStats());
        text.setCharacterSize(15);
        text.setPosition(x, y);
        window.draw(text);
    }

    void DrawDino(sf::RenderWindow& window) {
        window.draw(DinoSprite);
    }

    void GetHitPlayer() {
        if (Type == TRex) {
            DinoTexture.loadFromFile("rex_ld.png");
            DinoSprite.setTexture(DinoTexture);
        }
        else if (Type == Brachio) {
            DinoTexture.loadFromFile("brachio_ld.png");
            DinoSprite.setTexture(DinoTexture);
        }
        if (Type == Tryc) {
            DinoTexture.loadFromFile("tryc_ld.png");
            DinoSprite.setTexture(DinoTexture);
        }
    }

    void GetHitEnemy() {
        if (Type == TRex) {
            DinoTexture.loadFromFile("rex_rd.png");
            DinoSprite.setTexture(DinoTexture);
        }
        else if (Type == Brachio) {
            DinoTexture.loadFromFile("brachio_rd.png");
            DinoSprite.setTexture(DinoTexture);
        }
        if (Type == Tryc) {
            DinoTexture.loadFromFile("tryc_rd.png");
            DinoSprite.setTexture(DinoTexture);
        }
    }

    void Die() {
        DinoTexture.loadFromFile("dead.png");
        DinoSprite.setTexture(DinoTexture);
    }

};

std::vector <Dino*> DinoPool;
Dino* fighter = nullptr;

void LoadDinos() {
    std::string s;
    std::vector <int> DinoStats;
    std::ifstream fin;
    fin.open("Saved_dinos.txt");

    while (getline(fin, s)) {
        DinoStats.push_back(std::stoi(s));
        if (DinoStats.size() == 6) {
            Dino* temp = new Dino(DinoStats[0], DinoStats[1], DinoStats[2], DinoStats[3], DinoStats[4], DinoStats[5]);
            DinoPool.push_back(temp);
            DinoStats.clear();
        }


    }
    fin.close();
}



template <typename T> void SaveDino(T dino) {
    std::ofstream out;
    out.open("Saved_dinos.txt", std::ios::app);
    if (out.is_open()) {
        out << dino.getStr() << std::endl;
        out << dino.getDex() << std::endl;
        out << dino.getInt() << std::endl;
        out << dino.getCost() << std::endl;
        out << dino.getType() << std::endl;
        out << dino.getFT() << std::endl;
        out.close();
    }


}



Dino GenerateDino(std::vector<int> v) {

    Dino dino;
    dino.setStr(v[0]);
    dino.setDex(v[1]);
    dino.setInt(v[2]);
    dino.setCost(v[3]);
    if (v[4] == 0) {
        dino.setType(TRex);
        dino.setName("TRex");
        
    }
    else if (v[4] == 1) {
        dino.setType(Brachio);
        dino.setName("Brachio");
    }
    else if (v[4] == 2) {
        dino.setType(Tryc);
        dino.setName("Tric");
    }
    if (v[5] == 0) { dino.setFT(Plain); }
    else if (v[5] == 1) { dino.setFT(River); }
    else if (v[5] == 2) { dino.setFT(Mountain); }
    return dino;

}

int Balance = 0;

void GetBalance() {
    std::ifstream in;
    in.open("Balance.txt");
    in >> Balance;
    in.close();
}
void SaveBalance() {
    std::ofstream fout;
    fout.open("Balance.txt");
    if (fout.is_open()) {
        fout << Balance;
        fout.close();
    }
}
void PrintBalance(sf::RenderWindow& window, float x, float y) {
    sf::Text text;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setString("Your balance:" + std::to_string(Balance));
    text.setCharacterSize(15);
    text.setPosition(x, y);
    window.draw(text);

}

void Menu(sf::RenderWindow& window, GameOption& go) {
    sf::Texture shop;
    shop.loadFromFile("shop.png");
    Button menu_shop;
    menu_shop.B_Sprite.setTexture(shop);
    menu_shop.B_Sprite.setPosition(100, 300);

    sf::Texture welcome;
    welcome.loadFromFile("welcome.png");
    Button logo;
    logo.B_Sprite.setTexture(welcome);
    logo.B_Sprite.setPosition(100, 100);

    sf::Texture fight;
    fight.loadFromFile("fight.png");
    Button fht;
    fht.B_Sprite.setTexture(fight);
    fht.B_Sprite.setPosition(100, 500);

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (menu_shop.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))) { go = Shop_Start; return; }
            if (fht.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))) { go = FightLobby; return; }

        }
        window.clear();
        window.draw(menu_shop.B_Sprite);
        window.draw(fht.B_Sprite);
        window.draw(logo.B_Sprite);
        window.display();
    }

}

void Lobby(sf::RenderWindow& window, GameOption& go) {

    LoadDinos();

    sf::Texture choose;
    choose.loadFromFile("choose.png");
    Button chs;
    chs.B_Sprite.setTexture(choose);
    chs.B_Sprite.setPosition(100, 100);

    sf::Texture next;
    next.loadFromFile("next.png");
    Button gonext;
    gonext.B_Sprite.setTexture(next);
    gonext.B_Sprite.setPosition(500, 400);

    sf::Texture take;
    take.loadFromFile("take.png");
    Button takethis;
    takethis.B_Sprite.setTexture(take);
    takethis.B_Sprite.setPosition(500, 600);


    int ptr = 0;
    int n = DinoPool.size();
    Dino* current_dino = nullptr;

    sf::Event event;
    while (window.isOpen())
    {
        current_dino = DinoPool[ptr];
        current_dino->setSpritePos(window, 100, 300);


        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (takethis.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) { fighter = current_dino; go = Fight; return; }

            if ((gonext.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
                if (ptr < n - 1) {
                    ptr++;
                }
                else { ptr = 0; }
            }
            window.clear();
            window.draw(chs.B_Sprite);
                window.draw(gonext.B_Sprite);
                window.draw(takethis.B_Sprite);
                current_dino->DrawDino(window);
                current_dino->PrintStats(window, 100, 600);
                window.display();
        }



    }
}

void Fighting(sf::RenderWindow& window, GameOption& go) {

    GetBalance();

    std::random_device random;
    int FightT = (random() % 3);
    Terrain t = Plain;
    sf::Texture loc;
    sf::Sprite location;
    location.setPosition(350, 600);

    if (FightT == 0) { loc.loadFromFile("plain.png"); location.setTexture(loc); t = Plain; }
    else if (FightT == 1) { loc.loadFromFile("river.png"); location.setTexture(loc); t = River; }
    else if (FightT == 2) { loc.loadFromFile("mt.png"); location.setTexture(loc); t = Mountain; }


    
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text yd;
    yd.setFont(font);
    yd.setFillColor(sf::Color::White);
    yd.setString("Your mighty champion");
    yd.setCharacterSize(15);
    yd.setPosition(50, 650);


    sf::Text ed;
    ed.setFont(font);
    ed.setFillColor(sf::Color::White);
    ed.setString("Their stinky lizard");
    ed.setCharacterSize(15);
    ed.setPosition(600, 650);


    sf::Texture fight;
    fight.loadFromFile("fight.png");
    Button fht;
    fht.B_Sprite.setTexture(fight);
    fht.B_Sprite.setPosition(100, 100);

    sf::Texture attack;
    attack.loadFromFile("attack.png");
    Button atk;
    atk.B_Sprite.setTexture(attack);
    atk.B_Sprite.setPosition(350, 500);

    fighter->setSpritePos(window, 50, 300);
    fighter->setDamage(t);

    Dino enemy;
    enemy.setDamage(t);
    enemy.setEnemySprite();
    enemy.setSpritePos(window, 450, 300);


    Reward = enemy.getCost();
    int P_HP = fighter->getHP();
    int P_DMG = fighter->getDMG();
    int E_HP = enemy.getHP();
    int E_DMG = enemy.getDMG();

    sf::Time delay = sf::seconds(1);
    sf::Texture exit;
    exit.loadFromFile("exit.png");
   

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (atk.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left) and E_HP > 0 and P_HP > 0) {
                E_HP -= P_DMG;
                if (E_HP < 100) { enemy.GetHitEnemy(); }
                P_HP -= E_DMG;
                if (P_HP < 100) { fighter->GetHitPlayer(); }
                


                //if (E_HP <= 0) { fighter->Die();  fighter->setDinoSprite(); go = Win; sf::sleep(delay); return; }
                //else if (P_HP <= 0) { enemy.Die();  fighter->setDinoSprite(); go = Lose; sf::sleep(delay); return; }
            }

            if (E_HP <= 0) {
                atk.B_Sprite.setTexture(exit);
                atk.B_Sprite.setPosition(350, 400);
                enemy.Die();
                fighter->setDinoSprite();
                if (atk.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    { go = Win; return; }
                }
            }

            if (P_HP <= 0) {
                atk.B_Sprite.setTexture(exit);
                atk.B_Sprite.setPosition(350, 400);
                fighter->Die();
                fighter->setDinoSprite();
                if (atk.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    { go = Lose; return; }
                }
            }
        }
            
        window.clear();
        window.draw(fht.B_Sprite);
        window.draw(location);
        window.draw(atk.B_Sprite);
        window.draw(yd);
        window.draw(ed);
        fighter->DrawDino(window);
        enemy.DrawDino(window);
        window.display();
    }

}
void ShopStart(sf::RenderWindow& window, GameOption& go) {
    sf::Texture shop;
    shop.loadFromFile("shop.png");
    Button shp;
    shp.B_Sprite.setTexture(shop);
    shp.B_Sprite.setPosition(100, 100);

    sf::Texture plain;
    plain.loadFromFile("plain.png");

    sf::Texture river;
    river.loadFromFile("river.png");

    sf::Texture mountain;
    mountain.loadFromFile("mt.png");

    Button shp_river;
    shp_river.B_Sprite.setTexture(river);
    shp_river.B_Sprite.setPosition(100, 300);
    Button shp_plain;
    shp_plain.B_Sprite.setTexture(plain);
    shp_plain.B_Sprite.setPosition(300, 300);
    Button shp_mt;
    shp_mt.B_Sprite.setTexture(mountain);
    shp_mt.B_Sprite.setPosition(500, 300);

    sf::Texture exit;
    exit.loadFromFile("exit.png");
    Button ext;
    ext.B_Sprite.setTexture(exit);
    ext.B_Sprite.setPosition(700, 700);


    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (shp_river.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) { go = Shop_River; return; }
            if (shp_plain.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) { go = Shop_River; return; }
            if (shp_mt.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) { go = Shop_Mountain; return; }
            if (ext.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))) { go = MainMenu; return; }

        }
        window.clear();
        window.draw(shp.B_Sprite);
        window.draw(shp_river.B_Sprite);
        window.draw(shp_plain.B_Sprite);
        window.draw(shp_mt.B_Sprite);
        window.draw(ext.B_Sprite);
        window.display();
    }

}
void ShopRiver(sf::RenderWindow& window, GameOption& go) {
    sf::Texture shop;
    shop.loadFromFile("shop.png");
    Button shp;
    shp.B_Sprite.setTexture(shop);
    shp.B_Sprite.setPosition(100, 100);

    

    sf::Texture exit;
    exit.loadFromFile("exit.png");
    Button ext;
    ext.B_Sprite.setTexture(exit);
    ext.B_Sprite.setPosition(700, 700);

    sf::Texture buy;
    buy.loadFromFile("buy.png");

    sf::Texture next;
    next.loadFromFile("next.png"); Button gonext;
    gonext.B_Sprite.setTexture(next);
    gonext.B_Sprite.setPosition(500, 400);

    Button buythis;
    buythis.B_Sprite.setTexture(buy);
    buythis.B_Sprite.setPosition(500, 600);

    Dino DrownMe;
    DrownMe.setFT(River);
    DrownMe.setSpritePos(window, 100, 300);

    GetBalance();

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (ext.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))) { go = MainMenu; return; }
            if (gonext.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) { go = Shop_Start; return; }
            if (buythis.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (Balance >= DrownMe.getCost()) {
                    SaveDino(DrownMe);
                    Balance -= DrownMe.getCost();
                    SaveBalance();
                    go = MainMenu;
                }
                else { go = LowBalance; }
            
            return;
            }

        }
        window.clear();
        window.draw(shp.B_Sprite);
        window.draw(buythis.B_Sprite);
        window.draw(gonext.B_Sprite);
        window.draw(ext.B_Sprite);
        DrownMe.DrawDino(window);
        DrownMe.PrintInfo(window, 100, 600);
        PrintBalance(window, 100, 650);
        window.display();
    }

}
void ShopMountain(sf::RenderWindow& window, GameOption& go) {
    sf::Texture shop;
    shop.loadFromFile("shop.png");
    Button shp;
    shp.B_Sprite.setTexture(shop);
    shp.B_Sprite.setPosition(100, 100);



    sf::Texture exit;
    exit.loadFromFile("exit.png");
    Button ext;
    ext.B_Sprite.setTexture(exit);
    ext.B_Sprite.setPosition(700, 700);

    sf::Texture buy;
    buy.loadFromFile("buy.png");

    sf::Texture next;
    next.loadFromFile("next.png"); Button gonext;
    gonext.B_Sprite.setTexture(next);
    gonext.B_Sprite.setPosition(500, 400);

    Button buythis;
    buythis.B_Sprite.setTexture(buy);
    buythis.B_Sprite.setPosition(500, 600);

    Dino EuthanizeMe;
    EuthanizeMe.setFT(Mountain);
    EuthanizeMe.setSpritePos(window, 100, 300);

    GetBalance();

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (ext.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))) { go = MainMenu; return; }
            if (gonext.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) { go = Shop_Start; return; }
            if (buythis.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (Balance >= EuthanizeMe.getCost()) {
                    SaveDino(EuthanizeMe);
                    Balance -= EuthanizeMe.getCost();
                    SaveBalance();
                    go = MainMenu;
                }
                else { go = LowBalance; }
                return;
            }

        }
        window.clear();
        window.draw(shp.B_Sprite);
        window.draw(buythis.B_Sprite);
        window.draw(gonext.B_Sprite);
        window.draw(ext.B_Sprite);
        EuthanizeMe.DrawDino(window);
        EuthanizeMe.PrintInfo(window, 100, 600);
        PrintBalance(window, 100, 650);
        window.display();
    }

}
void ShopPlain(sf::RenderWindow& window, GameOption& go) {
    sf::Texture shop;
    shop.loadFromFile("shop.png");
    Button shp;
    shp.B_Sprite.setTexture(shop);
    shp.B_Sprite.setPosition(100, 100);



    sf::Texture exit;
    exit.loadFromFile("exit.png");
    Button ext;
    ext.B_Sprite.setTexture(exit);
    ext.B_Sprite.setPosition(700, 700);

    sf::Texture buy;
    buy.loadFromFile("buy.png");

    sf::Texture next;
    next.loadFromFile("next.png"); Button gonext;
    gonext.B_Sprite.setTexture(next);
    gonext.B_Sprite.setPosition(500, 400);

    Button buythis;
    buythis.B_Sprite.setTexture(buy);
    buythis.B_Sprite.setPosition(500, 600);

    Dino KillMe;
    KillMe.setFT(Plain);
    KillMe.setSpritePos(window, 100, 300);

    GetBalance();

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (ext.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))) { go = MainMenu; return; }
            if (gonext.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) { go = Shop_Start; return; }
            if (buythis.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (Balance >= KillMe.getCost()) {
                    SaveDino(KillMe);
                    Balance -= KillMe.getCost();
                    SaveBalance();
                    go = MainMenu;
                }
                else { go = LowBalance; }
            }

        }
        window.clear();
        window.draw(shp.B_Sprite);
        window.draw(buythis.B_Sprite);
        window.draw(gonext.B_Sprite);
        window.draw(ext.B_Sprite);
        KillMe.DrawDino(window);
        KillMe.PrintInfo(window, 100, 600);
        PrintBalance(window, 100, 650);
        window.display();
    }

}
void GetMoreMoney(sf::RenderWindow& window, GameOption& go) {
    sf::Texture nomoney;
    nomoney.loadFromFile("nomoney.png");
    Button nm;
    nm.B_Sprite.setTexture(nomoney);
    nm.B_Sprite.setPosition(100, 100);


    sf::Texture exit;
    exit.loadFromFile("exit.png");
    Button ext;
    ext.B_Sprite.setTexture(exit);
    ext.B_Sprite.setPosition(300, 350);

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (ext.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))) { go = MainMenu; return; }

        }
        window.clear();
        window.draw(nm.B_Sprite);

        window.draw(ext.B_Sprite);
        window.display();
    }


}

void YouLose(sf::RenderWindow& window, GameOption& go) {
    sf::Text text;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setString("You lost!");
    text.setCharacterSize(15);
    text.setPosition(100, 100);


    sf::Texture exit;
    exit.loadFromFile("exit.png");
    Button ext;
    ext.B_Sprite.setTexture(exit);
    ext.B_Sprite.setPosition(300, 350);

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (ext.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))) { go = MainMenu; return; }

        }
        window.clear();
        window.draw(text);
        window.draw(ext.B_Sprite);
        window.display();
    }


}


void YouWin(sf::RenderWindow& window, GameOption& go) {
    sf::Text text;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setString("You win! Your reward is" + std::to_string(Reward));
    text.setCharacterSize(15);
    text.setPosition(100, 100);

    Balance += Reward;
    SaveBalance();

    sf::Texture exit;
    exit.loadFromFile("exit.png");
    Button ext;
    ext.B_Sprite.setTexture(exit);
    ext.B_Sprite.setPosition(300, 350);

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (ext.IsMouseOverButton(window) and sf::Mouse::isButtonPressed(sf::Mouse::Left) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))) { go = MainMenu; return; }

        }
        window.clear();
        window.draw(text);
        window.draw(ext.B_Sprite);
        window.display();
    }


}



    int main() { 

        sf::RenderWindow window(sf::VideoMode(800, 800), "Dino v2");

        while(true)
        {
            
            switch (Current) {
            case MainMenu:
                Menu(window, Current);
                break;
            case Shop_Start:
                ShopStart(window, Current);
                break;
                
            case Shop_River:
                ShopRiver(window, Current);
                break;
            case Shop_Mountain:
                ShopMountain(window, Current);
                break;
            case Shop_Plain:
                ShopPlain(window, Current);
                break;
            case FightLobby:
                Lobby(window, Current);
                break;
            case Fight:
                Fighting(window, Current);
                break;
            case LowBalance:
                GetMoreMoney(window, Current);
                break;
            case Win:
                YouWin(window, Current);
                break;
            case Lose:
                YouLose(window, Current);
                break;
            }
        }
        
        return 0; }