#pragma once

void handleInventory(sf::Event& event, sf::RenderWindow& window, sf::Font& font, sf::Text& balance, \
	sf::Text& earnedBalance, int& cntUserTyrannosaurus, int& cntUserStegosaurus, \
	int& cntUserTriceratops)
{
	sf::Texture shopBackground, nameTyrannosaurusTexture, nameStegosaurusTexture, nameTriceraptorTexture, \
		TyrannosaurusTexture, StegosaurusTexture, TriceratopsTexture;
	shopBackground.loadFromFile("images/shop.png");
	TyrannosaurusTexture.loadFromFile("images/shop-Tyrannosaurus-compressed.png");
	StegosaurusTexture.loadFromFile("images/shop-Stegosaurus-compressed.png");
	TriceratopsTexture.loadFromFile("images/shop-Triceratops-compressed.png");
	sf::Sprite shopBg(shopBackground), Tyrannosaurus(TyrannosaurusTexture), Stegosaurus(StegosaurusTexture), Triceratops(TriceratopsTexture);

	Tyrannosaurus.setPosition(50, 110);
	Stegosaurus.setPosition(50, 360);
	Triceratops.setPosition(50, 610);

	//������� ��������� ��� ������ � ����������� ����������
	sf::Text cntUserTyrannosaurusText("", font, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	cntUserTyrannosaurusText.setStyle(sf::Text::Bold);//������ �����
	sf::Text cntUserStegosaurusText("", font, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	cntUserStegosaurusText.setStyle(sf::Text::Bold);//������ �����
	sf::Text cntUserTriceratopsText("", font, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	cntUserTriceratopsText.setStyle(sf::Text::Bold);//������ �����
	
	cntUserTyrannosaurusText.setPosition(400, 110);
	cntUserStegosaurusText.setPosition(400, 360);
	cntUserTriceratopsText.setPosition(400, 610);

	while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();


		window.draw(shopBg);
		window.draw(Tyrannosaurus);
		window.draw(Stegosaurus);
		window.draw(Triceratops);

		// ����� ���������� ���� � ���������
		cntUserTyrannosaurusText.setString("Tyrannosaurus: " + std::to_string(cntUserTyrannosaurus));
		cntUserStegosaurusText.setString("Stegosaurus: " + std::to_string(cntUserStegosaurus));
		cntUserTriceratopsText.setString("Triceratops: " + std::to_string(cntUserTriceratops));
		window.draw(cntUserTyrannosaurusText);
		window.draw(cntUserStegosaurusText);
		window.draw(cntUserTriceratopsText);
		window.display();


	}
}