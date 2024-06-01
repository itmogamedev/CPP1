#pragma once
#include "Resourses.h"


// ������������ ����� ���������
enum Terrain { Plain, River, Mountain };

// ������� ����� ����
class Dinobase { // ����� ������ ���� �����������
protected:
	int STR = 0; // ���� 10 - 30
	int DEX = 0; // �������� 10 - 30
	int INT = 0; // ��������� 10 - 30
	int cost = 0; // ����
	int type = 0;
	std::string name; // ���
	int TextureOffsetX = 0;
public:
	Dinobase()
	{
	}
	~Dinobase()
	{
	}
	int HP = 100;
	sf::Sprite dinoSprite;
	virtual int Damage(Terrain terrain) = 0;
	int GetCost() { return cost; }
	int GetStr() { return STR; }
	int GetDex() { return DEX; }
	int GetInt() { return INT; }
	std::string GetType() {
		switch (type)
		{
		case Plain: return "Plain(STR)";
		case River: return "River(DEX)";
		case Mountain: return "Mountain(INT)";
		default: return "noname";
		}
	}
	std::string getname() { return name; }
	void Animation(std::string animName, int frames)
	{
		dinoSprite.setTexture(Textures["resources/DinoTextures/" + animName + "_" + name + ".png"]);
		TextureOffsetX = (TextureOffsetX + 24) % (24 * frames);
		dinoSprite.setTextureRect(sf::IntRect(TextureOffsetX, 0, 24, 24));
	}
};

// �������� ��� ���� ���� Plain(STR)
class DinoStr : virtual public Dinobase {

public:
	int Damage(Terrain terrain) {
		return terrain == Plain ?
			2 * STR :
			terrain == River ?
			DEX :
			INT;
	}
};

// �������� ��� ���� ���� River(DEX)
class DinoDex : virtual public Dinobase {
public:
	int Damage(Terrain terrain) {
		return terrain == River ?
			2 * DEX :
			terrain == Plain ?
			STR :
			INT;
	}
};

// �������� ��� ���� ���� Mountain(INT)
class DinoInt : virtual public Dinobase {
public:
	int Damage(Terrain terrain) {
		return terrain == Mountain ?
			2 * INT :
			terrain == Plain ?
			STR :
			DEX;
	}
};

// �������� �� 3-� ������� ����, ����������� ����� ������������
class Dino : public DinoInt, public DinoStr, public DinoDex
{
private:
	int (Dino::* curdamage)(Terrain terrain); // ���������� curdamage
	int damage_int(Terrain terrain) { return DinoInt::Damage(terrain); }
	int damage_str(Terrain terrain) { return DinoStr::Damage(terrain); }
	int damage_dex(Terrain terrain) { return DinoDex::Damage(terrain); }


public:
	Dino(int str, int dex, int intl, int cost, int type, std::string name)
	{
		std::cout << "DINO CREATED\n";
		this->STR = str;
		this->DEX = dex;
		this->INT = intl;
		this->cost = cost;
		this->type = type;
		this->name = name;
		dinoSprite.setTexture(Textures["resources/DinoTextures/Idle_" + name + ".png"]);
		dinoSprite.setScale(15, 15);
		dinoSprite.setTextureRect(sf::IntRect(TextureOffsetX, 0, 24, 24));
		dinoSprite.setOrigin((dinoSprite.getLocalBounds().left + dinoSprite.getLocalBounds().width) / 2.f, (dinoSprite.getLocalBounds().top + dinoSprite.getLocalBounds().height) / 2.f);
		dinoSprite.setPosition(width / 2.f, height / 2.f);
		switch (type)
		{
		case Plain: curdamage = &Dino::damage_str; break;  // ������������ curdamage ������ �� ������(� ����������� �� ����) �������
		case River: curdamage = &Dino::damage_dex; break;
		case Mountain: curdamage = &Dino::damage_int; break;
		default: curdamage = &Dino::damage_int; break;
		}
	}
	~Dino()
	{
		std::cout << "DINO DELETED\n";
	}
	int Damage(Terrain terrain) { // ��������� ������� damage �������������� �� ������ �������
		return (this->*curdamage)(terrain);
	}
};

// ������
class Button
{
public:
	Button(sf::Sprite sprite, sf::Text text, sf::Vector2f position, sf::Color text_color = sf::Color::Black, int buttonId = 0)
	{
		this->ButtonId = buttonId;
		this->Sprite = sprite;
		this->Text = text;
		Sprite.setOrigin(Sprite.getLocalBounds().getSize() / 2.f);
		Text.setOrigin((Text.getLocalBounds().left + Text.getLocalBounds().width) / 2.f, (Text.getLocalBounds().top + Text.getLocalBounds().height) / 2.f);
		Sprite.setPosition(position);
		Text.setPosition(Sprite.getPosition() - sf::Vector2f(0, 12));
		Text.setFillColor(text_color);
	}
	int ButtonId;
	sf::Sprite Sprite;
	sf::Text Text;
};

// ����� ������
class Player
{
public:
	int currbalance, victnum, losnum;
	std::vector<Dino*>dinoset;

};

// ������������� � �������
class TextRect
{
public:
	TextRect()
	{
	}
	// ������������� � �������
	TextRect(float posX, float posY, float width, float height, sf::Color bgColor, sf::Color outlineColor, float outlineThickness, sf::Text text, sf::Vector2f textOffset, sf::Color textColor)
	{
		this->Rect = sf::RectangleShape(sf::Vector2f(width, height));
		this->Text = text;
		CenterOrigin(Rect);
		CenterOrigin(Text);
		Rect.setFillColor(bgColor);
		Text.setFillColor(textColor);
		Rect.setPosition(posX, posY);
		Text.setPosition(Rect.getPosition() + textOffset);
		Rect.setOutlineColor(outlineColor);
		Rect.setOutlineThickness(outlineThickness);
	}
	// ������������� � ������� � ���������(����������� ������� ������� �����)
	TextRect(float posX, float posY, float width, float height, sf::Color bgColor, sf::Color outlineColor, float outlineThickness, sf::Text text, sf::Vector2f textOffset, sf::Color textColor, sf::Text valueText, sf::Vector2f valueTextOffSet)
	{
		this->Rect = sf::RectangleShape(sf::Vector2f(width, height));
		CenterOrigin(Rect);
		Rect.setFillColor(bgColor);
		Rect.setPosition(posX, posY);
		Rect.setOutlineColor(outlineColor);
		Rect.setOutlineThickness(outlineThickness);

		this->Text = text;
		this->ValueText = valueText;
		CenterOrigin(Text);
		CenterOrigin(ValueText);

		if (Text.getString() == "")
		{
			ValueText.setPosition(Rect.getPosition().x, Rect.getPosition().y - 5);
		}
		else
		{
			ValueText.setPosition(Rect.getPosition() + valueTextOffSet);
			Text.setPosition(Rect.getPosition() + textOffset);
			Text.setFillColor(textColor);
		}
	}
	void Draw(sf::RenderWindow& window) // ���������� ���� �������������
	{
		window.draw(Rect);
		window.draw(Text);
		window.draw(ValueText);
	}
	void Move(float x, float y)
	{
		sf::Vector2f vector(x, y);
		Rect.move(vector);
		Text.move(vector);
		ValueText.move(vector);
	}
	sf::RectangleShape Rect;
	sf::Text Text;
	sf::Text ValueText;
};