#include "menu.h"

void CP_Menu::Make_BG_Sprite(sf::RenderWindow& window, int x, int y)
{
	bg_image.loadFromFile(bg_path);
	bg_texture.loadFromImage(bg_image);
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setPosition(x, y);

    logo_image.loadFromFile(logo_path);
    logo_texture.loadFromImage(logo_image);
    logo_sprite.setTexture(logo_texture);
    logo_sprite.setPosition(640, 220);

    if (irilogo_texture.loadFromFile(irilogo_path)) {
        irilogo_sprite.setTexture(irilogo_texture);
        irilogo_sprite.setPosition(50, 970);
        irilogo_sprite.setScale({ 0.05, 0.05 });
    }

    if (lublogo_texture.loadFromFile(lublogo_path)) {
        lublogo_sprite.setTexture(lublogo_texture);
        lublogo_sprite.setPosition(250, 960);
        lublogo_sprite.setScale({ 0.05, 0.05 });
    }

    Set_Buttons();

	window.draw(bg_sprite);
    window.draw(logo_sprite);
    window.draw(irilogo_sprite);
    window.draw(lublogo_sprite);

    NewGame_Button.drawTo(window);
    LoadGame_Button.drawTo(window);
    Settings_Button.drawTo(window);
    Exit_Button.drawTo(window);
}

void CP_Menu::Button_Actions(sf::RenderWindow& window, sf::Event& event)
{
    sf::Clock clock;
    float time = clock.getElapsedTime().asMicroseconds();
    time /= 2000;
    clock.restart();
    Make_BG_Sprite(window, 0, 0);

    window.display();

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                Button_Overlap(NewGame_Button, window);
                Button_Overlap(LoadGame_Button, window);
                Button_Overlap(Settings_Button, window);
                Button_Overlap(Exit_Button, window);
                break;
            case sf::Event::MouseButtonPressed:
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                if (NewGame_Button.isMouseOver(mouse)) {
                    game.Button_Actions(window, event);
                    break;
                }
                if (LoadGame_Button.isMouseOver(mouse)) {
                    break;
                }
                if (Settings_Button.isMouseOver(mouse)) {
                    break;
                }
                if (Exit_Button.isMouseOver(mouse)) {
                    exit(true);
                }
            }
        }
    }
}

void CP_Menu::CP_SetMenuState()
{
    CP_GameState = GameState::Game;
}

void CP_Menu::Set_Buttons() {
	arial.loadFromFile("ArialRegular.ttf");

	NewGame_Button.setPosition({ 800, 450 }, {850, 460 });
	NewGame_Button.setFont(arial);

	LoadGame_Button.setPosition({ 800, 550 }, {850, 560 });
	LoadGame_Button.setFont(arial);

	Settings_Button.setPosition({ 800, 650 }, {850, 660 });
	Settings_Button.setFont(arial);

	Exit_Button.setPosition({ 800, 750 }, {850, 760 });
	Exit_Button.setFont(arial);

}

void CP_Menu::Button_Overlap(CP_Button& Button, sf::RenderWindow& window)
{
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    if (Button.isMouseOver(mouse)) {
        Button.setBackColor(sf::Color::White);
    }
    else {
        Button.setBackColor(sf::Color::Green);
    }
}
