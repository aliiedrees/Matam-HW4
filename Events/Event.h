
#pragma once
#include "../Players/Player.h"


class Event {
public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    virtual string getDescription() const;
};

class Encounter : public Event {
    
    public:
    virtual ~Encounter() = 0;
    virtual unsigned int getCombatPower() const;
    virtual unsigned int getLoot() const;
    virtual unsigned int getDamage() const;
    protected:
    unsigned int combatPower;
    unsigned int loot;
    unsigned int damage;
    Encounter(unsigned int combatPower, unsigned int loot, usigned int damage);
}

class Snail : public Encounter {
    static const unsigned int combatPower = 5;
    static const unsigned int loot = 2;
    static const unsigned int damage = 10;

    public:
    Snail() {Encounter(combatPower, loot, damage);}
    ~Snail() = default;
    string getDescription() const override{
        return "Snail (power 5, loot 2, damage 10)";
    }
    unsigned int getCombatPower() const override{return combatPower;}
    unsigned int getLoot() const override{return loot;}
    unsigned int getDamage() const override{return damage;}
}

class Slime : public Encounter {
    static const unsigned int combatPower = 12;
    static const unsigned int loot = 5;
    static const unsigned int damage = 25;
    public:
    Slime() {Encounter(combatPower, loot, damage);}
    ~Slime() = default;
    string getDescription() const override{
        return "Slime (power 12, loot 5, damage 25)";
    }
    unsigned int getCombatPower() const override{return combatPower;}
    unsigned int getLoot() const override{return loot;}
    unsigned int getDamage() const override{return damage;}
}

class Barlog : public Encounter {
    static const unsigned int combatPower = 15;
    static const unsigned int loot = 100;
    static const unsigned int damage = 9001;
    public:
    Barlog() {Encounter(combatPower, loot, damage);}
    ~Barlog() = default;
    string getDescription() const override{
        return "Barlog (power 15, loot 100, damage 9001)";
    }
    unsigned int getCombatPower() const override{return combatPower;}
    unsigned int getLoot() const override{return loot;}
    unsigned int getDamage() const override{return damage;}
}

class Pack : public Encounter {
    Encounter** monsters;
    int size;

    public:
    Pack(int size, Encounter** monsters) : size(size), monsters(monsters);
    ~Pack(){
        for (int i = 0; i < size; i++){
            delete monsters[i];
        }
        delete[] monsters;
    }
    string getDescription() const override;
    unsigned int getCombatPower() const override;
    unsigned int getLoot() const override;
    unsigned int getDamage() const override;
}

class SolarEclipse : public Event {
    string getDescription() const override{return "SolarEclipse";}
}

class PotionsMerchant : public Event {
    string getDescription() const override{return "PotionsMerchant";}
}