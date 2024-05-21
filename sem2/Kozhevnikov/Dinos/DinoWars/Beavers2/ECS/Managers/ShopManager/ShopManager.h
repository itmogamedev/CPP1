#pragma once
#include "ECS.h"
#include "DinoCreator.h"
#include "UIButton.h"
#include "SystemMessage.h"

class ShopManager : public Component
{
private:
	std::vector<Dino*> dinos;
	std::vector<Entity*> cards;

	glm::vec2 startCoords;

	static float cardX;
	static float cardY;
public:

	void init() override;
	void update() override;


	~ShopManager();

private:
	Entity* CreateDinoCard(Dino* dino, glm::vec2 pos);
};