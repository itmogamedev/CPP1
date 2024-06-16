#include "DinoCollection.h"

DinoCollection::~DinoCollection()
{
}

std::vector<Dino*>* DinoCollection::getDinos() { return &dinos; }

std::vector<Dino*>* DinoCollection::getAvailableDinos() { return &availableDinos; }

std::vector<Dino*>* DinoCollection::getAllDinos() { return &allDinos; }

std::vector<Dino*>* DinoCollection::getFightDinos() { return &fightDinos; }

void DinoCollection::addDino(Dino* d)
{
    dinos.push_back(d);

    std::vector<Dino*>::iterator it = std::find(availableDinos.begin(), availableDinos.end(), d);
    if (it != availableDinos.end())
        {
            availableDinos.erase(it);
        }
}

void DinoCollection::addStartDinos()
{
    addDino(&tyrannosaurus);
    fightDinos.push_back(&tyrannosaurus);
}

void DinoCollection::pushFightDino(Dino* d)
{
    fightDinos.push_back(d);
}

void DinoCollection::addFightDino(std::string input)
{
    if (fightDinos.size() < 3) {
        for (Dino* d : dinos) {
            if (d->getName() == input) {
                pushFightDino(d);
                return;
            }
        }
    }
}

void DinoCollection::deleteFightDino(std::string input) {
    for (int i = 0; i < fightDinos.size(); i++) {
        if (fightDinos[i]->getName() == input) {
            fightDinos.erase(fightDinos.begin() + i);
            return;
        }
    }
}

int DinoCollection::isFighter(Dino* d)
{
    for (int i = 1; i < fightDinos.size() + 1; i++)
        if (fightDinos.at(i - 1) == d) return i;

    return 0;
}

void DinoCollection::manageFighters(std::string input)
{
    for (Dino* d : dinos) {
        if (d->getName() == input) {
            if (isFighter(d)) deleteFightDino(input);
            else addFightDino(input);
            break;
        }
    }
}

void DinoCollection::run()
{
}
