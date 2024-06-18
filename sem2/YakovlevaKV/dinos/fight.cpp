#include "fight.hpp"

enum Location { Plain, River, Mountin };

void attack() {}

void attack_enemy() {}

struct Dino {
    int damage = 0;
    int hp = 0;
    char place = 'o';
    bool isdie = 0;
    sf::Texture DinoTexture;
    sf::Sprite DinoSprite;
};
struct Trex : public Dino {
    Trex() {
        damage = 4;
        hp = 10;
        place = 'p';
        DinoTexture.loadFromFile("dinoR.png");
        DinoSprite.setTexture(DinoTexture);
        DinoSprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
    }
};
struct Stegosaurus : public Dino {
    Stegosaurus() {
        damage = 3;
        hp = 11;
        place = 'm';
        DinoTexture.loadFromFile("dinoS.png");
        DinoSprite.setTexture(DinoTexture);
        DinoSprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
    }
};
struct Triceratops : public Dino {
    Triceratops() {
        damage = 5;
        hp = 8;
        place = 'r';
        DinoTexture.loadFromFile("dinoT.png");
        DinoSprite.setTexture(DinoTexture);
        DinoSprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
    }
};
struct Brachiosaurus : public Dino {
    Brachiosaurus() {
        damage = 2;
        hp = 14;
        place = 'm';
        DinoTexture.loadFromFile("dinoB.png");
        DinoSprite.setTexture(DinoTexture);
        DinoSprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
    }
};
struct Velociraptor : public Dino {
    Velociraptor() {
        damage = 6;
        hp = 7;
        place = 'r';
        DinoTexture.loadFromFile("dinoV.png");
        DinoSprite.setTexture(DinoTexture);
        DinoSprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
    }
};

int Damage(char pl, int l, int dd) {
    if (l == 0) {
        if (pl == 'p') return dd * 2;
        else return dd;
    }
    if (l == 1) {
        if (pl == 'r') return dd * 2;
        else return dd;
    }
    if (l == 2) {
        if (pl == 'm') return dd * 2;
        else return dd;
    }
    return 0;
}


int fight(sf::RenderWindow& win)
{
    sf::Music main;
    main.openFromFile("fight.ogg");
    main.play();
    main.setLoop(true);

    srand((unsigned int)time(NULL));
    int locat = rand() % 3;

    sf::Texture Texforback;
    Texforback.loadFromFile("main.png");
    sf::RectangleShape background(sf::Vector2f(1920, 1080));
    background.setTexture(&Texforback);
    background.setPosition(sf::Vector2f(0, 0));
    if (locat == Plain) { Texforback.loadFromFile("field.png");  }
    if (locat == River) { Texforback.loadFromFile("redgrass.png"); }
    if (locat == Mountin) { Texforback.loadFromFile("lava.png"); }
    background.setTexture(&Texforback);

    Trex PTrex; Stegosaurus PStegosaurus; Triceratops PTriceratops; Brachiosaurus PBrachiosaurus; Velociraptor PVelociraptor;
    Trex ETrex; Stegosaurus EStegosaurus; Triceratops ETriceratops; Brachiosaurus EBrachiosaurus; Velociraptor EVelociraptor;

    fstream deck; string path_deck = "deck.txt"; string Sdeck;
    deck.open(path_deck); deck >> Sdeck; deck.close();
    bool pd1 = 0, pd2 = 0, pd3 = 0, ed1 = 0, ed2 = 0, ed3 = 0;
    vector<Dino> Pdeck;
    vector<Dino> Edeck;

    std::map<char, Dino> dinoMap = { {'R', PTrex}, {'S', PStegosaurus}, {'T', PTriceratops}, {'B', PBrachiosaurus}, {'V', PVelociraptor} };

    for (char c : Sdeck) {
        if (dinoMap.find(c) != dinoMap.end()) {
            Pdeck.push_back(dinoMap[c]);
        }
    }

    std::map<int, Dino> enemyDinoMap = { {0, ETrex}, {1, EStegosaurus}, {2, ETriceratops}, {3, EBrachiosaurus}, {4, EVelociraptor} };

    int a = abs(rand() % 5); int b = abs(rand() % 5); int c = abs(rand() % 5);

    for (int i : {a, b, c}) {
        Edeck.push_back(enemyDinoMap[i]);
    }

    for (int i = 0; i < 3; i++) {
        Pdeck[i].DinoSprite.setPosition(sf::Vector2f(172, 80 + i * 360));
        Edeck[i].DinoSprite.setPosition(sf::Vector2f(1528, 80 + i * 360));
    }

    int attack_gamage = Damage(Pdeck[0].place, locat, Pdeck[0].damage);
    sf::Clock clock;
    int ed = 0, pd = 0;
    int actDino = 0;
    
    while (win.isOpen() and ed != 3 and pd != 3)
    {
        if (Pdeck[actDino].isdie == 1) {
            if (actDino == 2) {
                actDino = 0;
                attack_gamage = Damage(Pdeck[0].place, locat, Pdeck[0].damage);
            }
            else {
                actDino++;
                attack_gamage = Damage(Pdeck[actDino].place, locat, Pdeck[actDino].damage);
            }
        }
        sf::Event event;
        sf::Vector2i mousePoz = sf::Mouse::getPosition(win);
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { win.close(); }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == sf::Mouse::Left) {
                    for (int i = 0; i < 3; i++) {
                        if (Pdeck[i].DinoSprite.getGlobalBounds().contains(mousePoz.x, mousePoz.y) and Pdeck[i].isdie == 0) {
                            attack_gamage = Damage(Pdeck[i].place, locat, Pdeck[i].damage);
                            Pdeck[i].DinoSprite.setTextureRect(sf::IntRect(200, 0, 200, 200));
                            actDino = i;
                        }
                    }

                    for (int i = 0; i < 3; i++) {
                        if (Edeck[i].DinoSprite.getGlobalBounds().contains(mousePoz.x, mousePoz.y) and Edeck[i].isdie == 0) {
                            Edeck[i].hp = Edeck[i].hp - attack_gamage;
                            Pdeck[actDino].DinoSprite.setTextureRect(sf::IntRect(200, 0, 200, 200));
                            if (Edeck[i].hp <= 0 and Edeck[i].isdie == 0) {
                                Edeck[i].DinoSprite.setTextureRect(sf::IntRect(400, 0, 200, 200));
                                ed++;
                                Edeck[i].isdie = 1;
                            }
                            else {
                                Edeck[i].DinoSprite.setTextureRect(sf::IntRect(200, 0, 200, 200));
                            }
                            Pdeck[actDino].hp = Pdeck[actDino].hp - Damage(Edeck[i].place, locat, Edeck[i].damage);
                            if (Pdeck[actDino].hp <= 0) {
                                Pdeck[actDino].isdie = 1;
                                Pdeck[actDino].DinoSprite.setTextureRect(sf::IntRect(400, 0, 200, 200));
                                pd++;
                            }
                        }
                    }
                    
                    
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.key.code == sf::Mouse::Left) {
                    for (int i = 0; i < 3; i++) {
                        if (Pdeck[i].DinoSprite.getGlobalBounds().contains(mousePoz.x, mousePoz.y) and Pdeck[i].isdie == 0) {
                            clock.restart();
                            while (clock.getElapsedTime() < sf::milliseconds(500)) {}
                            Pdeck[i].DinoSprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
                        }
                    }

                    for (int i = 0; i < 3; i++) {
                        if (Edeck[i].DinoSprite.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                            clock.restart();
                            while (clock.getElapsedTime() < sf::milliseconds(500)) {}
                            if (Edeck[i].isdie == 1 and Pdeck[actDino].isdie == 1) {}
                            else if (Edeck[i].isdie == 1) {
                                Pdeck[actDino].DinoSprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
                            }
                            else if (Pdeck[actDino].isdie == 1) {
                                Edeck[i].DinoSprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
                            }
                            else {
                                Edeck[i].DinoSprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
                                Pdeck[actDino].DinoSprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
                            }
                        }
                    }

                }

            }

        }
            win.clear();
            win.draw(background);
            for (int i = 0; i < 3; i++) {
                win.draw(Pdeck[i].DinoSprite);
                win.draw(Edeck[i].DinoSprite);
            }
            win.display();
        
    }
    main.stop();
    if (ed == 3) return 1;
    else return 0;
}
