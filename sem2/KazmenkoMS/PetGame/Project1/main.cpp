#include <SFML/Graphics.hpp>
#include "cat.h"
#include "info.h"
#include "iostream"
#include "chrono"
#define CenterOrigin(n)  n.setOrigin((n.getLocalBounds().left + n.getLocalBounds().width) / 2.f, (n.getLocalBounds().top + n.getLocalBounds().height) / 2.f);
// Задача: сделать игру тамагочи про котика.
// Его нужно кормить, поить, убирать.
// Он будет расти и расти пока не заполнит весь экран.

// TODO
// Кнопки [кормить, поить, мыть]
// центровать

// Управление
// Рисовать кнопки на экране:
// * Покормить
// * Помыть
// * Напоить



void updateCatPicture(const  sf::Texture& texture, sf::Sprite& sprite,
	std::chrono::time_point<std::chrono::steady_clock>& startTime) 
{
	sprite.setTexture(texture);
	startTime = std::chrono::high_resolution_clock::now();
}

void EndWindow(sf::RenderWindow& window,sf::Font& font,bool isWin)
{
	sf::Text text("", font, 50);
	if (isWin) text.setString("YOU WIN!!!");
	else text.setString("YOU LOSE!!!");
	text.setFillColor(sf::Color::Black);
	CenterOrigin(text);
	text.setPosition(window.getSize().x / 2.f, window.getSize().y / 5.f);
	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) 
			{
				if (event.key.code == sf::Keyboard::Escape) return;
			}
		}
		window.clear(sf::Color::White);
		window.draw(text);
		window.display();
	}
	
}
bool Pause(sf::RenderWindow& window, sf::Font& font)
{
	// button sprites
	sf::Texture continueButText;
	continueButText.loadFromFile("continue.png");
	sf::Texture menuButText;
	menuButText.loadFromFile("menu.png");
	
	sf::Sprite continueButSprite(continueButText);
	continueButSprite.setScale(1.5f, 1.5f);
	CenterOrigin(continueButSprite);
	continueButSprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 5.f);

	sf::Sprite menuButSprite(menuButText);
	menuButSprite.setScale(1.5f, 1.5f);
	CenterOrigin(menuButSprite);
	menuButSprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 4.f);
	//
	sf::Text text("PAUSE", font, 50);
	text.setFillColor(sf::Color::Black);
	CenterOrigin(text);
	text.setPosition(window.getSize().x / 2.f, window.getSize().y / 8.f);
	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) return true;
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					if (continueButSprite.getGlobalBounds().contains(mousePos))
					{
						return true;
					}
					if (menuButSprite.getGlobalBounds().contains(mousePos))
					{
						return false;
					}

				}
			}
		}
		window.clear(sf::Color::White);
		window.draw(text);
		window.draw(menuButSprite);
		window.draw(continueButSprite);
		window.display();
	}
}
void GamePlay(sf::RenderWindow& window,sf::Font font, Pet* pet)
{
	// icon sprites
	sf::Texture bowl;
	bowl.loadFromFile("bowl.png");
	sf::Texture bottle;
	bottle.loadFromFile("bottle.png");
	sf::Texture sponge;
	sponge.loadFromFile("sponge.png");
	sf::Sprite bowlSprite(bowl);
	bowlSprite.setScale(.3f, .3f);
	CenterOrigin(bowlSprite);
	bowlSprite.setPosition(window.getSize().x / 4.f * 1.65f, window.getSize().y / 6.f);

	sf::Sprite bottleSprite(bottle);
	bottleSprite.setScale(.2f, .2f);
	CenterOrigin(bottleSprite);
	bottleSprite.setPosition(window.getSize().x / 4.f * 2.05f, window.getSize().y / 6.f + 10);

	sf::Sprite spongeSprite(sponge);
	CenterOrigin(spongeSprite);
	spongeSprite.setScale(.2f, .2f);
	spongeSprite.setPosition(window.getSize().x / 4.f * 2.5f, window.getSize().y / 6.f + 10);
	//


	const sf::Texture* texture1 = pet->closemouthtext;
	const sf::Texture* texture2 = pet->openmouthtext;
	Info info(8,
		pet->getSize(), pet->getMaxSize(),
		pet->getFull(), pet->getMaxFull(),
		pet->getHydr(), pet->getMaxHydr(),
		pet->getClean(), pet->getMaxClean());

	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setString(info.getStr());
	text.setCharacterSize(35); // in pixels, not points!
	CenterOrigin(text);
	text.setPosition(window.getSize().x / 2.f, window.getSize().y / 10.f);

	std::chrono::time_point<std::chrono::steady_clock> startTime
		= std::chrono::high_resolution_clock::now();
	sf::Event event;
	while (window.isOpen())
	{
		if (pet->isDead()) // TODO Окно поражения 
		{
			EndWindow(window, font, false);
			return;
		}
		if (pet->isSuccess())
		{
			EndWindow(window, font, true);
			return;
		}
		pet->live();
		pet->sprite->setScale(sf::Vector2f(float(pet->getSize()) / pet->getMaxSize(),
			float(pet->getSize()) / pet->getMaxSize()));

		while (window.pollEvent(event))
		{

			std::chrono::duration<float> duration =
				std::chrono::high_resolution_clock::now() - startTime;
			if (duration.count() > 0.01)
			{
				pet->sprite->setTexture(*texture1);
			}

			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				// Получаем нажатую клавишу - выполняем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape)
				{
					if (!Pause(window, font)) return;
				}
				
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					if (bowlSprite.getGlobalBounds().contains(mousePos))
					{
						pet->increaseFull(50);
						updateCatPicture(*texture2, *pet->sprite, startTime);
					}
					if (bottleSprite.getGlobalBounds().contains(mousePos))
					{
						pet->increaseHydr(50);
						updateCatPicture(*texture2, *pet->sprite, startTime);
					}
					if (spongeSprite.getGlobalBounds().contains(mousePos))
					{
						pet->increaseClean(50);
						updateCatPicture(*texture2, *pet->sprite, startTime);
					}

				}
			}
		}

		Info info(8,
			pet->getSize(), pet->getMaxSize(),
			pet->getFull(), pet->getMaxFull(),
			pet->getHydr(), pet->getMaxHydr(),
			pet->getClean(), pet->getMaxClean());
		text.setString(info.getStr());

		// Выполняем необходимые действия по отрисовке
		window.clear(sf::Color::White);
		window.draw(*pet->sprite);
		window.draw(text);
		window.draw(bowlSprite);
		window.draw(bottleSprite);
		window.draw(spongeSprite);
		window.display();
	}
}
int main() 
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Full da Cat");
	window.setFramerateLimit(60);

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		return 3;
	}

	sf::Texture catClosedTexture;
	sf::Texture catOpenTexture;
	sf::Texture chinchillaClosedTexture;
	sf::Texture chinchillaOpenTexture;
	sf::Texture leftArrowTexture;
	sf::Texture rightArrowTexture;
	sf::Texture dogeClosedTexture;
	sf::Texture dogeOpenTexture;
	if (!catClosedTexture.loadFromFile("cat1.png") or !catOpenTexture.loadFromFile("cat2.png") or
		!chinchillaClosedTexture.loadFromFile("chinchilla1.png") or !chinchillaOpenTexture.loadFromFile("chinchilla2.png") or 
		!leftArrowTexture.loadFromFile("left.png") or !rightArrowTexture.loadFromFile("right.png") or
		!dogeClosedTexture.loadFromFile("doge1.png") or !dogeOpenTexture.loadFromFile("doge2.png")
		)
	{
		return 3;
	}
	// arrows
	sf::Sprite leftArr(leftArrowTexture);
	leftArr.setScale(.1f, .1f);
	CenterOrigin(leftArr);
	leftArr.setPosition(window.getSize().x / 4.f, window.getSize().y / 5.f * 4);
	sf::Sprite rightArr(rightArrowTexture);
	rightArr.setPosition(window.getSize().x / 4.f*3, window.getSize().y / 5.f * 4);
	rightArr.setScale(.1f, .1f);
	CenterOrigin(rightArr);

	// cat
	sf::Sprite catSprite;
	catSprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
	// chinchilla
	sf::Sprite chinchillaSprite;
	chinchillaSprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
	// doge
	sf::Sprite dogeSprite;
	dogeSprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
	while (true)
	{
		int curpet = 0;
		bool isGameEnded = false;

		catSprite.setScale(sf::Vector2f(.5f, .5f));
		catSprite.setTexture(catClosedTexture);
		CenterOrigin(catSprite);


		chinchillaSprite.setScale(sf::Vector2f(.5f, .5f));
		chinchillaSprite.setTexture(chinchillaClosedTexture);
		CenterOrigin(chinchillaSprite);

		dogeSprite.setScale(sf::Vector2f(.5f, .5f));
		dogeSprite.setTexture(dogeClosedTexture);
		CenterOrigin(dogeSprite);

		// Game logic
		Pet* cat = new Pet(3, 100, 1000, 1000, &catSprite, &catOpenTexture, &catClosedTexture);
		Pet* chinchilla = new Pet(3, 100, 1000, 1000, &chinchillaSprite, &chinchillaOpenTexture, &chinchillaClosedTexture);
		Pet* doge = new Pet(3, 100, 1000, 1000, &dogeSprite, &dogeOpenTexture, &dogeClosedTexture);
		std::vector<Pet*>pets = { cat,chinchilla,doge };
		// menu text
		sf::Text menutext("MENU", font, 50);
		CenterOrigin(menutext);
		menutext.setFillColor(sf::Color::Black);
		menutext.setPosition(window.getSize().x / 2.f, window.getSize().y / 7.f);

		sf::Event event;
		while (window.isOpen())
		{
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) window.close();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					GamePlay(window, font, pets[curpet]);
					isGameEnded = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					if (curpet > 0)
						curpet--;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					if (curpet < pets.size() - 1)
						curpet++;
				}
			}
			if (isGameEnded) break;
			window.clear(sf::Color::White);
			window.draw(menutext);
			window.draw(leftArr);
			window.draw(rightArr);
			window.draw(*pets[curpet]->sprite);
			window.display();
		}

		if (!window.isOpen()) return 0;
	}
	return 0;
}