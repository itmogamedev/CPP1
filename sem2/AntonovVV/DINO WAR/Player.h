#ifndef HELLOSFML_PLAYER_H
#define HELLOSFML_PLAYER_H
#include <bits/stdc++.h>

class Player {
public:
    std :: string nickname;
    int balance = 300;
    std :: set <std :: string> pull;
    std :: vector <std :: string> vecPull;
};
class Enemy : public Player
{
};
inline Player player;

#endif //HELLOSFML_PLAYER_H
