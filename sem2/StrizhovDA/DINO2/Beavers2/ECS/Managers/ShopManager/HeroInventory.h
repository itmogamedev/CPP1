#pragma once
#include "ECS.h"
#include "Dino.h"
#include "UIButton.h"
#include "SystemMessage.h"
#include "SaveManager.h"
#include "SavebleObj.h"
#include "DinoCreator.h"

class HeroInventory : public Component, public SavebleObj
{
private:
	UIText* moneyCount;

	static std::vector<Dino*> dinos;
	static std::vector<Entity*> buttons;

	static glm::vec2 startCoords;
	bool inShop;

	static float cardX;
	static float cardY;

public:
	static int nowMoney;

	HeroInventory(bool inShopState);

	void init() override;
	void draw() override;

	static void AddDino(Dino* dino);

	void SaveData() override;
	void LoadData() override;

	~HeroInventory();
private:
	static Entity* CreateDinoCard(Dino& dino, glm::vec2 pos);
};