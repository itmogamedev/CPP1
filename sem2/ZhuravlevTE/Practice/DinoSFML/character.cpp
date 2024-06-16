#include "character.h"
#include "character.h"
#include "character.h"

CP_DinosaurBase::~CP_DinosaurBase() {}

void CP_DinosaurBase::CP_TakeDamage(float CP_DinoDMG)
{
	CP_CheckDeath();
	CP_DinoCurrentHP -= CP_DinoDMG;
	CP_CheckDeath();
}

void CP_DinosaurBase::CP_CheckDeath()
{
	if (CP_DinoCurrentHP <= 0) {
		CP_DinoCurrentHP = 0;
		CP_IsAlive = false;
	}
}

void CP_DinosaurBase::CP_SetIsAttacking(bool CP_NewBool)
{
	CP_IsAttacking = CP_NewBool;
}

void CP_DinosaurBase::CP_SetIsAlive(bool CP_NewBool)
{
	CP_IsAlive = CP_NewBool;
}

void CP_DinosaurBase::CP_SetIsChoosedInArsenal(bool CP_NewBool)
{
	CP_IsChoosedInArsenal = CP_NewBool;
}

void CP_DinosaurBase::CP_SetIsPurchased(bool CP_NewBool)
{
	CP_IsPurchased = CP_NewBool;
}

void CP_DinosaurBase::CP_SetDinoPosition(sf::Vector2f CP_NewDinoPosition)
{
	CP_DinoPosition = CP_NewDinoPosition;
}

void CP_DinosaurBase::CP_drawTo(sf::RenderWindow& window)
{
	window.draw(CP_DinoSprite);
}

float CP_DinosaurBase::CP_GetDinoHealth()
{
	return CP_DinoHealth;
}

float CP_DinosaurBase::CP_GetDinoCurrentHP()
{
	return CP_DinoCurrentHP;
}

int CP_DinosaurBase::CP_GetDinoCost()
{
	return CP_DinoCost;
}

std::string CP_DinosaurBase::CP_GetDinoName()
{
	return CP_DinoName;
}

int CP_DinosaurBase::CP_GetDinoDamage()
{
	return CP_DinoDamage;
}

int CP_DinosaurBase::CP_GetDinoIntellect()
{
	return CP_DinoIntellect;
}

int CP_DinosaurBase::CP_GetDinoMovement()
{
	return CP_DinoMovement;
}

bool CP_DinosaurBase::CP_GetIsAttacking()
{
	return CP_IsAttacking;
}

bool CP_DinosaurBase::CP_GetIsAlive()
{
	return CP_IsAlive;
}

bool CP_DinosaurBase::CP_GetIsChoosedInArsenal()
{
	return CP_IsChoosedInArsenal;
}

bool CP_DinosaurBase::CP_GetIsPurchased()
{
	return CP_IsPurchased;
}

std::string CP_DinosaurBase::CP_GetDinoPath()
{
	return CP_DinoImagePath;
}

sf::Vector2f CP_DinosaurBase::CP_GetDinoPosition()
{
	return CP_DinoPosition;
}

sf::Sprite CP_DinosaurBase::CP_GetDinoSprite()
{
	return CP_DinoSprite;
}

sf::Texture CP_DinosaurBase::CP_GetDinoTexture()
{
	return CP_DinoTexture;
}

Direction CP_DinosaurBase::CP_GetDinoDirection()
{
	return CP_DinoDirection;
}
