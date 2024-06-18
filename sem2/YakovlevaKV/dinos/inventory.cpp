#include "inventory.hpp"



void inventory(sf::RenderWindow& win)
{
    
    sf::Font font;
    font.loadFromFile("FontOver.otf");
    sf::Text Tcash;
    Tcash.setFont(font);
    
    sf::Texture Texforback;
    Texforback.loadFromFile("main.png");
    sf::RectangleShape background(sf::Vector2f(1920, 1080));
    background.setTexture(&Texforback);
    background.setPosition(sf::Vector2f(0, 0));



    fstream deck; string path_deck = "deck.txt"; string Sdeck;
    ifstream inv; string path_inv = "inventory.txt"; string Sinv;

    inv.open(path_inv); inv >> Sinv; inv.close();
    bool Dino_R, Dino_S, Dino_T, Dino_B, Dino_V;
    sf::RectangleShape DinoBuyR(sf::Vector2f(200, 200));
    DinoBuyR.setPosition(sf::Vector2f(172, 300));
    sf::Texture TexR;
    TexR.loadFromFile("dinoR_fs.png");
    DinoBuyR.setTexture(&TexR);

    sf::RectangleShape DinoBuyS(sf::Vector2f(200, 200));
    DinoBuyS.setPosition(sf::Vector2f(516, 300));
    sf::Texture TexS;
    TexS.loadFromFile("dinoS_fs.png");
    DinoBuyS.setTexture(&TexS);

    sf::RectangleShape DinoBuyT(sf::Vector2f(200, 200));
    DinoBuyT.setPosition(sf::Vector2f(860, 300));
    sf::Texture TexT;
    TexT.loadFromFile("dinoT_fs.png");
    DinoBuyT.setTexture(&TexT);

    sf::RectangleShape DinoBuyB(sf::Vector2f(200, 200));
    DinoBuyB.setPosition(sf::Vector2f(1204, 300));
    sf::Texture TexB;
    TexB.loadFromFile("dinoB_fs.png");
    DinoBuyB.setTexture(&TexB);

    sf::RectangleShape DinoBuyV(sf::Vector2f(200, 200));
    DinoBuyV.setPosition(sf::Vector2f(1548, 300));
    sf::Texture TexV;
    TexV.loadFromFile("dinoV_fs.png");
    DinoBuyV.setTexture(&TexV);



    sf::Text buttonTGB ("Back", font);
    buttonTGB.setCharacterSize(100);
    buttonTGB.setFillColor(sf::Color(0,0,0));
    buttonTGB.setStyle(sf::Text::Bold);
    buttonTGB.setPosition(sf::Vector2f(760, 750));

    if (Sinv.find("R") == std::string::npos) {
        DinoBuyR.setFillColor(sf::Color(128, 128, 128));
        Dino_R = 0;
    }
    else { Dino_R = 1; }

    if (Sinv.find('S') == std::string::npos) {
        DinoBuyS.setFillColor(sf::Color(128, 128, 128));
        Dino_S = 0;
    }
    else { Dino_S = 1; }

    if (Sinv.find('T') == std::string::npos) {
        DinoBuyT.setFillColor(sf::Color(128, 128, 128));
        Dino_T = 0;
    }
    else { Dino_T = 1; }

    if (Sinv.find('B') == std::string::npos) {
        DinoBuyB.setFillColor(sf::Color(128, 128, 128));
        Dino_B = 0;
    }
    else { Dino_B = 1; }

    if (Sinv.find('V') == std::string::npos) {
        DinoBuyV.setFillColor(sf::Color(128, 128, 128));
        Dino_V = 0;
    }
    else { Dino_V = 1; }
    deck.open(path_deck, fstream::in | fstream::out); deck >> Sdeck; deck.close();

    int count_dino = 0;
    bool fR = 1; bool fS = 1; bool fT = 1; bool fB = 1; bool fV = 1;
    if (Sdeck.find('R') == -1 and Dino_R == 1) { DinoBuyR.setFillColor(sf::Color(0, 100, 100)); fR = 0; }
    else if (Dino_R == 1) { count_dino++; }
    if (Sdeck.find('S') == -1 and Dino_S == 1) { DinoBuyS.setFillColor(sf::Color(0, 100, 100)); fS = 0; }
    else if (Dino_S == 1) { count_dino++; }
    if (Sdeck.find('T') == -1 and Dino_T == 1) { DinoBuyT.setFillColor(sf::Color(0, 100, 100)); fT = 0; }
    else if (Dino_T == 1) { count_dino++; }
    if (Sdeck.find('B') == -1 and Dino_B == 1) { DinoBuyB.setFillColor(sf::Color(0, 100, 100)); fB = 0; }
    else if (Dino_B == 1) { count_dino++; }
    if (Sdeck.find('V') == -1 and Dino_V == 1) { DinoBuyV.setFillColor(sf::Color(0, 100, 100)); fV = 0; }
    else if (Dino_V == 1) { count_dino++; }
    int c = 0;
    while (win.isOpen() and c == 0) {

        deck.open(path_deck, fstream::in | fstream::out); deck >> Sdeck; deck.close();
        sf::Event event_inv;

        win.clear();
        sf::Vector2i mousePoz = sf::Mouse::getPosition(win);
        while (win.pollEvent(event_inv))
        {
            if (event_inv.type == sf::Event::Closed)
                win.close();
            if (event_inv.type == sf::Event::MouseButtonPressed)
                if (event_inv.key.code == sf::Mouse::Left) {
                    if (DinoBuyR.getGlobalBounds().contains(mousePoz.x, mousePoz.y) and Dino_R == 1) {
                        if (fR == 0) {
                            fR = 1; DinoBuyR.setFillColor(sf::Color(255, 255, 255)); count_dino++;
                        }
                        else {
                            fR = 0; DinoBuyR.setFillColor(sf::Color(0, 100, 100)); count_dino--;
                        }
                    }
                    if (DinoBuyS.getGlobalBounds().contains(mousePoz.x, mousePoz.y) and Dino_S == 1) {
                        if (fS == 0) {
                            fS = 1; DinoBuyS.setFillColor(sf::Color(255, 255, 255)); count_dino++;
                        }
                        else {
                            fS = 0; DinoBuyS.setFillColor(sf::Color(0, 100, 100)); count_dino--;
                        }
                    }
                    if (DinoBuyT.getGlobalBounds().contains(mousePoz.x, mousePoz.y) and Dino_T == 1) {
                        if (fT == 0) {
                            fT = 1; DinoBuyT.setFillColor(sf::Color(255, 255, 255)); count_dino++;
                        }
                        else {
                            fT = 0; DinoBuyT.setFillColor(sf::Color(0, 100, 100)); count_dino--;
                        }
                    }
                    if (DinoBuyB.getGlobalBounds().contains(mousePoz.x, mousePoz.y) and Dino_B == 1) {
                        if (fB == 0) {
                            fB = 1; DinoBuyB.setFillColor(sf::Color(255, 255, 255)); count_dino++;
                        }
                        else {
                            fB = 0; DinoBuyB.setFillColor(sf::Color(0, 100, 100)); count_dino--;
                        }
                    }
                    if (DinoBuyV.getGlobalBounds().contains(mousePoz.x, mousePoz.y) and Dino_V == 1) {
                        if (fV == 0) {
                            fV = 1; DinoBuyV.setFillColor(sf::Color(255, 255, 255)); count_dino++;
                        }
                        else {
                            fV = 0; DinoBuyV.setFillColor(sf::Color(0, 100, 100)); count_dino--;
                        }
                    }
                    if (buttonTGB.getGlobalBounds().contains(mousePoz.x, mousePoz.y) and count_dino == 3) {
                        string t_s = "";
                        if (fR) t_s += 'R';
                        if (fS) t_s += 'S';
                        if (fT) t_s += 'T';
                        if (fB) t_s += 'B';
                        if (fV) t_s += 'V';
                        t_s += '_';
                        deck.open(path_deck, fstream::in | fstream::out); deck << t_s; deck.close();
                        c = 1;
                    }
                }
        };
        win.draw(background);
        win.draw(DinoBuyR);
        win.draw(DinoBuyS);
        win.draw(DinoBuyT);
        win.draw(DinoBuyB);
        win.draw(DinoBuyV);
        win.draw(buttonTGB);
        win.display();

    }

}
