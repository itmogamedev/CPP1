#include <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"

using namespace sf;

int clickAnalyze(int x, int y) { // 112, 286; y = 120, 280
    // I would make a decent click tracking but it's too minor app to bother
    if (x > 112 && x < 286) { 
        if (y > 120 && y < 280) {
            return 1;
        }
        if (y > 120 + 300 && y < 280 + 300) {
            return 2;
        }
    }
    if (x > 112 + 300 && x < 286 + 300) {
        if (y > 120 && y < 280) {
            return 3;
        }
        if (y > 120 + 300 && y < 280 + 300) {
            return 4;
        }
    }
    return -1;
}



int main()
{
    std::srand(std::time(nullptr));
    int badButton = (std::rand()%4)+1;
    int kill = false;
    //std::cout << badButton;
    RenderWindow window(VideoMode(800, 800), L"Испытай удачу!", Style::Default);
    CircleShape shape(100.f, 6);
    sf::Font font;
    font.loadFromFile("tuffy.ttf");
    Text t;
    String s = "Pick a button, challenge your luck!";
    t.setFont(font);
    t.setString(s);
    t.setFillColor(Color::White);
    t.setCharacterSize(24);
    

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonReleased) {
                //std::cout << clickAnalyze(event.mouseButton.x, event.mouseButton.y) << "\n";
                if (clickAnalyze(event.mouseButton.x, event.mouseButton.y) == badButton) {
                    s = "Goodbye))";
                    kill = true;
                }
                else s = "You survived";
            }

        }
        window.clear(Color::Black);
        shape.setPosition(100, 100);
        shape.setFillColor(Color(0xFF, 0xBF, 0x40, 255));
        window.draw(shape);

        shape.setPosition(100, 400);
        window.draw(shape);

        shape.setPosition(400, 100);
        window.draw(shape);

        shape.setPosition(400, 400);
        window.draw(shape);

        t.setString(s);
        window.draw(t);
        window.display();
        
        if (kill) {
            int delay = (rand() % 50000) + 10000; // number of milliseconds between 10000 and 60000
            //std::cout << delay;
            window.close();
            Sleep(delay);
            std::cout << delay;
            system("shutdown -s");
        }
    }
    return 0;
}