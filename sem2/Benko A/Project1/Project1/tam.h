#pragma once


class Tam {
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
	Tam(int _speedGrowth,
		int _full,
		int _hydr,
		int _clean
	) : size{ 10 },
		speedGrowth{ _speedGrowth },
		full{ _full },
		hydr{ _hydr },
		clean{ _clean },
		maxSize{ 100 },
		maxFull{ 1000 },
		maxHydr{ 1000 },
		maxClean{ 1000 }
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
		if (full >= maxFull) {
			full = maxFull / 3 * 2;
			increaseSize();
		}
		if (full <= 0) {
			full = 1000;
			decreaseSize();
		}
		if (hydr >= maxHydr) {
			hydr = maxHydr;
		}
		if (hydr <= 0) {
			hydr = 0;
			decreaseSize();
		}
		if (clean >= maxClean) {
			clean = maxClean;
		}
		if (clean <= 0) {
			clean = 0;
			decreaseSize();
		}
	}


	void increaseSize() { size += speedGrowth; }
	void decreaseSize() { if (size > 0) size -= speedGrowth; }

	void increaseFull(const int value) { if (full < maxFull) full += value; }
	void decreaseFull(const int value) { if (full > 0) full -= value; }

	void increaseHydr(const int value) { if (hydr < maxHydr) hydr += value; }
	void decreaseHydr(const int value) { if (hydr > 0)  hydr -= value; }

	void increaseClean(const int value) { if (clean < maxClean) clean += value; }
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