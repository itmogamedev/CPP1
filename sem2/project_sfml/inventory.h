#pragma once
#include <vector>
#include "dino.h"

class Inventory {
	std::vector<int> inv = {0,0,0};
	int gold = 300;
public:
	void push(Rex d) {
		inv[0]++;
	}

	void push(Raptor d) {
		inv[1]++;
	}

	void push(Tricer d) {
		inv[2]++;
	}

	std::vector<int> getInv() {
		return inv;
	}

	int getRex() {
		return inv[0];
	}

	int getRaptor() {
		return inv[1];
	}

	int getTricer() {
		return inv[2];
	}

	int getGold() {
		return gold;
	}


	void shop_rex() {
		if (gold >= 100) {
			inv[0]++;
			gold -= 100;
		}
	}

	void shop_raptor() {
		if (gold >= 100) {
			inv[1]++;
			gold -= 100;
		}
	}

	void shop_tricer() {
		if (gold >= 100) {
			inv[2]++;
			gold -= 100;
		}
	}

	void pop_rex() {
		inv[0]--;
	}

	void pop_raptor() {
		inv[1]--;
	}

	void pop_tricer() {
		inv[2]--;
	}

	void push_rex() {
		inv[0]++;
	}

	void push_raptor() {
		inv[1]++;
	}

	void push_tricer() {
		inv[2]++;
	}

	void push_rex(int i) {
		inv[0] += i;
	}

	void push_raptor(int i) {
		inv[1] += i;
	}

	void push_tricer(int i) {
		inv[2] += i;
	}

	void setGold(int i) {
		gold += i;
	}

	void setRex(int i) {
		inv[0] = i;
	}

	void setRaptor(int i) {
		inv[1] = i;
	}

	void setTricer(int i) {
		inv[2] = i;
	}
};