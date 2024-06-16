#include "includes.h"

using namespace std;


void drawMainMenu(sf::RenderWindow& window, sf::Font& font, std::vector<Button>& buttons, sf::Sprite& backgroundSprite, sf::Sprite& foregroundSprite) {
    window.draw(backgroundSprite);
    window.draw(foregroundSprite);
    for (Button& button : buttons) {
        button.draw(window);
    }
}



void main()
{
    sf::VideoMode resolution = sf::VideoMode(1280, 720);

    sf::RenderWindow window(resolution, "MEGA ULTRA HYPE PINK DINO GAMEEEEEEEEEEEEEE", sf::Style::Titlebar | sf::Style::Close);
    
    RenderPointer current_render = Main_Menu;                                                                                         // START CONDITIONS

    Player player;
    Player ENEMY;
    Shop shop(player, window, current_render);
    FightProccess fight(player, ENEMY, window, current_render);

    player.DINO_load("DINO_INFO.txt");                                                                                                 // SAVED DATA

    sf::Sprite backgroundSprite(TextureLoader::getInstance().getTexture("GameData/Terrain/Plain.png"));
	sf::Sprite GameLogo(TextureLoader::getInstance().getTexture("GameData/Logo.png"));
    GameLogo.setPosition(140, 75);

    sf::Font sf_font;
    sf_font.loadFromFile("GameData/Arial.ttf");


    std::vector<Button> buttons;                                                                                                     // BUTTON CREATE
    sf::Texture t_button;
    t_button = TextureLoader::getInstance().getTexture("GameData/temp.png");
    buttons.emplace_back(850, 100, 300, 75, sf_font, "Battle", t_button);
    buttons.emplace_back(850, 250, 300, 75, sf_font, "Inventory", t_button);
    buttons.emplace_back(850, 400, 300, 75, sf_font, "Shop", t_button);
    buttons.emplace_back(850, 550, 300, 75, sf_font, "Quit", t_button);


    while (window.isOpen()) {
       
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {                                                                    // MOUSE INTERACTION
                    for (Button& button : buttons) {
                        if (button.isOverlapped(window)) {
                            if (button.text.getString() == "Inventory") {
                                current_render = Inventory;
                            }
                            else if (button.text.getString() == "Shop") {
                                current_render = Shop_Selector;
                            }
                            else if (button.text.getString() == "Battle") {
                                current_render = DINO_Selector;
                            }
                            else if (button.text.getString() == "Quit") {
                                
                                window.close();
                            }
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(backgroundSprite);
        if (current_render == Main_Menu) {                                                                                          // GAME STATE SYSTEM
			drawMainMenu(window, sf_font, buttons, backgroundSprite, GameLogo);
        }
        else if (current_render == DINO_Selector) {
            fight.dinosSelection();
        }
        else if (current_render == Inventory) {
            fight.Inventory();
        }
        else if (current_render == Shop_Selector) {
            shop.shopDialog();
        }
        else if (current_render == Simulation) {
            fight.FIGHT_PROCCESS();
            player.selectedDinos.clear();
            ENEMY.selectedDinos.clear();
            ENEMY.DINO_random_pull();
        }
        
        window.display();
    }
}