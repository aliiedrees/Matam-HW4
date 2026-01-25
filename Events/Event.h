#pragma once
#include <string>
#include <vector>
#include <memory>

using namespace std;
class Player;
class Event {
    protected:
    virtual string apply(Player& player);
    public:
    virtual string getDescription() const = 0;
    virtual string applyEvent(Player& player) {return apply(player);}
};
class Encounter :public Event {
protected:
    string type;
    int combatPower;
    int loot;
    int damage;
public:
    Encounter() = default;
    Encounter(string  type , int power,  int loot,  int damage)
    :type(type), combatPower(power), loot(loot), damage(damage){}

    virtual string apply(Player& player) ;
    virtual int getCombatPower() const;
    virtual int getLoot() const;
    virtual int getDamage() const;
    virtual void setCombatPowers(int plus) const;
    virtual string getName() const;
    virtual bool isPack() const {return false;}

};
class Snail : public Encounter {
public:
    Snail():Encounter("Snail",5,2,10){}
    string getName() const override;
    string getDescription() const override{
        return "Snail (power 5, loot 2, damage 10)";
    }
};
class Slime :public Encounter {
public:
    Slime():Encounter("Slime",12,5,25){}
    string getName() const override;
    string getDescription() const override{
        return "Slime (power 12, loot 5, damage 25)";
    }
};
class Balrog :public Encounter {
public:
    Balrog():Encounter("Balrog",15,100,9001){}
    string getName() const override;
    void setCombatPowers(int plus) const override;  
    string getDescription() const override{
        return "Balrog (power " + to_string(combatPower) + ", loot 100, damage 9001)";
    } 
    string applyEvent(Player& player) override {
        string outcome = Encounter::apply(player);
        this->setCombatPowers(2);
        return outcome;   
    }
};
class Pack :public Encounter {
    vector<unique_ptr<Encounter>> monsters;
    int size;

    public:
    Pack() = default;
    string getDescription() const override;
    string applyEvent(Player& player) override;
    string getName() const override;
    bool isPack() const override {return true;};
    void applyBalrogCombatPower(std::vector<std::unique_ptr<Encounter>>& monsters);
    static std::unique_ptr<Pack> createPack(std::vector<std::unique_ptr<Encounter>> monsters, int size);
};
class SolarEclipse:public Event {
    string applyEvent(Player& player) override;
    string getDescription() const override{return "SolarEclipse";}

};
class PotionsMerchant:public Event {
    string applyEvent(Player& player) override;
    string getDescription() const override{return "PotionsMerchant";}
};

