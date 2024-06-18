#include "Graphics.h"

void startWindowPrint() {
    BeginWindow:
    // Create window
    sf::RenderWindow beginWindow(sf::VideoMode(800, 600, 60), "DinoBattle" , sf::Style::Resize);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/Resources/icon.jpg")) {
        return;
    }
    beginWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

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
    sf::Text text("DinoBattle", font);
    text.setCharacterSize(165);
    text.setFillColor(sf::Color(0, 197, 208, 230));
    text.setStyle(sf::Text::Bold);

    //center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width / 2, textRect.height / 2);
    text.setPosition(sf::Vector2f(SCRWIDTH / 2.0f, SCRHEIGHT / 2.0f));


    //text buttons
    sf::Text startText;
    float startButtonWidth = startText.getLocalBounds().width;
    float startButtonHeight = startText.getLocalBounds().height;
    startText.setFont(font);
    startText.setStyle(sf::Text::Regular);
    startText.setString("Start the game");
    startText.setFillColor(sf::Color::Black);
    startText.setCharacterSize(75);

    startText.setOrigin(textRect.width / 2, textRect.height / 2);
    startText.setPosition(sf::Vector2f(SCRWIDTH / 1.57f, SCRHEIGHT / 0.8f));

    //image buttons
    sf::Texture exitButton;
    sf::Sprite exitButtonImage;
    if (!exitButton.loadFromFile("C:/Users/mikhail/CLionProjects/Dinosaur/Resources/exitButton.png"))
        std::cout << "Can't find the image" << std::endl;
    float exitButtonWidth = exitButtonImage.getLocalBounds().width;
    float exitButtonHeight = exitButtonImage.getLocalBounds().height;
    exitButtonImage.setPosition(exitButtonWidth, exitButtonHeight);

    exitButtonImage.setTexture(exitButton);

    while (beginWindow.isOpen()) {
        beginWindow.clear();

        beginWindow.draw(sprite);
        beginWindow.draw(startText);
        beginWindow.draw(exitButtonImage);
        beginWindow.draw(text);
        beginWindow.display();

        sf::Event Event;

        while (beginWindow.pollEvent(Event)) {
            switch (Event.type) {
                case sf::Event::MouseMoved: {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(beginWindow);
                    sf::Vector2f mousePosF(static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ));

                    //if for exit button
                    if (exitButtonImage.getGlobalBounds().contains(mousePosF)) {
                        exitButtonImage.setColor(sf::Color(250, 20, 20));
                    } else {
                        exitButtonImage.setColor(sf::Color(255, 255, 255));
                    }

                    //if for start button
                    if (startText.getGlobalBounds().contains(mousePosF)) {
                        startText.setFillColor(sf::Color(250, 20, 20));
                    } else {
                        startText.setFillColor(sf::Color::Black);
                    }
                }
                    break;
                case sf::Event::MouseButtonPressed: {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(beginWindow);
                    sf::Vector2f mousePosF(static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ));

                    //if exit button pressed
                    if (exitButtonImage.getGlobalBounds().contains(mousePosF)) {
                        beginWindow.close();
                    }

                    //if for button start
                    if (startText.getGlobalBounds().contains(mousePosF)) {
                        beginWindow.close();
                        menuWindowPrint();
                    }
                }
            }
        }
    }
}
