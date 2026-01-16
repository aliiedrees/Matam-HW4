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
    virtual string playEvent(Player& player) const;
};

class Encounter : public Event {
    
    public:
    virtual ~Encounter() = 0;
    virtual unsigned int getCombatPower() const {this->combatPower;};
    virtual unsigned int getLoot() const {this->loot;};
    virtual unsigned int getDamage() const {this->damage;};
    protected:
    unsigned int combatPower;
    unsigned int loot;
    unsigned int damage;
    Encounter(unsigned int combatPower, unsigned int loot, unsigned int damage);
    Encounter() = default;
};

class Snail : public Encounter {
    static const unsigned int combatPower = 5;
    static const unsigned int loot = 2;
    static const unsigned int damage = 10;

    public:
    Snail() : Encounter(combatPower, loot, damage){}
    ~Snail() = default;
    string getDescription() const override{
        return "Snail (power 5, loot 2, damage 10)";
    }
    string playEvent(Player& player) const override;
};

class Slime : public Encounter {
    static const unsigned int combatPower = 12;
    static const unsigned int loot = 5;
    static const unsigned int damage = 25;
    public:
    Slime() : Encounter(combatPower, loot, damage){}
    ~Slime() = default;
    string getDescription() const override{
        return "Slime (power 12, loot 5, damage 25)";
    }
    string playEvent(Player& player) const override;
};

class Barlog : public Encounter {
    static const unsigned int combatPower = 15;
    static const unsigned int loot = 100;
    static const unsigned int damage = 9001;
    public:
    Barlog() : Encounter(combatPower, loot, damage){}
    ~Barlog() = default;
    string getDescription() const override{
        return "Barlog (power 15, loot 100, damage 9001)";
    }
    string playEvent(Player& player) const override;
};

class Pack : public Encounter {
    vector<unique_ptr<Encounter>> monsters;
    int size;

    public:
    Pack(int size, vector<unique_ptr<Encounter>> monsters) : size(size), monsters(std::move(monsters)){}
    ~Pack() = default;
    string getDescription() const override;
    unsigned int getCombatPower() const override;
    unsigned int getLoot() const override;
    unsigned int getDamage() const override;
    string playEvent(Player& player) const override;
};

class SolarEclipse : public Event {
    string getDescription() const override{return "SolarEclipse";}
    string playEvent(Player& player) const override;
};

class PotionsMerchant : public Event {
    string getDescription() const override{return "PotionsMerchant";}
    string playEvent(Player& player) const override;
};

/*
class Player;
class Event {

    public:
    virtual string apply(Player& player);
    virtual int getCombatPower(Player& player) const;
};
class Monsters :public Event {
    public:
    Monsters(std::string  type , int power,  int loot,  int damage)
        :type(std::move(type)) {
        CombatPower = power;
        Loot = loot;
        Damage = damage;
    }
    virtual string apply(Player& player) ;
    virtual int getCombatPower() const;
    virtual int getLoot() const;
    virtual int getDamage() const;
    virtual void setCombatPowers(int plus) const;
    virtual string getName() const;
    string type;
    int CombatPower;
    int Loot;
    int Damage;
};
class Snail : public Monsters {
    Snail():Monsters("Snail",5,2,10){}
    string getName() const override;
};
class Slime :public Monsters {
    Slime():Monsters("Slime",12,5,25){}
    string getName() const override;
};
class Barlog :public Monsters {
Barlog():Monsters("Balrog",15,100,9001){}
    string getName() const override;
    void setCombatPowers(int plus) const override;
    string apply(Player& player) override ;
};
class Pack :public Monsters {
Monsters* monsters;
    string apply(Player& player) override;
    int getCombatPower() const override;
    int getLoot() const override;
    int getDamage() const override;
    string getName() const override;
};
class SolarEclipse:public Event {
    string apply(Player& player) override;
};
class PotionsMerchant:public Event {
    string apply(Player& player) override;
};
*/