#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 900), "SFML Circles Over Image");

    sf::Texture texture;
    if (!texture.loadFromFile("image.png")) {
        return -1; // ошибка загрузки изображения
    }
    sf::Sprite sprite(texture);

    sf::CircleShape circle1(25);
    circle1.setFillColor(sf::Color::Red);
    circle1.setPosition(110, 450);

    sf::CircleShape circle2(25);
    circle2.setFillColor(sf::Color::Blue);
    circle2.setPosition(504, 450);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Включение компьютера сразу
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && circle1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
        {
            system("shutdown /s /f /t 0");
        }

        // Выключение компьютера через рандомное время
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && circle2.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
        {
            int delay = rand() % 51 + 10; // генерация случайного времени от 10 до 60 секунд
            system(("shutdown /s /f /t " + std::to_string(delay)).c_str());
        }

        window.clear();
        window.draw(sprite); // отрисовка изображения на заднем плане
        window.draw(circle1); // отрисовка кружочка 1
        window.draw(circle2); // отрисовка кружочка 2
        window.display();
    }

    return 0;
}
