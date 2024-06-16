#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include "Store.h"
#include "Fight.h"
#include "DinoCollection.h"

class GameState {
private:
    Store store;
    Fight fight;

public:
    Store* getStore();
    Fight* getFight();
};
