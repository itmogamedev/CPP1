#ifndef Graphics_h
#define Graphics_h
#define SCRWIDTH 800
#define SCRHEIGHT 300
#include "includes.h"


using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
void menuWindowPrint();
void shopWindowPrint();
void registrationWindowPrint();
void startWindowPrint();
void profileWindowPrint();
void startingBattleWindowPrint();
void battleMenu();
void winnerWindowPrint();
void looserWindowPrint();
void idleAnimation(sf::Sprite &sprite, std::string output);
#endif /* Graphics_h */
