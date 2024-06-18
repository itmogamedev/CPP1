#include "shop.hpp"

void InitText(sf::Text mtext, float xpos, float ypos, sf::String str, int size_font = 60, sf::Color menu_text_color = sf::Color::White, int bord = 0, sf::Color boreder_color = sf::Color::White) {
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(boreder_color);
}

void shop(sf::RenderWindow& win)
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


    fstream cash; string path_cash = "cash.txt"; int Scash;
    fstream inv; string path_inv = "inventory.txt"; string Sinv;

    inv.open(path_inv, fstream::in | fstream::out | fstream::app); inv >> Sinv; inv.close();
    cash.open(path_cash, fstream::in | fstream::out | fstream::app); cash >> Scash; cash.close();

    bool Dino_B, Dino_V, endB, endV;

    sf::RectangleShape DinoBuyB(sf::Vector2f(450, 450));
    DinoBuyB.setPosition(sf::Vector2f(420, 200));
    sf::Texture TexB;
    TexB.loadFromFile("dinoB_fs.png");
    DinoBuyB.setTexture(&TexB);

    sf::RectangleShape DinoBuyV(sf::Vector2f(450, 450));
    DinoBuyV.setPosition(sf::Vector2f(1050, 200));
    sf::Texture TexV;
    TexV.loadFromFile("dinoV_fs.png");
    DinoBuyV.setTexture(&TexV);


    sf::Text buttonTGB ("Back", font);
    buttonTGB.setCharacterSize(100);
    buttonTGB.setFillColor(sf::Color(0,0,0));
    buttonTGB.setStyle(sf::Text::Bold);
    buttonTGB.setPosition(sf::Vector2f(760, 750));

    if (Sinv.find('B') == std::string::npos) {
        DinoBuyB.setFillColor(sf::Color(128, 128, 128));
        Dino_B = 0; endB = 1;
    }
    else { Dino_B = 1; endB = 0; DinoBuyB.setFillColor(sf::Color(128, 128, 128)); }

    if (Sinv.find('V') == std::string::npos) {
        DinoBuyV.setFillColor(sf::Color(128, 128, 128));
        Dino_V = 0; endV = 1;
    }
    else { Dino_V = 1; endV = 0; DinoBuyB.setFillColor(sf::Color(128, 128, 128)); }
    int c = 0;
    while (win.isOpen() and c == 0) {
        win.clear();
        sf::Event event_inv;

        win.clear();
        sf::Vector2i mousePoz = sf::Mouse::getPosition(win);
        while (win.pollEvent(event_inv))
        {
            if (event_inv.type == sf::Event::Closed)
                win.close();
            if (event_inv.type == sf::Event::MouseButtonPressed)
                if (event_inv.key.code == sf::Mouse::Left) {
                    if (DinoBuyB.getGlobalBounds().contains(mousePoz.x, mousePoz.y) and Dino_B == 0 and Scash >= 100) {
                        DinoBuyB.setFillColor(sf::Color(255, 255, 255)); Dino_B = 1; Scash = Scash - 100;

                    }
                    if (DinoBuyV.getGlobalBounds().contains(mousePoz.x, mousePoz.y) and Dino_V == 0 and Scash >= 100) {
                        DinoBuyV.setFillColor(sf::Color(255, 255, 255)); Dino_V = 1; Scash = Scash - 100;

                    }

                    if (buttonTGB.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
                        if (Dino_B == 1 and endB == 1) { Sinv = Sinv + 'B'; }
                        if (Dino_V == 1 and endV == 1) { Sinv = Sinv + 'V'; }
                        inv.open(path_inv, fstream::in | fstream::out); inv << Sinv; inv.close();
                        cash.open(path_cash, fstream::in | fstream::out); cash << Scash; cash.close();
                        c = 1;
                    }

                }
        }
        
        win.draw(background);
        Tcash.setString(std::to_string(Scash));
        Tcash.setCharacterSize(60);
        Tcash.setOutlineThickness(3);
        Tcash.setOutlineColor(sf::Color::Black);
        Tcash.setPosition(1600, 50);

        win.draw(Tcash);
        if (Dino_B == 1) DinoBuyB.setFillColor(sf::Color(255, 255, 255));
        if (Dino_V == 1) DinoBuyV.setFillColor(sf::Color(255, 255, 255));
        win.draw(DinoBuyB);
        win.draw(DinoBuyV);
        win.draw(buttonTGB);
        win.display();
    }
}
