#include <iostream>
#include <SFML/Graphics.hpp> 
#include "windows.h"
#include <fstream>
#include <string>
#include <cmath>
#include "Dino.h"
using namespace sf; //убрать

int money = 0;
int scene = 0;
bool flag_click;
int first_dino = -1, second_dino = -1, third_dino = -1; //переменные для запоминания номеров динозавров, которые будут участвовать в бою.
int place;
int terrain; //переменная для выбора характеристики и удваивания урона
int temp_player = 0, temp_enemy = 0;
int characteristic_player, characteristic_enemy;
int player_animation = 0, enemy_animation = 0;

std::string first_dino_pic0, second_dino_pic0, third_dino_pic0; //картинки динозавров, которые участвую в бою
std::string first_dino_pic1, second_dino_pic1, third_dino_pic1; 
std::string first_dino_pic2, second_dino_pic2, third_dino_pic2; 

std::unique_ptr<Dinozaur> dinozaur;
std::unique_ptr<Dinozaur> player;
std::unique_ptr<Dinozaur> enemy;

sf::RenderWindow window(sf::VideoMode(1950, 1000), "Dinozaur Battle", /*sf::Style::Close*/sf::Style::Fullscreen);  // Создаём объект окна с кнопкой закрытия

sf::RectangleShape button_menu(sf::Vector2f(600, 150)); // Объект кнопки меню (размер кнопки)
sf::RectangleShape button_shop(sf::Vector2f(200, 100)); // Объект кнопки в магазине купить

sf::RectangleShape click_rect(sf::Vector2f(1, 1)); // прямоугольник, который перемещается на место клика

sf::RectangleShape pull(sf::Vector2f(500, 280)); // Объект кнопки меню (размер кнопки)

sf::Font font; // Объект, хранящий в себе шрифт
sf::Text text_menu; // Текст для кнопок
sf::Text text_inventory; // Текст для инвентаря

sf::Texture texture;
sf::Texture texture_death;
sf::Sprite sprite;
sf::Sprite sprite_death;

void Start() {
	font.loadFromFile("arkhip.ttf"); // Считываем шрифт из arkhip.ttf файла

	text_menu.setFont(font); // Передаём шрифт в текст
	text_menu.setFillColor(sf::Color(64, 64, 64)); // Окрашиваем в тёмно-серый цвет 
	text_menu.setCharacterSize(38); // Размер текста на экране в пиксели

	text_inventory.setFont(font); // Передаём шрифт в текст
	text_inventory.setFillColor(sf::Color(255, 165, 0)); // Окрашиваем цвет текста в оранжевый
	text_inventory.setCharacterSize(40); // Размер текста на экране в пиксели

	button_menu.setOutlineThickness(3); //толщина кнопок в меню
	button_menu.setOutlineColor(sf::Color::Black);

	button_shop.setOutlineThickness(3); //толщина кнопок в меню
	button_shop.setOutlineColor(sf::Color::Black);

	pull.setOutlineThickness(3); //толщина кнопок в меню
	pull.setOutlineColor(sf::Color::Black);
}

void Render_hello_screen() { //сцена 0
	window.clear(sf::Color::White);

	button_menu.setPosition(675, 140 + 200);
	window.draw(button_menu);
	button_menu.setPosition(675, 140 + 400);
	window.draw(button_menu);

	text_menu.setString(L"Начать новую игру");
	text_menu.setPosition(985 - text_menu.getGlobalBounds().width / 2, 190 + 200);
	window.draw(text_menu);
	text_menu.setString(L"Продолжить");
	text_menu.setPosition(985 - text_menu.getGlobalBounds().width / 2, 190 + 400);
	window.draw(text_menu);

	window.display();
}


void Render_menu() { //сцена 1
	window.clear(sf::Color::White); // Очищаем окна на белый цвет

	text_menu.setString(L"Чтобы вернуться на этот экран нажмите esc");
	text_menu.setPosition(20 , 30);
	window.draw(text_menu);

	button_menu.setPosition(675, 140);
	window.draw(button_menu);
	button_menu.setPosition(675, 140 + 200);
	window.draw(button_menu);
	button_menu.setPosition(675, 140 + 400);
	window.draw(button_menu);
	button_menu.setPosition(675, 140 + 600);
	window.draw(button_menu);

	text_menu.setString(L"Начать бой");
	text_menu.setPosition(985 - text_menu.getGlobalBounds().width / 2, 190);
	window.draw(text_menu);
	text_menu.setString(L"Инвентарь");
	text_menu.setPosition(985 - text_menu.getGlobalBounds().width / 2, 190 + 200);
	window.draw(text_menu);
	text_menu.setString(L"Магазин");
	text_menu.setPosition(985 - text_menu.getGlobalBounds().width / 2, 190 + 400);
	window.draw(text_menu);
	text_menu.setString(L"Выход из игры");
	text_menu.setPosition(985 - text_menu.getGlobalBounds().width / 2, 190 + 600);
	window.draw(text_menu);

	window.display();
}
void Render_choice_pull() { //сцена 2
	window.clear(sf::Color::White);
	pull.setPosition(100, 110);
	window.draw(pull);
	pull.setPosition(100, 420);
	window.draw(pull);
	pull.setPosition(100, 730);
	window.draw(pull);

	pull.setPosition(700, 200);
	window.draw(pull);
	pull.setPosition(1300, 200);
	window.draw(pull);
	pull.setPosition(700, 600);
	window.draw(pull);
	pull.setPosition(1300, 600);
	window.draw(pull);

	text_menu.setString(L"Соберите свою команду из 3-х динозавров");
	text_menu.setPosition(985 - text_menu.getGlobalBounds().width / 2, 50);
	window.draw(text_menu);
	text_menu.setString(L"1. Тиранозавр");
	text_menu.setPosition(950 - text_menu.getGlobalBounds().width / 2, 140);
	window.draw(text_menu);
	text_menu.setString(L"2. Трицератопс");
	text_menu.setPosition(1550 - text_menu.getGlobalBounds().width / 2, 140);
	window.draw(text_menu);
	text_menu.setString(L"3. Брахиозавр");
	text_menu.setPosition(950 - text_menu.getGlobalBounds().width / 2, 540);
	window.draw(text_menu);
	text_menu.setString(L"2. Птерозавр");
	text_menu.setPosition(1550 - text_menu.getGlobalBounds().width / 2, 540);
	window.draw(text_menu);

	//Сначала загружаем все картинки серыми
	texture.loadFromFile("animation/1e.png");
	sprite.setTexture(texture);
	sprite.setScale(1.f, 1.f);
	sprite.setPosition(700, 200);
	window.draw(sprite);

	texture.loadFromFile("animation/2e.png");
	sprite.setTexture(texture);
	sprite.setScale(1.f, 1.f);
	sprite.setPosition(1300, 200);
	window.draw(sprite);

	texture.loadFromFile("animation/3e.png");
	sprite.setTexture(texture);
	sprite.setScale(1.f, 1.f);
	sprite.setPosition(700, 600);
	window.draw(sprite);

	texture.loadFromFile("animation/4e.png");
	sprite.setTexture(texture);
	sprite.setScale(1.f, 1.f);
	sprite.setPosition(1300, 600);
	window.draw(sprite);

	//Если номер дино есть в инвентаре, то выгружаем светлую картинку вместо темной
	int dino_num;
	std::string line = "";
	std::ifstream in("dinonum.txt");//Выводим картинку темную/светлую в зависимости от наличия дино в инвентаре
	while (in >> dino_num) { //читаем номер дино из файла
		switch (dino_num) {
		case 0:
			texture.loadFromFile("animation/1w.png");
			sprite.setTexture(texture);
			sprite.setPosition(700, 200);
			window.draw(sprite);
			break;
		case 1:
			texture.loadFromFile("animation/2w.png");
			sprite.setTexture(texture);
			sprite.setPosition(1300, 200);
			window.draw(sprite);
			break;
		case 2:
			texture.loadFromFile("animation/3w.png");
			sprite.setTexture(texture);
			sprite.setPosition(700, 600);
			window.draw(sprite);
			break;
		case 3:
			texture.loadFromFile("animation/4w.png");
			sprite.setTexture(texture);
			sprite.setPosition(1300, 600);
			window.draw(sprite);
			break;
		}
	}
	if (scene == 1) //делаем только при 1-м вызове Render_choice_pull
		window.display();
	scene = 2;
}

void Inventory() { //сцена 6 читаем из инвентаря 
	int dino_num;
	std::string line = "";
	std::ifstream in("dinonum.txt");
	while (in >> dino_num) { //читаем номер дино из файла
		switch (dino_num) {
		case 0:
			dinozaur = std::make_unique<Tiranozavr>();
			break;
		case 1:
			dinozaur = std::make_unique<Triceratops>();
			break;
		case 2:
			dinozaur = std::make_unique<Braxiozavr>();
			break;
		case 3:
			dinozaur = std::make_unique<Pterozavr>();
			break;
		}
		line += dinozaur->get_name() + " {Power - " + std::to_string(dinozaur->get_power()) + ", Dexterity - " 
			+ std::to_string(dinozaur->get_dexterity()) + ", Intellect - " + std::to_string(dinozaur->get_intellect()) + "}\n";
	}
	text_inventory.setString(L"                                                               \
    Ваш инвентарь:\n\nНакоплено - " + std::to_string(money) + L" монет \n\nДинозавры: \n" + line);
	text_inventory.setPosition(30, 60);
	window.clear(sf::Color::White);
	window.draw(text_inventory);
	window.display();
}
void Render_shop() {
	window.clear(sf::Color::White);

	button_menu.setPosition(675, 140);
	window.draw(button_menu);
	button_menu.setPosition(675, 140 + 200);
	window.draw(button_menu);
	button_menu.setPosition(675, 140 + 400);
	window.draw(button_menu);
	button_menu.setPosition(675, 140 + 600);
	window.draw(button_menu);

	text_menu.setString(L"Тиранозавр");
	text_menu.setPosition(985 - text_menu.getGlobalBounds().width / 2, 190);
	window.draw(text_menu);
	text_menu.setString(L"Трицератопс");
	text_menu.setPosition(985 - text_menu.getGlobalBounds().width / 2, 190 + 200);
	window.draw(text_menu);
	text_menu.setString(L"Брахиозавр");
	text_menu.setPosition(985 - text_menu.getGlobalBounds().width / 2, 190 + 400);
	window.draw(text_menu);
	text_menu.setString(L"Птерозавр");
	text_menu.setPosition(985 - text_menu.getGlobalBounds().width / 2, 190 + 600);
	window.draw(text_menu);

	window.display();
}

void render_button_buy() {
	button_shop.setPosition(900, 250);
	window.draw(button_shop);

	text_menu.setString(L"Купить");
	text_menu.setPosition(1000 - text_menu.getGlobalBounds().width / 2, 275);
	window.draw(text_menu);

	window.display();
}

void Pressed_hello_screen() {
	if (flag_click)
		for (int i = 1; i < 3; i++) {
			button_menu.setPosition(675, 140 + i * 200);
			if (button_menu.getGlobalBounds().intersects(click_rect.getGlobalBounds())) { // Условие пересечения
				flag_click = false;
				scene = 1;
				Render_menu();
				switch (i) {
				case 1: {//начать новую игру
					std::ofstream mon("деньги.txt");
					mon << money; //обнуляем деньги
					mon.close();

					std::ofstream out; // записать номер дино в инвентарь
					out.open("dinonum.txt"); // добавление в конец нового дино
					if (out.is_open()) {
						out << 0 << " " << 1 << " " << 2 << " ";
						out.close();
					}
				}
				case 2: { //продолжить
					std::ifstream mon("деньги.txt");//перед началом считываем кол-во монет
					mon >> money;
					mon.close();
				}
				};
			}
		}
}
void MouseButtonPressed_menu() {
	if (flag_click)
		for (int i = 0; i < 4; i++) {
			button_menu.setPosition(675, 140 + i * 200);
			if (button_menu.getGlobalBounds().intersects(click_rect.getGlobalBounds())) { // Условие пересечения
				flag_click = false;
				switch (i) {
				case 0:
					Render_choice_pull();
					break;
				case 1:
					scene = 6; //инвентарь
					Inventory();
					break;
				case 2:
					scene = 3; //магазин
					Render_shop();
					break;
				case 3:
					window.close();
					break;
				};
			}
		}
}
void press_button_shop() { //когда нажали на динозавра в магазине
	if (flag_click)
		for (int j = 0; j < 4; j++) {
			button_menu.setPosition(675, 140 + j * 200);
			if (button_menu.getGlobalBounds().intersects(click_rect.getGlobalBounds())) { // Условие пересечения
				scene = 4;
				flag_click = false;
				window.clear(sf::Color::White);
				switch (j) {
				case 0: 
					dinozaur = std::make_unique<Tiranozavr>();
					texture.loadFromFile("animation/1.0.png");
					break;
				case 1:
					dinozaur = std::make_unique<Triceratops>();
					texture.loadFromFile("animation/2.0.png");
					break;
				case 2: 
					dinozaur = std::make_unique<Braxiozavr>();
					texture.loadFromFile("animation/3.0.png");
					break;
				case 3: 				
					dinozaur = std::make_unique<Pterozavr>();
					texture.loadFromFile("animation/4.0.png");
					break;
				};
				sprite.setTexture(texture);
				sprite.setPosition(0, 130);
				sprite.setScale(4.f, 4.f);
				window.draw(sprite);

				text_inventory.setString(L"Накопленные монеты: " + std::to_string(money) + L"\nСтоимость " + dinozaur->get_name() + " - " + 
					std::to_string(dinozaur->get_cost()) + L"\nСила - " + std::to_string(dinozaur->get_power()) +
					L", Ловкость - " + std::to_string(dinozaur->get_dexterity()) + L", Интеллект - " + std::to_string(dinozaur->get_intellect()) +
					L"\nМестность, на которой урон динозавра удваивается - " + dinozaur->get_terrain());
				text_inventory.setPosition(15, 20);
				window.draw(text_inventory);
				render_button_buy();
			}
		}
}

void buy_dino() { //вызывается на 4 сцене (проверка на нажатие кнопки купить)
	if (flag_click) {
		button_shop.setPosition(900, 250);
		if (button_shop.getGlobalBounds().intersects(click_rect.getGlobalBounds())) { // Условие пересечения места клика с кнопкой
			flag_click = false;
			if (money >= dinozaur->get_cost()) {//проверка на то, достаточно ли денег
				money -= dinozaur->get_cost();

				std::ofstream mon("деньги.txt");//записать новое значение money в инвентарь
				mon << money;
				mon.close();

				std::ofstream out; // записать номер дино в инвентарь
				out.open("dinonum.txt", std::ios::app); // добавление в конец нового дино
				if (out.is_open()) {
					switch (dinozaur->get_num()) {
					case 0:
						out << 0 << " "; break;
					case 1:
						out << 1 << " "; break;
					case 2:
						out << 2 << " "; break;
					case 3:
						out << 3 << " "; break;
					}
					out.close();
				}
				scene = 3;
				Render_shop();
			}
			else { //если денег недостаточно
				scene = 5;
				window.clear(sf::Color::White); // Очищаем окна на белый цвет
				text_menu.setString(L"Ошибка. Недостаточно денег");
				text_menu.setPosition(1000 - text_menu.getGlobalBounds().width / 2, 370);
				window.draw(text_menu);
				window.display();
			}
		}
	}
}
int findValue(const std::vector<int>& data, int value) {
	auto result{ std::find(begin(data), end(data), value) };
	if (result == end(data))
		return false;
	else
		return true;
}

void Pressed_pull() { //функция, которая собирает пул (отслеживает нажатия и проверяет на правильность выбора)
	if (flag_click)
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				pull.setPosition(700 + i * 600, 200 + j * 400);
				if (pull.getGlobalBounds().intersects(click_rect.getGlobalBounds())) { // Условие пересечения
					flag_click = false;
					int dino_num;
					std::vector<int> dino;
					std::ifstream in("dinonum.txt");
					while (in >> dino_num) {
						dino.push_back(dino_num);
					}
					if (i == 0 && j == 0 && findValue(dino, 0) == true) { //Проверка на наличие в инвентаре цифры 0.
						auto it = std::find(dino.begin(), dino.end(), 0);
						dino.erase(it);
						std::ofstream out("dinonum.txt");//Перезаписываем инвентарь
						std::ostream_iterator<int> output_iterator(out, " ");
						std::copy(std::begin(dino), std::end(dino), output_iterator);

						if (first_dino == -1) {
							first_dino_pic0 = "animation/1.0r.png";
							first_dino_pic1 = "animation/1.1r.png";
							first_dino_pic2 = "animation/1.2r.png";
							first_dino = 0;
						}
						else if (second_dino == -1) {
							second_dino_pic0 = "animation/1.0r.png";
							second_dino_pic1 = "animation/1.1r.png";
							second_dino_pic2 = "animation/1.2r.png";
							second_dino = 0;
						}
						else {
							third_dino_pic0 = "animation/1.0r.png";
							third_dino_pic1 = "animation/1.1r.png";
							third_dino_pic2 = "animation/1.2r.png";
							third_dino = 0;
						}
					}
					else if (i == 1 && j == 0 && findValue(dino, 1) == true) {
						auto it = std::find(dino.begin(), dino.end(), 1);
						dino.erase(it);
						std::ofstream out("dinonum.txt");//Перезаписываем инвентарь
						std::ostream_iterator<int> output_iterator(out, " ");
						std::copy(std::begin(dino), std::end(dino), output_iterator);
						if (first_dino == -1) {
							first_dino_pic0 = "animation/2.0r.png";
							first_dino_pic1 = "animation/2.1r.png";
							first_dino_pic2 = "animation/2.2r.png";
							first_dino = 1;
						}
						else if (second_dino == -1) {
							second_dino_pic0 = "animation/2.0r.png";
							second_dino_pic1 = "animation/2.1r.png";
							second_dino_pic2 = "animation/2.2r.png";
							second_dino = 1;
						}
						else {
							third_dino_pic0 = "animation/2.0r.png";
							third_dino_pic1 = "animation/2.1r.png";
							third_dino_pic2 = "animation/2.2r.png";
							third_dino = 1;
						}
					}
					else if (i == 0 && j == 1 && findValue(dino, 2) == true) {
						auto it = std::find(dino.begin(), dino.end(), 2);
						dino.erase(it);
						std::ofstream out("dinonum.txt");//Перезаписываем инвентарь
						std::ostream_iterator<int> output_iterator(out, " ");
						std::copy(std::begin(dino), std::end(dino), output_iterator);
						if (first_dino == -1) {
							first_dino_pic0 = "animation/3.0r.png";
							first_dino_pic1 = "animation/3.1r.png";
							first_dino_pic2 = "animation/3.2r.png";
							first_dino = 2;
						}
						else if (second_dino == -1) {
							second_dino_pic0 = "animation/3.0r.png";
							second_dino_pic1 = "animation/3.1r.png";
							second_dino_pic2 = "animation/3.2r.png";
							second_dino = 2;
						}
						else {
							third_dino_pic0 = "animation/3.0r.png";
							third_dino_pic1 = "animation/3.1r.png";
							third_dino_pic2 = "animation/3.2r.png";
							third_dino = 2;
						}
					}
					else if (i == 1 && j == 1 && findValue(dino, 3) == true) {
						auto it = std::find(dino.begin(), dino.end(), 3);
						dino.erase(it);
						std::ofstream out("dinonum.txt");//Перезаписываем инвентарь
						std::ostream_iterator<int> output_iterator(out, " ");
						std::copy(std::begin(dino), std::end(dino), output_iterator);
						if (first_dino == -1) {
							first_dino_pic0 = "animation/4.0r.png";
							first_dino_pic1 = "animation/4.1r.png";
							first_dino_pic2 = "animation/4.2r.png";
							first_dino = 3;
						}
						else if (second_dino == -1) {
							second_dino_pic0 = "animation/4.0r.png";
							second_dino_pic1 = "animation/4.1r.png";
							second_dino_pic2 = "animation/4.2r.png";
							second_dino = 3;
						}
						else {
							third_dino_pic0 = "animation/4.0r.png";
							third_dino_pic1 = "animation/4.1r.png";
							third_dino_pic2 = "animation/4.2r.png";
							third_dino = 3;
						}
					}
					Render_choice_pull();
					if (third_dino != -1)
						window.clear(sf::Color::White);
					if (first_dino != -1) {
						texture.loadFromFile(first_dino_pic0);
						sprite.setPosition(100, 110);
						sprite.setTexture(texture);
						window.draw(sprite);
					}
					if (second_dino != -1) {
						texture.loadFromFile(second_dino_pic0);
						sprite.setPosition(100, 420);
						sprite.setTexture(texture);
						window.draw(sprite);
					}
					if (third_dino != -1) {
						texture.loadFromFile(third_dino_pic0);
						sprite.setPosition(100, 730);
						sprite.setTexture(texture);
						window.draw(sprite);
						//когда пулл заполнен

						button_menu.setPosition(900, 470);
						window.draw(button_menu);
						text_inventory.setString(L"ИГРАТЬ"); //сделать кнопку и начать бой
						text_inventory.setPosition(1200 - text_inventory.getGlobalBounds().width / 2, 520);
						window.draw(text_inventory);

						std::ofstream outp;
						outp.open("dinonum.txt", std::ios::app); //Перезаписываем инвентарь
						int i = 3;
						int j;
						while (i > 0) {
							if (i == 3) j = first_dino;
							if (i == 2) j = second_dino;
							if (i == 1) j = third_dino;
							switch (j) {
							case 0:
								outp << 0 << " "; break;
							case 1:
								outp << 1 << " "; break;
							case 2:
								outp << 2 << " "; break;
							case 3:
								outp << 3 << " "; break;
							}
							i--;
						}
						scene = 7;
					}
					window.display();
				}
			}
		}
}
void createRandomEnemy() {
	int choice = rand()% 4;
	switch (choice) {
	case 0:
		enemy = std::make_unique<Tiranozavr>(); break;
	case 1:
		enemy = std::make_unique<Triceratops>(); break;
	case 2:
		enemy = std::make_unique<Braxiozavr>(); break;
	case 3:
		enemy = std::make_unique<Pterozavr>(); break;
	}
}
void createDino() {
	int number_dino;
	if (temp_player == 0)
	number_dino = first_dino;
	else if (temp_player == 1)
		number_dino = second_dino;
	else if (temp_player == 2)
		number_dino = third_dino;
	switch (number_dino) {
	case 0:
		player = std::make_unique<Tiranozavr>(); break;
	case 1:
		player = std::make_unique<Triceratops>(); break;
	case 2:
		player = std::make_unique<Braxiozavr>(); break;
	case 3:
		player = std::make_unique<Pterozavr>(); break;
	};
}

void place_choice() {
	switch (place) {
	case 0:
		terrain = 0; //Игроки сражаются силой
		text_menu.setString(L"Местность - Равнина. Игроки сражаются силой");
		text_menu.setPosition(1000 - text_menu.getGlobalBounds().width / 2, 70);
		window.draw(text_menu);
		break;
	case 1:
		terrain = 1; //Игроки сражаются ловкостью
		text_menu.setString(L"Местность - Гора. Игроки сражаются ловкостью");
		text_menu.setPosition(1000 - text_menu.getGlobalBounds().width / 2, 70);
		window.draw(text_menu);
		break;
	case 2:
		terrain = 2; //Игроки сражаются интеллектом
		text_menu.setString(L"Местность - Река. Игроки сражаются интеллектом");
		text_menu.setPosition(1000 - text_menu.getGlobalBounds().width / 2, 70);
		window.draw(text_menu);
		break;
	}
}
void double_strength() {
	if (terrain == player->get_dino_terrain()) {
		characteristic_player *= 2;
		text_menu.setString(L"Урон игрока увеличился вдвое!");
		text_menu.setPosition(600 - text_menu.getGlobalBounds().width / 2, 920);
		window.draw(text_menu);
	}
	if (terrain == enemy->get_dino_terrain()) {
		characteristic_enemy *= 2;
		text_menu.setString(L"Урон врага увеличился вдвое!");
		text_menu.setPosition(1400 - text_menu.getGlobalBounds().width / 2, 920);
		window.draw(text_menu);
	}
}
void Print_player() {
	if (temp_player == 0) {
		if (player_animation == 0)
			texture.loadFromFile(first_dino_pic0);
		else if (player_animation == 1)
			texture.loadFromFile(first_dino_pic1);
		else 
			texture.loadFromFile(first_dino_pic2);
	}
	else if (temp_player == 1)
		if (player_animation == 0)
			texture.loadFromFile(second_dino_pic0);
		else if (player_animation == 1)
			texture.loadFromFile(second_dino_pic1);
		else
			texture.loadFromFile(second_dino_pic2);
	else if (temp_player == 2)
		if (player_animation == 0)
			texture.loadFromFile(third_dino_pic0);
		else if (player_animation == 1)
			texture.loadFromFile(third_dino_pic1);
		else
			texture.loadFromFile(third_dino_pic2);
	sprite.setTexture(texture);
	sprite.setScale(3.f, 3.f);
	sprite.setPosition(-150, 150);
	window.draw(sprite);
}
void Print_enemy() {
	switch (enemy->get_num()) { //выводим изображение врага
	case 0:
		if (enemy_animation == 0)
			texture.loadFromFile("animation/1.0.png");
		else if (enemy_animation == 1)
			texture.loadFromFile("animation/1.1.png");
		else
			texture.loadFromFile("animation/1.2.png");
		break;
	case 1:
		if (enemy_animation == 0)
			texture.loadFromFile("animation/2.0.png");
		else if (enemy_animation == 1)
			texture.loadFromFile("animation/2.1.png");
		else
			texture.loadFromFile("animation/2.2.png");
		break;
	case 2:
		if (enemy_animation == 0)
			texture.loadFromFile("animation/3.0.png");
		else if (enemy_animation == 1)
			texture.loadFromFile("animation/3.1.png");
		else
			texture.loadFromFile("animation/3.2.png");
		break;
	case 3:
		if (enemy_animation == 0)
			texture.loadFromFile("animation/4.0.png");
		else if (enemy_animation == 1)
			texture.loadFromFile("animation/4.1.png");
		else
			texture.loadFromFile("animation/4.2.png");
		break;
	}
	sprite.setTexture(texture);
	sprite.setScale(3.f, 3.f);
	sprite.setPosition(650, 150);
	window.draw(sprite);
}

void characteristics() {
	text_menu.setString(L"Сражается " + std::to_string(temp_player + 1) + " " + player->get_name());
	text_menu.setPosition(600 - text_menu.getGlobalBounds().width / 2, 160);
	window.draw(text_menu);
	text_menu.setString(L"Сражается " + std::to_string(temp_enemy + 1) + " " + enemy->get_name());
	text_menu.setPosition(1400 - text_menu.getGlobalBounds().width / 2, 160);
	window.draw(text_menu);

	switch (terrain) {
	case 0:
		characteristic_player = player->get_power();
		characteristic_enemy = enemy->get_power();
		double_strength();
		text_menu.setString(L"Сила игрока " + std::to_string(characteristic_player));
		text_menu.setPosition(600 - text_menu.getGlobalBounds().width / 2, 850);
		window.draw(text_menu);
		text_menu.setString(L"Сила врага " + std::to_string(characteristic_enemy));
		text_menu.setPosition(1400 - text_menu.getGlobalBounds().width / 2, 850);
		window.draw(text_menu);
		break;
	case 1:
		characteristic_player = player->get_dexterity();
		characteristic_enemy = enemy->get_dexterity();
		double_strength();
		text_menu.setString(L"Ловкость игрока " + std::to_string(characteristic_player));
		text_menu.setPosition(600 - text_menu.getGlobalBounds().width / 2, 850);
		window.draw(text_menu);
		text_menu.setString(L"Ловкость врага " + std::to_string(characteristic_enemy));
		text_menu.setPosition(1400 - text_menu.getGlobalBounds().width / 2, 850);
		window.draw(text_menu);
		break;
	case 2:
		characteristic_player = player->get_intellect();
		characteristic_enemy = enemy->get_intellect();
		double_strength();
		text_menu.setString(L"Интеллект игрока " + std::to_string(characteristic_player));
		text_menu.setPosition(600 - text_menu.getGlobalBounds().width / 2, 850);
		window.draw(text_menu);
		text_menu.setString(L"Интеллект врага " + std::to_string(characteristic_enemy));
		text_menu.setPosition(1400 - text_menu.getGlobalBounds().width / 2, 850);
		window.draw(text_menu);
		break;
	}
}
void Play_game() { //генерируем сцену 8 
	createDino();
	createRandomEnemy(); //рандомный динозавр для компьютера
	place = rand() % 3;
	while (temp_enemy < 3 && temp_player < 3) {
		while ((enemy->get_hp() > 0) && (player->get_hp() > 0)) {
			if ((player->get_hp() == 100) || (enemy->get_hp() == 100)) { //Выводим кол-во жизней 100
				window.clear(sf::Color::White); // Очищаем окна на белый цвет
				place_choice(); //генерируем текст про местность
				Print_enemy();
				Print_player();
				characteristics();

				text_menu.setString(L"Жизни игрока " + std::to_string(player->get_hp()));
				text_menu.setPosition(600 - text_menu.getGlobalBounds().width / 2, 240);
				window.draw(text_menu);
				text_menu.setString(L"Жизни врага " + std::to_string(enemy->get_hp()));
				text_menu.setPosition(1400 - text_menu.getGlobalBounds().width / 2, 240);
				window.draw(text_menu);

				window.display();
				Sleep(1000);

				if (player_animation < 2)
					player_animation++;
				else
					player_animation = 0;
				if (enemy_animation < 2)
					enemy_animation++;
				else
					enemy_animation = 0;
			}
			
			window.clear(sf::Color::White); // Очищаем окна на белый цвет
			place_choice(); //генерируем текст про местность
			Print_enemy();
			Print_player();
			characteristics();

			player->set_hp(player->get_hp() - characteristic_enemy);
			enemy->set_hp(enemy->get_hp() - characteristic_player);
			
			if (player->get_hp() > 0 ) {
				text_menu.setString(L"Жизни игрока " + std::to_string(player->get_hp()));
				text_menu.setPosition(600 - text_menu.getGlobalBounds().width / 2, 240);
				window.draw(text_menu);
			}
			if (player->get_hp() <= 0) {
				texture_death.loadFromFile("animation/death2.png");
				sprite_death.setTexture(texture_death);
				sprite_death.setScale(0.1f, 0.1f);
				sprite_death.setPosition(550, 240);
				window.draw(sprite_death);
			}
			if (enemy->get_hp() > 0) {
				text_menu.setString(L"Жизни врага " + std::to_string(enemy->get_hp()));
				text_menu.setPosition(1400 - text_menu.getGlobalBounds().width / 2, 240);
				window.draw(text_menu);
			}
			if (enemy->get_hp() <= 0) {
				texture_death.loadFromFile("animation/death2.png");
				sprite_death.setTexture(texture_death);
				sprite_death.setScale(0.1f, 0.1f);
				sprite_death.setPosition(1320, 240);
				window.draw(sprite_death);
			}
			window.display();
			Sleep(1000);

			if (enemy->get_hp() > 0) { //чтобы анимация не менялась когда динозавр враг умер
				if (player_animation < 2)
					player_animation++;
				else
					player_animation = 0;
			}
			if (player->get_hp() > 0) {
				if (enemy_animation < 2)
					enemy_animation++;
				else
					enemy_animation = 0;
			}
		}
		if (player->get_hp() <= 0) { //если у динозавра игрока закончились жизни, то генерируем нового
			temp_player++;
			if (temp_player < 3) {
				createDino();
				player->set_hp(100);
				player_animation = 0;	
			}
		}
		if (enemy->get_hp() <= 0) {//если у динозавра компьютера закончились жизни, то генерируем нового
			temp_enemy++;
			if (temp_enemy < 3) {
				createRandomEnemy();
				enemy->set_hp(100);
				enemy_animation = 0;
			}
		}
	}
	//все динозавры обоих или одного из игроков умерли
	if (temp_player < 3 || ((temp_player == 3) && (temp_enemy == 3))) {//если игрок победил или ничья
		scene = 9;
		money += 100;
		std::ofstream mon("деньги.txt");//записать новое значение money в инвентарь
		mon << money;
		mon.close();
		window.clear(sf::Color::White);
		text_menu.setString(L"Вы выиграли и получили 100 монет.\n\n                   Ваши деньги - " + std::to_string(money));
		text_menu.setPosition(950 - text_menu.getGlobalBounds().width / 2, 450);
		window.draw(text_menu);
		window.display();
	}
	else { //если проиграл
		scene = 9;
		window.clear(sf::Color::White);
		text_menu.setString(L"Вы проиграли и не заработали монеты");
		text_menu.setPosition(950 - text_menu.getGlobalBounds().width / 2, 450);
		window.draw(text_menu);
		window.display();
	}
	player_animation = 0;
	enemy_animation = 0;
	temp_player = 0;
	temp_enemy = 0;
	first_dino = -1, second_dino = -1, third_dino = -1;
}
void button_play() { //сцена 7
	if (flag_click) {
		button_menu.setPosition(900, 470);
		if (button_menu.getGlobalBounds().intersects(click_rect.getGlobalBounds())) { // Условие пересечения места клика с кнопкой
			scene = 8;
			flag_click = false;
			Play_game();
		}
	}
}

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	Start();
	Render_hello_screen();

	while (window.isOpen()) { // Бесконечный цикл пока открыто окно 
		flag_click = false; //сбрасываем признак нажатия лкм
		sf::Event event; // Объект на событие
		while (window.pollEvent(event)) { // Проходимся по всем событиям окна
			if (event.type == sf::Event::Closed) {  // Если событие - это закрытие окна
				window.close(); // Закрываем окно
			}
			if (event.type == sf::Event::MouseButtonPressed) { //если нажали мышкой на кнопку
				click_rect.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)); // Перемещаем на нужные координаты мнимый квадрат
				flag_click = true; //говорит о том, что была нажата лкм
				switch (scene) {
				case 0: // если мы начали игру
					Pressed_hello_screen();
					break;
				case 1: // если мы в главном меню
					MouseButtonPressed_menu();
					break;
				case 2:
					Pressed_pull();
					break;
				case 3: //если мы в магазине
					press_button_shop();
					break;
				case 4: //если мы выбрали дино в магазине
					buy_dino();
					break;
				case 7: 
					button_play();
					break;
				}
			}
			if (event.type == sf::Event::KeyReleased)
				if (event.key.code == sf::Keyboard::Escape) { //если нажали esc
					if (scene == 4 || scene == 5) {
						scene = 3;
						Render_shop();
					}
					else if (scene == 0)
						window.close();
					else {
						scene = 1;
						std::ofstream outp;
						outp.open("dinonum.txt", std::ios::app); //Перезаписываем инвентарь
						int i = 3;
						int j;
						while (i > 0) {
							if (i == 3) j = first_dino;
							if (i == 2) j = second_dino;
							if (i == 1) j = third_dino;
							switch (j) {
							case 0:
								outp << 0 << " "; break;
							case 1:
								outp << 1 << " "; break;
							case 2:
								outp << 2 << " "; break;
							case 3:
								outp << 3 << " "; break;
							default: break;
							}
							i--;
						}
						first_dino = -1, second_dino = -1, third_dino = -1;
						Render_menu();
					}
				}
		}
	}
}