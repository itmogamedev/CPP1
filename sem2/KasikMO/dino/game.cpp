#include "game.h"
#include "Windows.h"
#include <iostream>

void Game::initVars()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 720;
	this->videoMode.width = 1280;
	this->window = new sf::RenderWindow(this->videoMode, "SuperDino2D", sf::Style::Titlebar | sf::Style::Close);
}

void Game::fillStore()
{
	for (int i = 0; i < storeCap; i++) {
		Dino* d = new Dino();
		forsale.push_back(d);
	}
}

void Game::emptyStore()
{
	for (int i = 0; i < forsale.size(); i++) {
		delete forsale[i];
	}
	forsale.clear();
}

void Game::emptyCol()
{
	for (int i = 0; i < collection.size(); i++) {
		delete collection[i];
	}
	collection.clear();
}

void Game::loadCollection()
{
	int str = 0, agi, _int, hp, bp, cost, breed;
	std::string name;
	std::ifstream in("resources/collection.txt");
	in >> str;
	while (str >= 0) {
		in >> agi;
		in >> _int;
		in >> hp;
		in >> bp;
		in >> name;
		in >> cost;
		in >> breed;
		if (name == "EndOfDino" or name == "") break;
		Dino* d = new Dino(bp, str, _int, agi, hp, name, cost, breed);
		collection.push_back(d);
		chosen.push_back(false);
		in >> name;
		in >> str;
	}
}

Game::Game()
{
	this->initVars();
	this->initWindow();
	font.loadFromFile("resources/tuffy.ttf");
	mode = 1;
	storeCap = 5;
	storePage = 0;
	std::ifstream in("resources/money.txt");
	in >> money;
	loadCollection();
	fillStore();


}

void Game::showDinos(std::vector<Dino*> list)
{
	if (list.empty()) return;
	Dino* d = list[storePage];
	d->update();
	d->sprite.setPosition(500, 100);
	d->sprite.setScale(2, 2);
	window->draw(d->sprite);

	sf::Text t;
	t.setFont(font);
	t.setCharacterSize(24);
	t.setFillColor(sf::Color::Black);

	t.setString("Page: " + std::to_string(storePage + 1));
	t.setPosition(50, 50);
	window->draw(t);

	t.setString(d->name);
	t.setPosition(510, 65);
	window->draw(t);

	t.setString("Strength: " + std::to_string(d->STR));
	t.setPosition(100, 150);
	window->draw(t);
	t.setString("Agility: " + std::to_string(d->AGI));
	t.setPosition(100, 180);
	window->draw(t);
	t.setString("Intelligence: " + std::to_string(d->INT));
	t.setPosition(100, 210);
	window->draw(t);
	t.setString("HP: " + std::to_string(d->HP));
	t.setPosition(100, 240);
	window->draw(t);

	t.setString("Cost: " + std::to_string(d->cost));
	t.setPosition(100, 300);
	window->draw(t);
	switch (d->birthplace)
	{
	case 0:
		t.setString("from Plains");
		break;
	case 1:
		t.setString("from River");
		break;
	case 2:
		t.setString("from Mountains");
		break;
	default:
		break;
	}
	t.setPosition(510, 330);
	window->draw(t);
}

Game::~Game()
{
	std::ofstream out("resources/money.txt");
	out << money;
	emptyCol();
	emptyStore();
	delete this->window;
}

void Game::onFight()
{
	for (int i = 0; i < 3; i++) {
		enemypack.push_back(new Dino());
	}
	for (int i = 0; i < chosen.size(); i++) {
		if (chosen[i])
		mypack.push_back(collection[i]);
	}
	terrain = std::rand() % 3;
	myTurn = true;
}


const bool Game::running() const
{
	return this->window->isOpen();

}


void Game::updateEvs()
{

	while (this->window->pollEvent(this->event))
	{

		this->window->display();
		switch (event.type)
		{
		case sf::Event::Closed:
			this->window->close();
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				this->window->close();
			if (event.key.code == sf::Keyboard::Left) {
				if (storePage > 0)
					storePage--;
			}
			if (event.key.code == sf::Keyboard::S) {
				if (mode == 0)
					mode = 1;
			else if (mode == 1 or mode == 4)
					mode = 0;
				storePage = 0;
			}
			if (event.key.code == sf::Keyboard::B and mode == 1 and c > 0) {
				mode = 2;
				onFight();
			}
			if (event.key.code == sf::Keyboard::C and mode == 1) {
				if (!(!chosen[storePage] and c >= 3))
				chosen[storePage] = !chosen[storePage];
			}
			if (mode == 0 and event.key.code == sf::Keyboard::Right) {
				if (storePage < storeCap -1)
					storePage++;
			}
			if (mode == 1 and event.key.code == sf::Keyboard::Right) {
				if (storePage < collection.size() - 1)
					storePage++;
			}
			if (event.key.code == sf::Keyboard::F5) {
				emptyStore();
				fillStore();
			}
			if (mode == 0 and event.key.code == sf::Keyboard::Space and money >= forsale[storePage]->cost) {
				collection.push_back(forsale[storePage]);
				forsale[storePage]->dump();
				money -= forsale[storePage]->cost;
				chosen.push_back(false);
			}
			
		default:
			break;
		}
	}
}

void Game::makeTurn()
{
	Dino* offender;
	Dino* defender;
	if (mypack.back()->HP <= 0)
		mypack.pop_back();
	if (enemypack.back()->HP <= 0)
		enemypack.pop_back();
	if (mypack.empty())
	{
		mode = 4;
		myVictory = false;
		return;
	}
	if (enemypack.empty())
	{
		mode = 4;
		reward = 50 + std::rand() % 50;
		money += reward;
		myVictory = true;
		return;
	}

	


	if (myTurn) {
		offender = mypack.back();
		defender = enemypack.back();
	}
	else {
		offender = enemypack.back();
		defender = mypack.back();
	}
	int d = offender->countDmg(terrain);
	offender->Damage(d);
	defender->takeDamage(d);
	myTurn = !myTurn;
}

void Game::update()
{
	this->updateEvs();
}

void Game::render()
{
	this->window->clear(sf::Color(0xAB, 0xEA, 0x90));
	if (mode == 0) {
		showDinos(forsale);
		sf::Text t;
		t.setFont(font);
		t.setCharacterSize(24);
		t.setFillColor(sf::Color::Black);

		t.setString("Shop");
		t.setPosition(900, 50);
		window->draw(t);

		t.setString("Money: "+std::to_string(money));
		t.setPosition(900, 100);
		window->draw(t);
	}
	if (mode == 1) {
		showDinos(collection);
		sf::Text t;
		t.setFont(font);
		t.setCharacterSize(24);
		t.setFillColor(sf::Color::Black);

		t.setString("Collection");
		t.setPosition(900, 50);
		window->draw(t);
		
		c = 0;
		for (int i = 0; i < chosen.size(); i++) {
			if (i == storePage and chosen[i]) {
				t.setString("Chosen!");
				t.setPosition(500, 400);
				window->draw(t);
			}
			if (chosen[i]) {
				t.setString(collection[i]->name);
				t.setPosition(800, 150+c*100);
				window->draw(t);
				collection[i]->sprite.setScale(1, 1);
				collection[i]->sprite.setPosition(1000, 100 + c * 100);
				window->draw(collection[i]->sprite);
				c++;
			}
		}
	}
	if (mode == 2) {
		makeTurn();
		showFight();
	}
	if (mode == 4) {
		sf::Text t;
		t.setFont(font);
		t.setCharacterSize(24);
		t.setFillColor(sf::Color::Black);
		if (myVictory) {
			t.setString("You won, got money: " + std::to_string(reward));
		}
		else {
			t.setString("You lost");
		}
		t.setPosition(300, 300);
		window->draw(t);
	}

	
	this->window->display();
	if (mode == 2) Sleep(500);
	else Sleep(100);
}

void Game::showFight()
{
	if (mypack.empty() or enemypack.empty()) return;
	sf::Text t;
	t.setFont(font);
	t.setCharacterSize(24);
	t.setFillColor(sf::Color::Black);
	
	int counter = 0;
	for (Dino* i : mypack) {
		t.setString(i->name);
		t.setPosition(300, 50 + counter * 100);
		window->draw(t);
		i->sprite.setScale(1, 1);
		i->sprite.setPosition(100, 50 + counter * 100);
		window->draw(i->sprite);
		counter++;
	}
	counter = 0;
	for (Dino* i : enemypack) {
		t.setString(i->name);
		t.setPosition(800, 50 + counter * 100);
		window->draw(t);
		i->sprite.setScale(-1, 1);
		i->sprite.setPosition(1210, 50 + counter * 100);
		window->draw(i->sprite);
		counter++;
	}
	Dino* myFighter = mypack.back();
	Dino* enemyFighter = enemypack.back();
	myFighter->sprite.setPosition(100, 400);
	myFighter->sprite.setScale(1.5, 1.5);
	window->draw(myFighter->sprite);

	t.setString(myFighter->name + " " + myFighter->bstr);
	t.setPosition(100, 600);
	window->draw(t);
	t.setString("HP: " + std::to_string(myFighter->HP));
	t.setPosition(100, 640);
	window->draw(t);

	enemyFighter->sprite.setPosition(1000, 400);
	enemyFighter->sprite.setScale(-1.5, 1.5);
	window->draw(enemyFighter->sprite);

	t.setString(enemyFighter->name + " " + enemyFighter->bstr);
	t.setPosition(800, 600);
	window->draw(t);
	t.setString("HP: " + std::to_string(enemyFighter->HP));
	t.setPosition(800, 640);
	window->draw(t);



	switch (terrain)
	{
	case 0:
		t.setString("Plains");
		break;
	case 1:
		t.setString("River");
		break;
	case 2:
		t.setString("Mountains");
		break;
	default:
		break;
	}
	t.setPosition(500, 350);
	window->draw(t);
	


	

}


