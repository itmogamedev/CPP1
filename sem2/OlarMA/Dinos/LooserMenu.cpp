#include "includes.h"
#include "Graphics.h"
#include "DatabaseFunc.h"

void looserWindowPrint() {
    // Create window
    sf::RenderWindow looserWindow(sf::VideoMode(800, 600, 60), "DinoBattle", sf::Style::Resize);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/Resources/icon.jpg")) {
        return;
    }
    looserWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/Resources/background.jpg")) {
        return;
    }
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    //font
    sf::Font font;
    if (!font.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/Resources/blackberry.otf")) {
        return;
    }
    //
    sf::Text text("RIP DINO'S", font);
    text.setCharacterSize(165);
    text.setFillColor(sf::Color(0, 197, 208, 230));
    text.setStyle(sf::Text::Bold);

    //center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width / 2, textRect.height / 2);
    text.setPosition(sf::Vector2f(SCRWIDTH / 2.0f, SCRHEIGHT / 2.0f - 70));


    //text buttons
    sf::Text startText;
    float startButtonWidth = startText.getLocalBounds().width;
    float startButtonHeight = startText.getLocalBounds().height;
    startText.setFont(font);
    startText.setStyle(sf::Text::Regular);
    startText.setString("sry babe, you're loser...(");
    startText.setFillColor(sf::Color::Black);
    startText.setCharacterSize(75);
    startText.setPosition(75, 300);


    //image buttons
    sf::Texture exitButton;
    sf::Sprite exitButtonImage;
    if (!exitButton.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/Resources/exitButton.png"))
        std::cout << "Can't find the image" << std::endl;
    float exitButtonWidth = exitButtonImage.getLocalBounds().width;
    float exitButtonHeight = exitButtonImage.getLocalBounds().height;
    exitButtonImage.setPosition(exitButtonWidth, exitButtonHeight);

    exitButtonImage.setTexture(exitButton);

    //grave 1
    sf::Texture grave1;
    sf::Sprite grave1Sprite;
    if (!grave1.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/Resources/grave2.png"))
        std::cout << "Can't find the image" << std::endl;

    grave1Sprite.setPosition(150, 400);
    grave1Sprite.setScale(3, 3);
    grave1Sprite.setTexture(grave1);

    //grave2
    sf::Texture grave2;
    sf::Sprite grave2Sprite;
    if (!grave2.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/Resources/grave2.png"))
        std::cout << "Can't find the image" << std::endl;
    grave2Sprite.setPosition(350, 470);
    grave2Sprite.setScale(3, 3);
    grave2Sprite.setTexture(grave2);

    //grave 3
    sf::Texture grave3;
    sf::Sprite grave3Sprite;
    if (!grave3.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/Resources/grave2.png"))
        std::cout << "Can't find the image" << std::endl;
    grave3Sprite.setPosition(550, 400);
    grave3Sprite.setScale(3, 3);
    grave3Sprite.setTexture(grave3);

    while (looserWindow.isOpen()) {
        looserWindow.clear();

        looserWindow.draw(sprite);
        looserWindow.draw(startText);
        looserWindow.draw(exitButtonImage);
        looserWindow.draw(grave1Sprite);
        looserWindow.draw(grave2Sprite);
        looserWindow.draw(grave3Sprite);
        looserWindow.draw(text);
        looserWindow.display();

        sf::Event Event;

        while (looserWindow.pollEvent(Event)) {
            switch (Event.type) {
                case sf::Event::MouseMoved: {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(looserWindow);
                    sf::Vector2f mousePosF(static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ));

                    //if for exit button
                    if (exitButtonImage.getGlobalBounds().contains(mousePosF)) {
                        exitButtonImage.setColor(sf::Color(250, 20, 20));
                    } else {
                        exitButtonImage.setColor(sf::Color(255, 255, 255));
                    }
                }
                    break;
                case sf::Event::MouseButtonPressed: {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(looserWindow);
                    sf::Vector2f mousePosF(static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ));

                    //if exit button pressed
                    if (exitButtonImage.getGlobalBounds().contains(mousePosF)) {
                        looserWindow.close();
                        menuWindowPrint();
                    }
                }
                    break;
            }
        }
    }
}

