#pragma once

enum class Inven { slt1, slt2, slt3, slt4, slt5, slt6, back };
Inven inven(sf::RenderWindow& window, sf::Font& font)
{
    std::string a;
    std::string M[6];
    for (int i = 0; i < 6; i++)
    {
        M[i] = "";
        MASS[i] = 0;
    }
    int tmp = 0;

    Button slot1({ 550, 550 }, { 200, 100 }, sf::Color(20, 230, 230), "");
    Button slot2({ 550, 550 }, { 1000, 100 }, sf::Color(20, 230, 230), "");
    Button slot3({ 550, 550 }, { 1800, 100 }, sf::Color(20, 230, 230), "");
    Button slot4({ 550, 550 }, { 200, 700 }, sf::Color(20, 230, 230), "");
    Button slot5({ 550, 550 }, { 1000, 700 }, sf::Color(20, 230, 230), "");
    Button slot6({ 550, 550 }, { 1800, 700 }, sf::Color(20, 230, 230), "");
    Button back({ 410, 125 }, { 1000, 1300 }, sf::Color(20, 230, 230), "back.png");

    std::string line, ln;
    std::ifstream in("dino_numbers.txt");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            ln = line;
        }
    }
    if (ln.length() == 0) 
    {
        UI alert1({ 1000, 100 }, { 800, 1100 }, sf::Color(20, 230, 230), 60, "You have no dino", font);
        alert1.draw(window);
        window.display();
        Sleep(1000);
        return Inven::back;
    }

    for (int i = 0; i < ln.length(); ++i)
    {
        a = ln[i];
        MASS[i] = std::stoi(a);
    }

    for (int i = 0; i < 6; ++i)
    {
        if (MASS[i] == 1)
        {
            M[i] = "ter.jpg";
        }
        else if (MASS[i] == 2)
        {
            M[i] = "dip.jpg";
        }
        else if (MASS[i] == 3)
        {
            M[i] = "tri.jpg";
        }
        else
        {
            M[i] = "";
        }
    }

    if (stsl1 == true) {
        slot1.color(sf::Color(20, 230, 20), window);
    }
    if (stsl2 == true) {
        slot2.color(sf::Color(20, 230, 20), window);
    }
    if (stsl3 == true) {
        slot3.color(sf::Color(20, 230, 20), window);
    }
    if (stsl4 == true) {
        slot4.color(sf::Color(20, 230, 20), window);
    }
    if (stsl5 == true) {
        slot5.color(sf::Color(20, 230, 20), window);
    }
    if (stsl6 == true) {
        slot6.color(sf::Color(20, 230, 20), window);
    }
    slot1.img(M[0], window);
    slot2.img(M[1], window);
    slot3.img(M[2], window);
    slot4.img(M[3], window);
    slot5.img(M[4], window);
    slot6.img(M[5], window);

    while (window.isOpen()) 
    {

        sf::Vector2i mPos = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (slot1.clicked(mPos) && (MASS[0] == 1 || MASS[0] == 2 || MASS[0] == 3))
                    {
                        if (stsl1 == false) 
                        {
                            if (tem < 3)
                            {
                                slot1.color(sf::Color(20, 230, 20), window);
                                ++tem;
                                stsl1 = true;
                            }
                        }
                        else
                        {
                            slot1.color(sf::Color(20, 230, 230), window);
                            --tem;
                            stsl1 = false;
                        }
                    }
                    if (slot2.clicked(mPos) && (MASS[1] == 1 || MASS[1] == 2 || MASS[1] == 3))
                    {
                        if (stsl2 == false)
                        {
                            if (tem < 3)
                            {
                                slot2.color(sf::Color(20, 230, 20), window);
                                tem += 1;
                                stsl2 = true;
                            }
                        }
                        else
                        {
                            slot2.color(sf::Color(20, 230, 230), window);
                            tem -= 1;
                            stsl2 = false;
                        }
                    }
                    if (slot3.clicked(mPos) && (MASS[2] == 1 || MASS[2] == 2 || MASS[2] == 3))
                    {
                        if (stsl3 == false)
                        {
                            if (tem < 3)
                            {
                                slot3.color(sf::Color(20, 230, 20), window);
                                tem += 1;
                                stsl3 = true;
                            }
                        }
                        else
                        {
                            slot3.color(sf::Color(20, 230, 230), window);
                            tem -= 1;
                            stsl3 = false;
                        }

                    }
                    if (slot4.clicked(mPos) && (MASS[3] == 1 || MASS[3] == 2 || MASS[3] == 3))
                    {
                        if (stsl4 == false)
                        {
                            if (tem < 3)
                            {
                                slot4.color(sf::Color(20, 230, 20), window);
                                tem += 1;
                                stsl4 = true;
                            }
                        }
                        else
                        {
                            slot4.color(sf::Color(20, 230, 230), window);
                            tem -= 1;
                            stsl4 = false;
                        }
                    }
                    if (slot5.clicked(mPos) && (MASS[4] == 1 || MASS[4] == 2 || MASS[4] == 3))
                    {
                        if (stsl5 == false)
                        {
                            if (tem < 3)
                            {
                                slot5.color(sf::Color(20, 230, 20), window);
                                tem += 1;
                                stsl5 = true;
                            }
                        }
                        else
                        {
                            slot5.color(sf::Color(20, 230, 230), window);
                            tem -= 1;
                            stsl5 = false;
                        }
                    }
                    if (slot6.clicked(mPos) && (MASS[5] == 1 || MASS[5] == 2 || MASS[5] == 3))
                    {
                        if (stsl6 == false)
                        {
                            if (tem < 3)
                            {
                                slot6.color(sf::Color(20, 230, 20), window);
                                tem += 1;
                                stsl6 = true;
                            }
                        }
                        else
                        {
                            slot6.color(sf::Color(20, 230, 230), window);
                            tem -= 1;
                            stsl6 = false;
                        }

                    }
                    if (back.clicked(mPos))
                    {
                        back.color(sf::Color(20, 180, 180), window);
                        back.draw(window);
                        window.display();
                        Sleep(250);
                        tmp = 0;
                        std::ofstream out;
                        out.open("pull.txt");
                        if (out.is_open())
                        {
                            if (stsl1 == true) {
                                out << MASS[0];
                            } else {
                                ++tmp;
                            }
                            if (stsl2 == true) {
                                out << MASS[1];
                            } else {
                                ++tmp;
                            }
                            if (stsl3 == true) {
                                out << MASS[2];
                            } else {
                                ++tmp;
                            }
                            if (stsl4 == true) {
                                out << MASS[3];
                            } else {
                                ++tmp;
                            }
                            if (stsl5 == true) {
                                out << MASS[4];
                            } else {
                                ++tmp;
                            }
                            if (stsl6 == true) {
                                out << MASS[5];
                            } else {
                                ++tmp;
                            }
                        }
                        out.close();
                        if (tmp != 6) {
                            slot1.img("", window);
                            slot2.img("", window);
                            slot3.img("", window);
                            slot4.img("", window);
                            slot5.img("", window);
                            slot6.img("", window);
                            return Inven::back;
                        } else {
                            UI alert1({ 1000, 100 }, { 800, 1100 }, sf::Color(20, 230, 230), 60, "Chose 1-3 dino", font);
                            alert1.draw(window);
                            window.display();
                            Sleep(1000);
                        }
                    }
                }
            }
        }
        sf::Texture start;
        start.loadFromFile("font.png");
        sf::RectangleShape HAHAShape(sf::Vector2f(window.getSize()));
        HAHAShape.setTexture(&start);
        HAHAShape.setPosition(0, 0);
        window.draw(HAHAShape);

        slot1.draw(window);
        slot2.draw(window);
        slot3.draw(window);
        slot4.draw(window);
        slot5.draw(window);
        slot6.draw(window);
        back.draw(window);

        window.display();
        
    }
}