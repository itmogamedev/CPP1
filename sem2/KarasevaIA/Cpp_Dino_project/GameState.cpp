#include "GameState.h"

Store* GameState::getStore() {
    return &store;
}

Fight* GameState::getFight()
{
    return &fight;
}