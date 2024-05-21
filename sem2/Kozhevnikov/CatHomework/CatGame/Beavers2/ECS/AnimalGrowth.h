#pragma once
#include "ECS.h"
#include "UIICon.h"
#include "SpriteComponent.h"
#include "TimeManager.h"
#include "HP.h"
#include "SystemMessage.h"

class AnimalGrowth : public Component
{
private:
	Transform* transform;

	UIIcon* escBack;
	float lastESC;

	UIText* hydrText;

	UIText* sizeText;

	UIText* cleanText;

	UIText* fullText;


	float lastTime;

	int size;
	int maxSize;

	int speedGrowth;

	int full;
	int maxFull;

	int hydr;
	int maxHydr;

	int clean;
	int maxClean;
public:
	AnimalGrowth() {}
	void init() override;
	void update() override;
	void draw() override;

	~AnimalGrowth();
private:
	void inline increaseFull(const int value)
	{
		if (full < maxFull) 
			full = std::min(full + value, maxFull);

		if (full > maxFull / 2.0f)
		{
			fullText->ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
	void inline decreaseFull(const int value)
	{ 
		if (full > 0) full -= value; 

		if (full < maxFull / 2.0f)
		{
			fullText->ChangeColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}

	void inline increaseHydr(const int value) 
	{ 
		if (hydr < maxHydr) 
			hydr = std::min(hydr + value, maxHydr);

		if (hydr > maxHydr / 2.0f)
		{
			hydrText->ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
	void inline decreaseHydr(const int value)
	{
		if (hydr > 0)  hydr -= value; 

		if (hydr < maxHydr / 2.0f)
		{
			hydrText->ChangeColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}

	void inline increaseClean(const int value)
	{ 
		if (clean < maxClean) 
			clean = std::min(clean + value, maxClean);

		if (clean > maxClean / 2.0f)
		{
			cleanText->ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
	void inline decreaseClean(const int value) 
	{
		if (clean > 0)  clean -= value; 

		if (clean < maxClean / 2.0f)
		{
			cleanText->ChangeColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}
};