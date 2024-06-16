#include "Dino.h"


Dino::Dino(int dstr, int ddex, int dinte) {
    str = dstr;
    dex = ddex;
    inte = dinte;
}


DinoStr::DinoStr(int dstr, int ddex, int dinte) : Dino(dstr, ddex, dinte) {
    str = dstr;
    dex = ddex;
    inte = dinte;
    type = 1;
    hp = 100;
    status = 1;
}
int DinoStr::gethp() { return hp; }
void DinoStr::sethp(int n) { hp = n; }
int DinoStr::damage(int place) {
    if (place == 1) {
        return 2 * str;
    }
    if (place == 2) {
        return dex;
    }
    if (place == 3) {
        return inte;
    }
}


DinoDex::DinoDex(int dstr, int ddex, int dinte) : Dino(dstr, ddex, dinte) {
    str = dstr;
    dex = ddex;
    inte = dinte;
    type = 2;
    hp = 100;
    status = 1;
}
int DinoDex::gethp() { return hp; }
void DinoDex::sethp(int n) { hp = n; }
int DinoDex::damage(int place) {
    if (place == 1) {
        return str;
    }
    if (place == 2) {
        return 2 * dex;
    }
    if (place == 3) {
        return inte;
    }
}

DinoInt::DinoInt(int dstr, int ddex, int dinte) : Dino(dstr, ddex, dinte) {
    str = dstr;
    dex = ddex;
    inte = dinte;
    type = 3;
    hp = 100;
    status = 1;
}
int DinoInt::gethp() { return hp; }
void DinoInt::sethp(int n) { hp = n; }
int DinoInt::damage(int place) {
    if (place == 1) {
        return str;
    }
    if (place == 2) {
        return dex;
    }
    if (place == 2) {
        return 2 * inte;
    }
}

