#pragma once

class Cat {
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
    int joy;
    const int maxJoy;

public:
    Cat(int _speedGrowth, int _full, int _hydr, int _clean, int _joy)
        : size{ 10 }, speedGrowth{ _speedGrowth }, full{ _full }, hydr{ _hydr }, clean{ _clean }, joy{ _joy },
        maxSize{ 30 }, maxFull{ 1000 }, maxHydr{ 1000 }, maxClean{ 1000 }, maxJoy{ 1000 } {}

    void live() {
        catGrow();
        decreaseFull(1);
        decreaseHydr(1);
        decreaseClean(1);
        decreaseJoy(1);
    }

    bool isDead() {
        return size == 0 || clean == 0 || hydr == 0 || joy == 0;
    }

    bool isSuccess() {
        return size >= maxSize;
    }

    void catGrow() {
        if (full >= maxFull) {
            full = 50;
            increaseSize();
        }
        else if (full == 0) {
            full = 99;
            decreaseSize();
        }
    }

    void increaseSize() { size += speedGrowth; }
    void decreaseSize() { if (size > 0) size -= speedGrowth; }

    void increaseFull(int value) { if (full < maxFull) full += value; }
    void decreaseFull(int value) { if (full > 0) full -= value; }

    void increaseHydr(int value) { if (hydr < maxHydr) hydr += value; }
    void decreaseHydr(int value) { if (hydr > 0) hydr -= value; }

    void increaseClean(int value) { if (clean < maxClean) clean += value; }
    void decreaseClean(int value) { if (clean > 0) clean -= value; }

    void increaseJoy(int value) { if (joy < maxJoy) joy += value; }
    void decreaseJoy(int value) { if (joy > 0) joy -= value; }

    int getSpeedGrowth() const { return speedGrowth; }
    int getSize() const { return size; }
    int getMaxSize() const { return maxSize; }
    int getFull() const { return full; }
    int getMaxFull() const { return maxFull; }
    int getHydr() const { return hydr; }
    int getMaxHydr() const { return maxHydr; }
    int getClean() const { return clean; }
    int getMaxClean() const { return maxClean; }
    int getJoy() const { return joy; }
    int getMaxJoy() const { return maxJoy; }
};
