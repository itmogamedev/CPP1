#include "cat.h"
#include <iostream>

void Cat::live()
{
    catGrow();
    decreaseFull(0.1);  // «амедл€ем скорость падени€ характеристик
    decreaseHydr(0.1);
    decreaseClean(0.1);
}

void Cat::catGrow()
{
    if (full >= maxFull) {
        full = 50;
        increaseSize();
    }
    else if (full <= 0) {
        full = 99;
        decreaseSize();
    }
    else if (hydr <= 0) { 
        hydr = 99;
        decreaseSize();
    }
    else if (clean <= 0) {
        clean = 99;
        decreaseSize();
    }
}

void Cat::increaseFull(int value)
{
    if (full + value < maxFull) { full += value; }
    else {full = maxFull;}
}

void Cat::increaseHydr(int value)
{
    if (hydr + value < maxHydr) { hydr += value; }
    else {hydr = maxHydr;}
}

void Cat::increaseClean(int value)
{
    if (clean + value < maxClean) { clean += value; }
    else {clean = maxClean;}
}
