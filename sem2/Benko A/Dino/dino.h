#pragma once

int LIM;
int cD;

class Dino {
protected:
    int st = rand() % 8 + 10;
    int ag = rand() % 10 + 10;
    int in = rand() % 20 + 5;
public:
    virtual double damage() = 0;
};

class DinoStr : public Dino {
public:
    double damage() override {
        cD = cD + st * 1.1;
        return cD;
    }
};

class DinoDex : public Dino {
public:
    double damage() override {
        cD = cD + ag * 1.3;
        return cD;
    }
};

class DinoInt : public Dino {
public:
    double damage() override {
        cD = cD + in * 1.5;
        return cD;
    }
};

class Player {
public:
    double damage(Dino* dino) {
        return dino->damage();
    }
};