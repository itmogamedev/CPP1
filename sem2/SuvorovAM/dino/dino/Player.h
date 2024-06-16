#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <memory>

#include "SFML/Graphics.hpp"

#include "Dino.h"
#include "DinoType.h"

class Player {

public:
    std::vector<Dino*> dinos;
    std::vector<Dino*> selectedDinos;
    int current_balance = 500;

    




    void addDino(Dino* dino) {
        dinos.push_back(dino);

    }

    void deleteDino(Dino* dino) {                                                                      // ERASING DEAD DINOS
        dinos.erase(std::remove(dinos.begin(), dinos.end(), dino), dinos.end());

    }



    void DINO_random_pull() {                                                                          // ENEMY PULL
        for (int i = 0; i < 3; i++) {
            DINO_Stats type = static_cast<DINO_Stats>(rand() % 3);
            DINO_Type dinoType = static_cast<DINO_Type>(rand() % 3);
            switch (dinoType) {
            case STR:
                selectedDinos.push_back(new DinoStr(dinoType));
                break;
            case DEX:
                selectedDinos.push_back(new DinoDex(dinoType));
                break;
            case INT:
                selectedDinos.push_back(new DinoInt(dinoType));
                break;
            default:
                break;
            }
        }
    }

    void attackEnemy(Player& enemy, std::vector<Dino*>& dinosToAttack, Terrain terrain) {               // ATTACK ON ENEMY
        if (dinosToAttack.empty() || selectedDinos.empty()) {
            return;
        }

        Dino* enemyDino = dinosToAttack.back();

        Dino* myDino = selectedDinos.back();
        myDino->triggerAttack();

        int damage = myDino->damage(terrain);

        if (enemyDino->GetDamageFromEnemy(damage)) {
            enemyDino->isDead = true;                                                                  // DEAD
        }
    }



    void DINO_save(const std::string& filename) {
        std::ofstream file(filename, std::ios::trunc);
        if (file.is_open()) {
            file << current_balance << "\n";

            for (const Dino* dino : dinos) {
                file << dino->type << " " << dino->HP << " " << dino->cost << "\n";
            }
            file.close();
        }
        
    }
    
    void DINO_reset() {
        
    }
    

    void DINO_load(const std::string& filename) {                                                       // LOAD DATA
        std::ifstream file(filename);
        if (file.is_open()) {
            dinos.clear();
            std::string balanceLine;
            if (std::getline(file, balanceLine)) {
                current_balance = std::stoi(balanceLine);
            }
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                int type, hp, cost;
                if (iss >> type >> hp >> cost) {
                    DINO_Type dinoType = static_cast<DINO_Type>(type);
                    Dino* dino = nullptr;
                    switch (dinoType) {
                    case Tyrannosaur:
                        dino = new DinoStr(dinoType);
                        break;
                    case Brachiosaur:
                        dino = new DinoDex(dinoType);
                        break;
                    case Triceratops:
                        dino = new DinoInt(dinoType);
                        break;
                    }
                    if (dino) {
                        dino->HP = hp;
                        dino->cost = cost;
                        dinos.push_back(dino);
                    }
                }
            }
            file.close();
        }
    }



};