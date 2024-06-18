enum Terrain {
    Plain, River, Mountain
};

class Dino {
public:
    int STRENGTH;
    int DEXTERITY;
    int INTELLIGENCE;
    std::string ULTY;
    float HP = 100;
    std::string name;
    int cost;
public:
    virtual int damage(Terrain terrain) = 0;
};

class Kira : public Dino {
public:
    int cost = 100;

    Kira() {
        STRENGTH = 10;
        DEXTERITY = 15;
        INTELLIGENCE = 10;
        cost = 100;
        HP = 100;
        name = "Kira";
    }

    int damage(Terrain terrain) {
        return terrain == Terrain::Mountain ?
               2 * INTELLIGENCE :
               terrain == Terrain::River ?
               DEXTERITY :
               STRENGTH;
    }

};

class Cole : public Dino {
public:
    int cost = 100;

    Cole() {
        STRENGTH = 10;
        DEXTERITY = 10;
        INTELLIGENCE = 15;
        cost = 100;
        HP = 100;
        name = "Cole";
    }

    int damage(Terrain terrain) {
        return terrain == Terrain::River ?
               2 * DEXTERITY :
               terrain == Terrain::Plain || terrain == Terrain::Mountain ?
               DEXTERITY :
               STRENGTH;
    }

};


class Mono : public Dino {
public:
    int cost = 100;

    Mono() {

        STRENGTH = 15;
        DEXTERITY = 10;
        INTELLIGENCE = 15;
        cost = 100;
        HP = 100;
        name = "Mono";
    }

    int damage(Terrain terrain) {
        return terrain == Terrain::Plain ?
               2 * STRENGTH :
               terrain == Terrain::River ?
               DEXTERITY :
               INTELLIGENCE;
    }
};
