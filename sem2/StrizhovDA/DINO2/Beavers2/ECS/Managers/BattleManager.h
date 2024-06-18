#pragma once
#include "ECS.h"
#include "UIButton.h"
#include "SystemMessage.h"
#include "UIIcon.h"
#include "Funcs.h"
#include "Dino.h"
#include "SaveManager.h"
#include "SavebleObj.h"
#include "DinoCreator.h"
#include "HP.h"

class BattleManager : public Component, public SavebleObj
{
private:
	static float cardX;
	static float cardY;

	UIText* nowTurnText;
	UIIcon* background;

	float winMoney;

	Dino* activeDino;
	Dino* activeEnemyDino;
	Dino* lowHPDino;


	std::vector<Dino*> enemyDinos;
	std::vector<Entity*> cardEnemy;
	float lastTimeChoosed_Enemy;
	float lastTimeChoosedToAttack_Enemy;

	std::vector<Dino*> toFightDino;
	std::vector<Entity*> cardHeroToFight;

	std::vector<Dino*> heroDinos;
	std::vector<Entity*> cardHero;

	Area nowArea;

	bool heroTurn;

	bool SettedCards;
	bool inFight;
public:
	
	inline void init() override;
	void update() override;
	void draw() override;

	void SaveData() override;
	void LoadData() override;

	~BattleManager();
private:
	void HeroLogic();
	void EnemyLogic();

	void SetEnemyDinos();
	void SetHeroDinos();

	void SetChooseDino();
	void StartFight();

	Entity* CreateDinoCard(Dino* dino, glm::vec2 pos);
	Entity* CreateDinoCardFight(Dino* dino, glm::vec2 pos);
	Entity* CreateEnemyDinoCard(Dino* dino, glm::vec2 pos);

	void SetOtherCardsUnactive(Entity* button);
	void SetAllCardUnactive();
};