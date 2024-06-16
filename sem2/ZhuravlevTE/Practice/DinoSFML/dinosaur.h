#pragma once
#include <SFML/Graphics.hpp>
#include "character.h"

class CP_Smuta : public CP_DinosaurBase {
public:
	CP_Smuta() : CP_DinosaurBase("Smuta", 400, 400, 50, 150, 143, 124, false, true, false, false, "images/Smuta") {};
};

class CP_SumoTatami : public CP_DinosaurBase {
public:
	CP_SumoTatami() : CP_DinosaurBase("Sumo Tatami", 450, 450, 50, 150, 155, 84, false, true, false, false, "images/SumoTatami") {};
};

class CP_CS2 : public CP_DinosaurBase {
public:
	CP_CS2() : CP_DinosaurBase("Counter-Strike 2", 250, 250, 50, 150, 142, 122, false, true, false, false, "images/CS2") {};
};

class CP_Chernograd : public CP_DinosaurBase {
public:
	CP_Chernograd() : CP_DinosaurBase("CHERNOGRAD", 500, 500, 50, 150, 125, 130, false, true, false, false, "images/CHERNOGRAD") {};
};

class CP_Cyberpunk2077 : public CP_DinosaurBase {
public:
	CP_Cyberpunk2077() : CP_DinosaurBase("Cyberpunk 2077", 250, 250, 50, 150, 110, 115, false, true, false, false, "images/Cyberpunk") {};
};

class CP_AlanWake2 : public CP_DinosaurBase {
public:
	CP_AlanWake2() : CP_DinosaurBase("Alan Wake 2", 300, 300, 50, 150, 105, 120, false, true, false, false, "images/AlanWake2") {};
};