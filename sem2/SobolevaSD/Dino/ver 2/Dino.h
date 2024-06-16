#pragma once
#include <string>

class Dino
{
public:
	int hp;
	int type;
	int inte, str, dex;
    int status;
	Dino(int _inte, int _str, int _dex);
	virtual int damage(int place) = 0;
	//Dino(std::string _line);
};

class DinoStr : public Dino {
public:
    DinoStr(int dstr, int ddex, int dinte) : Dino(dstr, ddex, dinte);
    int gethp();
    void sethp(int n);
    int damage(int place);
};

class DinoDex : public Dino {
public:
    DinoDex(int dstr, int ddex, int dinte) : Dino(dstr, ddex, dinte);
    int gethp();
    void sethp(int n);
    int damage(int place);
};

class DinoInt : public Dino {
public:
    DinoInt(int dstr, int ddex, int dinte) : Dino(dstr, ddex, dinte);
    int gethp();
    void sethp(int n);
    int damage(int place);
};

