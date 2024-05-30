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
        : size{ 10 }, speedGrowth{ _speedGrowth }, full{ _full }, hydr{ _hydr }, clean{ _clean }, maxSize{ 20 }, maxFull{ 200 }, maxHydr{ 200 }, maxClean{ 200 } {}

    void live();

    bool isDead() {return size == 0}

    bool isSuccess() {return size >= maxSize;}

    void catGrow();

    void increaseSize() {if (size < maxSize) size += speedGrowth;}

    void decreaseSize() {if (size > 0) size -= speedGrowth;}

    void increaseFull(int value);

    void decreaseFull(float value) { if (full > 0) full -= value; }

    void increaseHydr(int value);

    void decreaseHydr(float value) {if (hydr > 0) hydr -= value;}

    void increaseClean(int value);

    void decreaseClean(float value) {if (clean > 0) clean -= value;}

    int getSize() const { return size; }
    int getMaxSize() const { return maxSize; }
    float getFull() const { return full; }
    int getMaxFull() const { return maxFull; }
    float getHydr() const { return hydr; }
    int getMaxHydr() const { return maxHydr; }
    float getClean() const { return clean; }
    int getMaxClean() const { return maxClean; }
};




