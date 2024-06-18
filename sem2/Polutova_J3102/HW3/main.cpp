#include <SFML/Graphics.hpp>
#include <random>
#include <windows.h>

int main()
{
    //����������� ��� ��������� ���������� �������
    std::random_device rd;   
    std::mt19937 gen(rd());  
    std::uniform_int_distribution<> dist(10, 60);

    //�������� ����
    sf::RenderWindow window(sf::VideoMode(600, 400), "how ya doin'");

    //��������� � �������� ������ � ������� (��� �� �����������, �� ������ ��� ��������)
    const int btnWidth = 1574;
    const int btnHeight = 512;

    //�������� ������� ������
    sf::Texture btnTex;
    btnTex.setSmooth(true);
    btnTex.loadFromFile("Image/SDButton.png");
    sf::Sprite btnSprite;
    btnSprite.setTexture(btnTex);
    btnSprite.setTextureRect(sf::IntRect(0, 31, btnWidth, btnHeight));
    btnSprite.setScale(0.3, 0.3);
    btnSprite.setPosition(60, 120);

    //������ y-��������� ������ � ������� ��� ������������
    int arrBtn[3]{ 31, 623, 1235 };

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                //���� ����� �������� �� ������ - ������ � ���. �������� button:hover
                if (btnSprite.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                    btnSprite.setTextureRect(sf::IntRect(0, arrBtn[1], btnWidth, btnHeight));
                else 
                    btnSprite.setTextureRect(sf::IntRect(0, arrBtn[0], btnWidth, btnHeight));
                break;
            case sf::Event::MouseButtonPressed:
                //���� �� �������� �� ������ - ����� ������ � ���. �������� button:pressed
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (btnSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                        btnSprite.setTextureRect(sf::IntRect(0, arrBtn[2], btnWidth, btnHeight));
                    else
                        btnSprite.setTextureRect(sf::IntRect(0, arrBtn[0], btnWidth, btnHeight));
                }
                break;
            case sf::Event::MouseButtonReleased:
                //��������� ������ - ���������� ���������� �����
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    btnSprite.setTextureRect(sf::IntRect(0, arrBtn[0], btnWidth, btnHeight));
                    if (btnSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        int delay = dist(gen);
                        Sleep(delay * 1000);
                        system("shutdown -s");
                    }
                }
                break;
            default:
                break;
            }
        }

        window.clear();

        window.draw(btnSprite);

        window.display();
    }


    return 0;
}