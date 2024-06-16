#pragma once
#include <SFML/Graphics.hpp>
#include "character.h"
#include "bot.h"

class CP_Player {
public:
    int GetBalance();

    bool GetIsTurn();

    void SetBalance(int MoneyRN);

    void SetTurn(bool NewIsTurnToAttack);

    void ChangePlusBalance(int NewMoney);

    void ChangeMinusBalance(int DinoCost);

    CP_DinosaurBase* GetDinosaurPlayer(int i);

    int TeamSize();

    void TeamClear();

    void AddDino(CP_DinosaurBase* Dino);
protected:
    std::vector<CP_DinosaurBase*> DinosaurPlayerChoosed;
    int CP_PlayerBalance = 52;
    bool CP_IsTurnToAttack = true;
};

class CP_Bot {
public:
    int BTeamSize();
    void BTeamClear();
    CP_DinosaurBase* GetDinosaurBot(int i);
    void AddBotDino(CP_DinosaurBase* Dino);
protected:
    std::vector<CP_DinosaurBase*> DinosaurBotChoosed;
};

void RandomGeneratorForTerrain();
int get_terrain();
void PlayerAttackOtherDino(int DinoPlayerChoosed, int DinoToAttack, CP_Player& player, CP_Bot& BotDino);
void BotAttackOtherDino(int DinoPlayerChoosed, int DinoToAttack, CP_Bot& BotDino, CP_Player& player);