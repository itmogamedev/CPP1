#pragma once
#include <string>
#include "terrain.h"
#include <SFML/Graphics.hpp>

enum class Direction : bool {
	LEFT = 1,
	RIGHT = -1
};

class CP_DinosaurBase {
public:
    virtual ~CP_DinosaurBase();

    void CP_TakeDamage(float CP_DinoDMG);
    void CP_CheckDeath();

    void CP_SetIsAttacking(bool CP_NewBool);
    void CP_SetIsAlive(bool CP_NewBool);
    void CP_SetIsChoosedInArsenal(bool CP_NewBool);
    void CP_SetIsPurchased(bool CP_NewBool);
    void CP_SetDinoPosition(sf::Vector2f CP_NewDinoPosition);
    void CP_drawTo(sf::RenderWindow& window);

    float CP_GetDinoHealth();
    float CP_GetDinoCurrentHP();
    int CP_GetDinoCost();

    std::string CP_GetDinoName();
    int CP_GetDinoDamage();
    int CP_GetDinoIntellect();
    int CP_GetDinoMovement();

    bool CP_GetIsAttacking();
    bool CP_GetIsAlive();
    bool CP_GetIsChoosedInArsenal();
    bool CP_GetIsPurchased();

    std::string CP_GetDinoPath();
    sf::Vector2f CP_GetDinoPosition();
    sf::Sprite CP_GetDinoSprite();
    sf::Texture CP_GetDinoTexture();
    Direction CP_GetDinoDirection();

    CP_DinosaurBase() {
        CP_DinoName = "default";
        CP_DinoHealth = 0;
        CP_DinoCurrentHP = 0;
        CP_DinoCost = 0;
        CP_DinoDamage = 0;
        CP_DinoIntellect = 0;
        CP_DinoMovement = 0;
        CP_IsAttacking = false;
        CP_IsAlive = true;
        CP_IsChoosedInArsenal = false;
        CP_IsPurchased = false;
        CP_DinoImagePath = "default.png";
    }

    CP_DinosaurBase(std::string CP_NName, int CP_NHealth, int CP_NCHP, int CP_NCost, int CP_NDMG, int CP_NInt, int CP_NMov, bool CP_NIsAttack, bool CP_NIsAlive, bool CP_NIsChA, bool CP_NIsPurch, std::string CP_NPath) {
        CP_DinoName = CP_NName;
        CP_DinoHealth = CP_NHealth;
        CP_DinoCurrentHP = CP_NCHP;
        CP_DinoCost = CP_NCost;
        CP_DinoDamage = CP_NDMG;
        CP_DinoIntellect = CP_NInt;
        CP_DinoMovement = CP_NMov;
        CP_IsAttacking = CP_NIsAttack;
        CP_IsAlive = CP_NIsAlive;
        CP_IsChoosedInArsenal = CP_NIsChA;
        CP_IsPurchased = CP_NIsPurch;
        CP_DinoImagePath = CP_NPath;

        if (CP_DinoTexture.loadFromFile(CP_DinoImagePath + ".png")) {
            CP_DinoSprite.setTexture(CP_DinoTexture);
        }
    };

protected:
    std::string CP_DinoName;

    float CP_DinoHealth;
    float CP_DinoCurrentHP;
    int CP_DinoCost;

    // Dinosaur Attack Stats
    int CP_DinoDamage;
    int CP_DinoIntellect;
    int CP_DinoMovement;

    // Dinosaur Booleans
    bool CP_IsAttacking;
    bool CP_IsAlive;
    bool CP_IsChoosedInArsenal;
    bool CP_IsPurchased;

    // Dino Vectors
    std::string CP_DinoImagePath;
    sf::Vector2f CP_DinoPosition;
    sf::Texture CP_DinoTexture;
    sf::Sprite CP_DinoSprite;

    Direction CP_DinoDirection = Direction::RIGHT;
};