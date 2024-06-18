#pragma once
#include <iostream>


std::string charToFName(char n) {
    switch (n) {
        case 'b':
            return "brachi-2.png";
        case 'd':
            return "diplo-2.png";
        case 's':
            return "stego-2.png";
        case 'r':
            return "rex-2.png";
        case 't':
            return "trice-2.png";
        default:
            return "";
    }
}

std::string toFName(int n) {
    switch (n) {
        case 0:
            return "brachi.png";
        case 1:
            return "diplo.png";
        case 2:
            return "stego.png";
        case 3:
            return "rex.png";
        case 4:
            return "trice.png";
        default:
            return "";
    }
}

std::string toName(int n) {
    switch (n) {
        case 0:
            return "Brachiosaurus";
        case 1:
            return "Diplodocus";
        case 2:
            return "Stegosaurus";
        case 3:
            return "Tyrannosaurus";
        case 4:
            return "Triceratops";
        default:
            return "";
    }
}

std::string toCost(int n) {
    switch (n) {
        case 0:
            return "184";
        case 1:
            return "174";
        case 2:
            return "184";
        case 3:
            return "184";
        case 4:
            return "146";
        default:
            return "";
    }
}

std::string toSTR(int n) {
    switch (n) {
        case 0:
            return "STR: 15";
        case 1:
            return "STR: 20";
        case 2:
            return "STR: 15";
        case 3:
            return "STR: 30";
        case 4:
            return "STR: 20";
        default:
            return "";
    }
}

std::string toINT(int n) {
    switch (n) {
        case 0:
            return "INT: 30";
        case 1:
            return "INT: 24";
        case 2:
            return "INT: 12";
        case 3:
            return "INT: 12";
        case 4:
            return "INT: 15";
        default:
            return "";
    }
}

std::string toDEX(int n) {
    switch (n) {
        case 0:
            return "DEX: 12";
        case 1:
            return "DEX: 17";
        case 2:
            return "DEX: 30";
        case 3:
            return "DEX: 15";
        case 4:
            return "DEX: 18";
        default:
            return "";
    }
}

std::string toInfo(char n) {
    switch (n) {
        case 't':
            return "Triceratops   STR: 20  DEX: 18  INT: 15";
        case 'r':
            return "Tyrannosaur   STR: 30  DEX: 15  INT: 12";
        case 's':
            return "Stegosaurus   STR: 15  DEX: 30  INT: 12";
        case 'd':
            return "Diplodocus   STR: 20  DEX: 17  INT: 24";
        case 'b':
            return "Brachiosaurus   STR: 15  DEX: 12  INT: 30";
        case 'n':
            return "";
        default:
            return "NAME_DISPLAY_ERROR";
    }
}
