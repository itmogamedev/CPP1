#pragma once


class Animal {
private:
	int size;
	const int maxSize;
	int speedGrowth;
	int full;
	const int maxFull;
	int hydr;
	const int maxHydr;
	int clean;
	const int maxClean;

public:
	Animal(const int _speedGrowth,
		const int _full,
		const int _hydr,
		const int _clean
	) : size{ 5 },
		speedGrowth{ _speedGrowth },
		full{ _full },
		hydr{ _hydr },
		clean{ _clean },
		maxSize{ 100 },
		maxFull{ 50 },
		maxHydr{ 150 },
		maxClean{ 150 }
	{

	}

	void live() {
		catGrow();

		decreaseFull(1);
		decreaseHydr(1);
		decreaseClean(1);
	}

	bool isDead() {
		return 0 == size or 0 == clean or 0 == hydr;
	}

	bool isSuccess() {
		return maxSize <= size;
	}

	void catGrow() {
		if (maxFull <= full) {
			full = 25;
			increaseSize();
		}
		else if (0 >= full) {
			full = 49;
			decreaseSize();
		}
	}

	void increaseSize() { if (size < maxSize) size += speedGrowth; }
	void decreaseSize() { if (size > 0) size -= speedGrowth; }

	void increaseFull(const int value) { full = std::min(full + value, maxFull); }
	void decreaseFull(const int value) { if (full > 0) full -= value; }

	void increaseHydr(const int value) { hydr = std::min(hydr + value, maxHydr); }
	void decreaseHydr(const int value) { if (hydr > 0)  hydr -= value; }

	void increaseClean(const int value) { clean = std::min(clean + value, maxClean); }
	void decreaseClean(const int value) { if (clean > 0)  clean -= value; }

	const int getSpeedGrowth() { return speedGrowth; }
	const int getSize() { return size; }
	const int getMaxSize() { return maxSize; }
	const int getFull() { return full; }
	const int getMaxFull() { return maxFull; }
	const int getHydr() { return hydr; }
	const int getMaxHydr() { return maxHydr; }
	const int getClean() { return clean; }
	const int getMaxClean() { return maxClean; }
};