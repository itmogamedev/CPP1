#include "player.h"
#include <iostream>

const int sizet = 1;
int terrain[sizet];

void RandomGeneratorForTerrain() {
    srand(time(NULL));

    bool alreadyThere;

    for (int i = 0; i < sizet;)
    {
        alreadyThere = false;
        int newRanomValue = rand() % 3;

        for (int j = 0; j < i; j++)
        {
            if (terrain[j] == newRanomValue)
            {
                alreadyThere = true;
                break;
            }
        }

        if (!alreadyThere)
        {
            terrain[i] = newRanomValue;
            i++;
        }

    }
}

int get_terrain()
{
    return terrain[0];
}

int CP_Player::GetBalance()
{
    return CP_PlayerBalance;
}

bool CP_Player::GetIsTurn()
{
    return CP_IsTurnToAttack;
}

void CP_Player::SetBalance(int MoneyRN)
{
    this->CP_PlayerBalance = MoneyRN;
}

void CP_Player::SetTurn(bool NewIsTurnToAttack)
{
    this->CP_IsTurnToAttack = NewIsTurnToAttack;
}

void CP_Player::ChangePlusBalance(int NewMoney)
{
    CP_PlayerBalance += NewMoney;
}

void CP_Player::ChangeMinusBalance(int DinoCost)
{
    CP_PlayerBalance -= DinoCost;
}

void PlayerAttackOtherDino(int DinoPlayerChoosed, int DinoToAttack, CP_Player& player, CP_Bot& BotDino)
{
    if (BotDino.GetDinosaurBot(DinoToAttack)->CP_GetIsAlive() == true) {
        switch (terrain[0]) {
        case Terrain::Steam:
            BotDino.GetDinosaurBot(DinoToAttack)->CP_TakeDamage(player.GetDinosaurPlayer(DinoPlayerChoosed)->CP_GetDinoDamage());
            break;
        case Terrain::VKPlay:
            BotDino.GetDinosaurBot(DinoToAttack)->CP_TakeDamage(player.GetDinosaurPlayer(DinoPlayerChoosed)->CP_GetDinoMovement());
            break;
        case Terrain::EpicGamesStore:
            BotDino.GetDinosaurBot(DinoToAttack)->CP_TakeDamage(player.GetDinosaurPlayer(DinoPlayerChoosed)->CP_GetDinoIntellect());
            break;
        }
    }
    else if (BotDino.GetDinosaurBot(DinoToAttack)->CP_GetIsAlive() == false) {
    }
}

void BotAttackOtherDino(int DinoPlayerChoosed, int DinoToAttack, CP_Bot& BotDino, CP_Player& player)
{
    if (player.GetDinosaurPlayer(DinoToAttack)->CP_GetIsAlive() == true) {
        switch (terrain[0]) {
        case Terrain::Steam:
            player.GetDinosaurPlayer(DinoToAttack)->CP_TakeDamage(BotDino.GetDinosaurBot(DinoPlayerChoosed)->CP_GetDinoDamage());
            break;
        case Terrain::VKPlay:
            player.GetDinosaurPlayer(DinoToAttack)->CP_TakeDamage(BotDino.GetDinosaurBot(DinoPlayerChoosed)->CP_GetDinoMovement());
            break;
        case Terrain::EpicGamesStore:
            player.GetDinosaurPlayer(DinoToAttack)->CP_TakeDamage(BotDino.GetDinosaurBot(DinoPlayerChoosed)->CP_GetDinoIntellect());
            break;
        }
    }
}

CP_DinosaurBase* CP_Player::GetDinosaurPlayer(int i)
{
    return DinosaurPlayerChoosed[i];
}

int CP_Player::TeamSize()
{
    return DinosaurPlayerChoosed.size();
}

void CP_Player::TeamClear()
{
    DinosaurPlayerChoosed.clear();
}

void CP_Player::AddDino(CP_DinosaurBase* Dino)
{
    DinosaurPlayerChoosed.push_back(Dino);
}

int CP_Bot::BTeamSize()
{
    return DinosaurBotChoosed.size();
}

void CP_Bot::BTeamClear()
{
    DinosaurBotChoosed.clear();
}

CP_DinosaurBase* CP_Bot::GetDinosaurBot(int i)
{
    return DinosaurBotChoosed[i];
}

void CP_Bot::AddBotDino(CP_DinosaurBase* Dino)
{
    DinosaurBotChoosed.push_back(Dino);
}
