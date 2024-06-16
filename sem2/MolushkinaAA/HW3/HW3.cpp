#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp> 
#include "windows.h"
sf::RenderWindow window(sf::VideoMode(600, 600), "Window", sf::Style::Close);  // Создаём объект окна с кнопкой закрытия

sf::RectangleShape button_menu(sf::Vector2f(400, 100)); // Объект кнопки меню (размер кнопки)
sf::RectangleShape click_rect(sf::Vector2f(1, 1)); // прямоугольник, который перемещается на место клика

sf::Font font; // Объект, хранящий в себе шрифт
sf::Text text_menu; // Текст для кнопок меню

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	window.clear(sf::Color::White); // Очищаем окна на белый цвет
	font.loadFromFile("arkhip.ttf"); // Считываем шрифт из arkhip.ttf файла

	text_menu.setFont(font); // Передаём шрифт в текст
	text_menu.setFillColor(sf::Color(64, 64, 64)); // Окрашиваем цвет в тёмно-серый цвет 
	text_menu.setCharacterSize(24); // Размер текста на экране в пиксели

	button_menu.setOutlineThickness(2); //толщина кнопок в меню
	button_menu.setOutlineColor(sf::Color::Black);

	button_menu.setPosition(100, 200);
	window.draw(button_menu);

	text_menu.setString(L"Выключить компьютер");
	text_menu.setPosition(300 - text_menu.getGlobalBounds().width / 2, 235);
	window.draw(text_menu);

	window.display();

	while (window.isOpen()) { // Бесконечный цикл пока открыто окно 
		sf::Event event; // Объект на событие
		while (window.pollEvent(event)) { // Проходимся по всем событиям окна
			if (event.type == sf::Event::Closed) {  // Если событие - это закрытие окна
				window.close(); // Закрываем окно
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				click_rect.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)); // Перемещаем на нужные координаты мнимый квадрат 
				if (button_menu.getGlobalBounds().intersects(click_rect.getGlobalBounds())) { // Условие пересечения с кнопкой
					int timer = rand() % 50 + 10;
					std::cout << "Ваш компьютер выключится через " << timer << " секунд" << std::endl;
					int i = 0;
					while (i < timer) {
						Sleep(1000);
						i++;
						std::cout << i << "\n";
					}
					system("C:\\WINDOWS\\System32\\shutdown /s /t 0"); //мнгновенное завершение работы компьютера
				}
			}
		}
	}
}