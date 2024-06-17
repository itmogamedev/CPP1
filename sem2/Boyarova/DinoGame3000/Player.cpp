#pragma once
#include "Player.h"

void Player::setCoins(int A) {
	coins = coins + A;
}
int Player::getCoins() {
	return coins;
}
void Player::buy(int A) {
	coins = coins - A;
}

std::vector <bool> Player::getInfo() {
	return Dinos;
}
void Player::setDino(std::vector <bool> B) {
	Dinos = B;
}

void Player:: LoadGame(const std::string& filename) {
	std::ifstream file(filename);
	Dinos.clear();
	if (file.is_open()) {
		file >> coins;
		for (int i = 0; i < 4; i++) {
			bool s;
			file >> s;
			Dinos.push_back(s);
		}
	}
}
void Player::SaveGame(const std::string& filename) {
	std::remove("data.txt");
	std::ofstream file(filename, std::ios::trunc);
	if (file.is_open()) {
		file << coins << std::endl;
		for (int i = 0; i < Dinos.size(); i++) {
			bool s = Dinos.at(i);
			file << s << std::endl;
		}
	}
}