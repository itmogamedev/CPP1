#pragma once

enum class Buy { lt1, lt2, lt3, back};
Buy shopin(sf::RenderWindow& window, sf::Font& font)
{
    int cu_ca, len = 0;
    std::string line;
    std::ifstream in("cash.txt");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            cu_ca = stoi(line);
        }
    }
    in.close();
    std::ifstream in2("dino_numbers.txt");
    if (in2.is_open())
    {
        while (getline(in2, line))
        {
            len = line.length();
        }
    }
    in2.close();

    Button lot1({ 600, 600 }, { 200, 250 }, sf::Color(20, 230, 230), "ter.jpg");
    UI stat1({ 600, 100 }, { 200, 850 }, sf::Color(20, 230, 230), 60, "20$", font);

    Button lot2({ 600, 600 }, { 1000, 250 }, sf::Color(20, 230, 230), "dip.jpg");
    UI stat2({ 600, 100 }, { 1000, 850 }, sf::Color(20, 230, 230), 60, "12$", font);

    Button lot3({ 600, 600 }, { 1800, 250 }, sf::Color(20, 230, 230), "tri.jpg");
    UI stat3({ 600, 100 }, { 1800, 850 }, sf::Color(20, 230, 230), 60, "16$", font);

    UI mon({ 410, 125 }, { 1100, 1100 }, sf::Color(20, 230, 230), 60, std::to_string(cu_ca).append("$"), font);

    Button back({ 410, 125 }, { 1100, 1300 }, sf::Color(20, 230, 230), "back.png");

    while (window.isOpen())
    {
        sf::Vector2i mPos = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (LIM <= 6)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (lot1.clicked(mPos))
                        {
                            lot1.color(sf::Color(20, 180, 180), window);
                            lot1.draw(window);
                            window.display();
                            Sleep(250);
                            if (len < 6) 
                            {
                                if (cu_ca >= 20) 
                                {
                                    stat1.text("-$", window);
                                    lot1.draw(window);
                                    cu_ca = cu_ca - 20;
                                    std::ofstream out;
                                    out.open("dino_numbers.txt", std::ios::app);
                                    out << 1;
                                    out.close();
                                    mon.text(std::to_string(cu_ca).append("$"), window);
                                    len += 1;
                                }
                                else
                                {
                                    UI alert2({ 1000, 100 }, { 800, 1100 }, sf::Color(20, 230, 230), 60, "You haven't enought money", font);
                                    alert2.draw(window);
                                    window.display();
                                    Sleep(1000);
                                }
                            }
                            else 
                            {
                                UI alert1({ 1000, 100 }, { 800, 1100 }, sf::Color(20, 230, 230), 60, "You haven't enought slots", font);
                                alert1.draw(window);
                                window.display();
                                Sleep(1000);
                            }
                        }
                        if (lot2.clicked(mPos))
                        {
                            lot2.color(sf::Color(20, 180, 180), window);
                            lot2.draw(window);
                            window.display();
                            Sleep(250);
                            if (len < 6)
                            {
                                if (cu_ca >= 12)
                                {
                                    stat2.text("-$", window);
                                    lot2.draw(window);
                                    cu_ca = cu_ca - 12;
                                    std::ofstream out;
                                    out.open("dino_numbers.txt", std::ios::app);
                                    out << 2;
                                    out.close();
                                    mon.text(std::to_string(cu_ca).append("$"), window);
                                    len += 1;
                                }
                                else
                                {
                                    UI alert2({ 1000, 100 }, { 800, 1100 }, sf::Color(20, 230, 230), 60, "You haven't enought money", font);
                                    alert2.draw(window);
                                    window.display();
                                    Sleep(1000);
                                }
                            }
                            else 
                            {
                                UI alert1({ 1000, 100 }, { 800, 1100 }, sf::Color(20, 230, 230), 60, "You haven't enought slots", font);
                                alert1.draw(window);
                                window.display();
                                Sleep(1000);
                            }
                        }
                        if (lot3.clicked(mPos))
                        {
                            lot3.color(sf::Color(20, 180, 180), window);
                            lot3.draw(window);
                            window.display();
                            Sleep(250);
                            if (len < 6)
                            {
                                if (cu_ca >= 16)
                                {
                                    stat3.text("-$", window);
                                    lot3.draw(window);
                                    cu_ca = cu_ca - 16;
                                    std::ofstream out;
                                    out.open("dino_numbers.txt", std::ios::app);
                                    out << 3;
                                    out.close();
                                    mon.text(std::to_string(cu_ca).append("$"), window);
                                    len += 1;
                                }
                                else
                                {
                                    UI alert2({ 1000, 100 }, { 800, 1100 }, sf::Color(20, 230, 230), 60, "You haven't enought money", font);
                                    alert2.draw(window);
                                    window.display();
                                    Sleep(1000);
                                }
                            }
                            else 
                            {
                                UI alert1({ 1000, 100 }, { 800, 1100 }, sf::Color(20, 230, 230), 60, "You haven't enought slots", font);
                                alert1.draw(window);
                                window.display();
                                Sleep(1000);
                            }
                        }
                        if (back.clicked(mPos))
                        {
                            back.color(sf::Color(20, 180, 180), window);
                            back.draw(window);
                            window.display();
                            Sleep(250);
                            std::ofstream out;
                            out.open("cash.txt");
                            if (out.is_open())
                            {
                                out << cu_ca;
                            }
                            out.close();
                            return Buy::back;
                        }
                    }
                }
                else 
                {
                
                }
            }
        }
        sf::Texture start;
        start.loadFromFile("font.png");
        sf::RectangleShape HAHAShape(sf::Vector2f(window.getSize()));
        HAHAShape.setTexture(&start);
        HAHAShape.setPosition(0, 0);
        window.draw(HAHAShape);
        lot1.color(sf::Color(20, 230, 230), window);
        lot2.color(sf::Color(20, 230, 230), window);
        lot3.color(sf::Color(20, 230, 230), window);
        lot1.draw(window);
        stat1.draw(window);
        lot2.draw(window);
        stat2.draw(window);
        lot3.draw(window);
        stat3.draw(window);
        mon.draw(window);
        back.draw(window);
        window.display();
    }
}