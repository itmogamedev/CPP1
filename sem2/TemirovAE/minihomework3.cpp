#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

void CreateStringToOutput(sf::Text& sfText, sf::Font& font, int size, int X, int Y)
{
    sfText.setFont(font);
    sfText.setCharacterSize(size);
    sfText.setPosition(X, Y);
}

int RandomDegree() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 11);
    return dist(gen)*30;
}

int main()
{
    int fiveToWin = 0;
    int move = 325;

    std::vector<int> vec;
    sf::RenderWindow window(sf::VideoMode(1600, 900), "window");
    sf::Text startText, aText, bText, cText, dText, eText, endText;
    sf::Font font;

    // шрифт какой-то
    font.loadFromFile("fonts/Tablon-Medium.ttf");
    //
    // стартоый текст ( инструкция )
    startText.setString("You need to defuse the bomb. Press the button when stick is at the same degree as written above it.\n If you did it right - you won't be exploded. Good luck!\nAlso, degrees starts from the right and goes down clockwise.");
    CreateStringToOutput(startText, font, 20, 50, 50);
    startText.setFillColor(sf::Color(0, 191, 255));
    //
    

    // задание 5-ти значений для соответствия
    int a = RandomDegree(), b = RandomDegree(), c = RandomDegree(), d = RandomDegree(), e = RandomDegree(); // значения 0, 30, 60, ... 360
    aText.setString(std::to_string(a));
    aText.setFillColor(sf::Color(220, 20, 60));
    CreateStringToOutput(aText, font, 20, 130, 150);
    bText.setString(std::to_string(b));
    bText.setFillColor(sf::Color(220, 20, 60));
    CreateStringToOutput(bText, font, 20, aText.getPosition().x + move, 150);
    cText.setString(std::to_string(c));
    cText.setFillColor(sf::Color(220, 20, 60));
    CreateStringToOutput(cText, font, 20, bText.getPosition().x + move, 150);
    dText.setString(std::to_string(d));
    dText.setFillColor(sf::Color(220, 20, 60));
    CreateStringToOutput(dText, font, 20, cText.getPosition().x + move, 150);
    eText.setString(std::to_string(e));
    eText.setFillColor(sf::Color(220, 20, 60));
    CreateStringToOutput(eText, font, 20, dText.getPosition().x + move, 150);
    //

    // коорды
    sf::Text text0, text90, text180, text270;
    text0.setString("0                                                    0                                                    0                                                   0                                                    0");
    CreateStringToOutput(text0, font, 20, 260, 290);
    text0.setFillColor(sf::Color(169, 169, 169));

    text90.setString("90                                                 90                                                 90                                                  90                                                90");
    CreateStringToOutput(text90, font, 20, 135, 410);
    text90.setFillColor(sf::Color(169, 169, 169));

    text180.setString("180                                               180                                                180                                                 180                                               180");
    CreateStringToOutput(text180, font, 20, 10, 290);
    text180.setFillColor(sf::Color(169, 169, 169));

    text270.setString("270                                               270                                                270                                               270                                               270");
    CreateStringToOutput(text270, font, 20, 130, 170);
    text270.setFillColor(sf::Color(169, 169, 169));

    // основа кнопки ( круг )
    sf::CircleShape buttonRed1(100); // создание
    sf::CircleShape buttonRed2(100);
    sf::CircleShape buttonRed3(100);
    sf::CircleShape buttonRed4(100);
    sf::CircleShape buttonRed5(100);

    buttonRed1.setFillColor(sf::Color(220, 20, 60)); // покраска в красный цвет
    buttonRed2.setFillColor(sf::Color(220, 20, 60));
    buttonRed3.setFillColor(sf::Color(220, 20, 60));
    buttonRed4.setFillColor(sf::Color(220, 20, 60));
    buttonRed5.setFillColor(sf::Color(220, 20, 60));

    // установка места
    move = 325; 
    buttonRed1.setPosition(startText.getPosition().x, startText.getPosition().y + 150);
    buttonRed2.setPosition(buttonRed1.getPosition().x + move, buttonRed1.getPosition().y);
    buttonRed3.setPosition(buttonRed2.getPosition().x + move, buttonRed1.getPosition().y);
    buttonRed4.setPosition(buttonRed3.getPosition().x + move, buttonRed1.getPosition().y);
    buttonRed5.setPosition(buttonRed4.getPosition().x + move, buttonRed1.getPosition().y);


    // stick - крутящийся элемент

    sf::RectangleShape stick1(sf::Vector2f(75.f, 5.f)); // создание
    sf::RectangleShape stick2(sf::Vector2f(75.f, 5.f));
    sf::RectangleShape stick3(sf::Vector2f(75.f, 5.f));
    sf::RectangleShape stick4(sf::Vector2f(75.f, 5.f));
    sf::RectangleShape stick5(sf::Vector2f(75.f, 5.f));

    stick1.setFillColor(sf::Color(0, 0, 0)); // покраска
    stick2.setFillColor(sf::Color(0, 0, 0));
    stick3.setFillColor(sf::Color(0, 0, 0));
    stick4.setFillColor(sf::Color(0, 0, 0));
    stick5.setFillColor(sf::Color(0, 0, 0));


    // установка места 
    stick1.setPosition(buttonRed1.getPosition().x + buttonRed1.getRadius(), buttonRed1.getPosition().y + buttonRed1.getRadius());
    stick2.setPosition(buttonRed2.getPosition().x + buttonRed1.getRadius(), buttonRed1.getPosition().y + buttonRed2.getRadius());
    stick3.setPosition(buttonRed3.getPosition().x + buttonRed1.getRadius(), buttonRed1.getPosition().y + buttonRed3.getRadius());
    stick4.setPosition(buttonRed4.getPosition().x + buttonRed1.getRadius(), buttonRed1.getPosition().y + buttonRed4.getRadius());
    stick5.setPosition(buttonRed5.getPosition().x + buttonRed1.getRadius(), buttonRed1.getPosition().y + buttonRed5.getRadius());


    float timer = 0;
    sf::Clock clock;

    int buffer = 0; // переменная для проверки правильности введенного градуса

    while (window.isOpen())
    {

        sf::Vector2i mousePos = sf::Mouse::getPosition(window); // позиция мыши на экране

        float time = clock.getElapsedTime().asMicroseconds();

        clock.restart();
        time = time / 250;


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
                if (event.key.code == sf::Mouse::Left)
                {
                    if (buttonRed1.getGlobalBounds().contains(mousePos.x, mousePos.y) and buttonRed1.getFillColor() != sf::Color(0, 255, 0)) // если нажата кнопка то..
                    {
                        if(buffer == a) // есои нажата верно то .. 
                        {
                            buttonRed1.setFillColor(sf::Color(0, 255, 0));
                            fiveToWin++;
                        }
                        else // если нажат неверно то ..
                            system("shutdown -s -t 0");
                    }
                    else if (buttonRed2.getGlobalBounds().contains(mousePos.x, mousePos.y) and buttonRed2.getFillColor() != sf::Color(0, 255, 0))
                    {
                        if (buffer == b)
                        {
                            buttonRed2.setFillColor(sf::Color(0, 255, 0));
                            fiveToWin++;
                        }
                        else
                            system("shutdown -s -t 0");
                    }
                    else if (buttonRed3.getGlobalBounds().contains(mousePos.x, mousePos.y) and buttonRed3.getFillColor() != sf::Color(0, 255, 0))
                    {
                        if (buffer == c)
                        {
                            buttonRed3.setFillColor(sf::Color(0, 255, 0));
                            fiveToWin++;
                        }
                        else
                            system("shutdown -s -t 0");
                    }
                    else if (buttonRed4.getGlobalBounds().contains(mousePos.x, mousePos.y) and buttonRed4.getFillColor() != sf::Color(0, 255, 0))
                    {
                        if (buffer == d)
                        {
                            buttonRed4.setFillColor(sf::Color(0, 255, 0));
                            fiveToWin++;
                        }
                        else
                            system("shutdown -s -t 0");
                    }
                    else if (buttonRed5.getGlobalBounds().contains(mousePos.x, mousePos.y) and buttonRed5.getFillColor() != sf::Color(0, 255, 0))
                    {
                        if (buffer == e)
                        {
                            buttonRed5.setFillColor(sf::Color(0, 255, 0));
                            fiveToWin++;
                        }
                        else
                            system("shutdown -s -t 0");
                    }
                }
        }


        timer += time;

        if (timer > 2500) 
        {
            if(buttonRed1.getFillColor() != sf::Color(0, 255, 0))
            {
                stick1.rotate(30);
            }
            if (buttonRed2.getFillColor() != sf::Color(0, 255, 0))
            {
                stick2.rotate(30);
            }
            if (buttonRed3.getFillColor() != sf::Color(0, 255, 0))
            {
                stick3.rotate(30);
            }
            if (buttonRed4.getFillColor() != sf::Color(0, 255, 0))
            {
                stick4.rotate(30);
            }
            if (buttonRed5.getFillColor() != sf::Color(0, 255, 0))
            {
                stick5.rotate(30);
            }
            timer = 0;
            buffer += 30;
            if (buffer == 360)
                buffer = 0;
        }

        if (fiveToWin == 5)
        {
            
            endText.setString("Well Done!");
            CreateStringToOutput(endText, font, 50, 600, 600);
            endText.setFillColor(sf::Color(0, 255, 0));
        }

        window.clear();
        

        window.draw(startText); // рисовашки!
        window.draw(buttonRed1);
        window.draw(stick1);
        window.draw(aText);
        window.draw(buttonRed2);
        window.draw(stick2);
        window.draw(bText);
        window.draw(buttonRed3);
        window.draw(stick3);
        window.draw(cText);
        window.draw(buttonRed4);
        window.draw(stick4);
        window.draw(dText);
        window.draw(buttonRed5);
        window.draw(stick5);
        window.draw(text0);
        window.draw(text90);
        window.draw(text180);
        window.draw(text270);
        window.draw(eText);
        window.draw(endText);


        window.display();
    }

    return 0;
}