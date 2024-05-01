#pragma once

class Cat {
private:
    int size;
    const int maxSize;
    float speedGrowth;
    float full;
    const int maxFull;
    float hydr;
    const int maxHydr;
    float clean;
    const int maxClean;

public:
    Cat(float _speedGrowth, float _full, float _hydr, float _clean)
        : size{ 10 }, speedGrowth{ _speedGrowth }, full{ _full }, hydr{ _hydr }, clean{ _clean }, maxSize{ 200 }, maxFull{ 200 }, maxHydr{ 200 }, maxClean{ 200 } {}

    void live() {
        catGrow();
        decreaseFull(0.1);  // «амедл€ем скорость падени€ характеристик
        decreaseHydr(0.1);
        decreaseClean(0.1);
    }

    bool isDead() {
        return size == 0 || clean == 0 || hydr == 0;
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

    void increaseSize() {
        if (size < maxSize) size += speedGrowth;
    }

    void decreaseSize() {
        if (size > 0) size -= speedGrowth;
    }

    void increaseFull(int value) {
        if (full < maxFull) full += value;
    }

    void decreaseFull(float value) {
        if (full > 0) full -= value;
    }

    void increaseHydr(int value) {
        if (hydr < maxHydr) hydr += value;
    }

    void decreaseHydr(float value) {
        if (hydr > 0) hydr -= value;
    }

    void increaseClean(int value) {
        if (clean < maxClean) clean += value;
    }

    void decreaseClean(float value) {
        if (clean > 0) clean -= value;
    }

    int getSize() const { return size; }
    int getMaxSize() const { return maxSize; }
    float getFull() const { return full; }
    int getMaxFull() const { return maxFull; }
    float getHydr() const { return hydr; }
    int getMaxHydr() const { return maxHydr; }
    float getClean() const { return clean; }
    int getMaxClean() const { return maxClean; }
};




