#pragma once
#include "Resourses.h"
#include "Classes.h"
// прототипы функции
bool DisplayDinos(sf::Color bg_color, std::vector<Dino*>& dinos, bool isShop, bool isGame, std::vector<Dino*>& myTeam = emptyvec);
void Menu(sf::Font& font, sf::Color& bg_color);
void GamePlay(sf::Font& font, sf::Color& bg_color);
void AfterFight(bool isWin);
void LoadStats(Player& player);
void SaveStats(Player& player);
void LoadTextures(std::unordered_map<std::string, sf::Texture>& Textures);
void CreateTexture(std::string name);
void CreateSound(std::string name,bool isLoop,float volume);
void MuteAll();