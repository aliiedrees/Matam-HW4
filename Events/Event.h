#pragma once
#include <string>
using namespace std;
class Player;
class Event {
    protected:
    virtual string apply(Player& player);
    public:
    virtual string getDescription() const;
    virtual string applyEvent(Player& player) {return apply(player);}
    static std::vector<std::unique_ptr<Event>> eventList;
};
class Monsters :public Event {
    public:
    Monsters() = default;
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
    virtual bool isPack() const {return false;}
    string type;
    int CombatPower;
    int Loot;
    int Damage;
};
class Snail : public Monsters {
public:
    Snail():Monsters("Snail",5,2,10){}
    string getName() const override;
    string getDescription() const override{
        return "Snail (power 5, loot 2, damage 10)";
    }
};
class Slime :public Monsters {
public:
    Slime():Monsters("Slime",12,5,25){}
    string getName() const override;
    string getDescription() const override{
        return "Slime (power 12, loot 5, damage 25)";
    }
};
class Barlog :public Monsters {
public:
    Barlog():Monsters("Balrog",15,100,9001){}
    string getName() const override;
    void setCombatPowers(int plus) const override;  
    string getDescription() const override{
        return "Barlog (power " + to_string(CombatPower) + ", loot 100, damage 9001)";
    } 
    string applyEvent(Player& player) override {
        string outcome = Monsters::apply(player);
        this->setCombatPowers(2);
        return outcome;   
    }
};
class Pack :public Monsters {
    vector<unique_ptr<Monsters>> monsters;
    int size;

    public:
    Pack() = default;
    string getDescription() const override;
    string applyEvent(Player& player) override;
    string getName() const override;
    bool isPack() const override {return true;};
    void applyBalrogCombatPower(std::vector<std::unique_ptr<Monsters>>& monsters);
    static std::unique_ptr<Pack> createPack(std::vector<std::unique_ptr<Monsters>> monsters) {
        auto pack = std::make_unique<Pack>();
        for (auto& monster : monsters) {
            pack->addMonster(std::move(monster));
        }
        return pack;
    }
        void addMonster(std::unique_ptr<Monsters> monster) {
        monsters.push_back(std::move(monster));
    }
};
class SolarEclipse:public Event {
    string applyEvent(Player& player) override;
    string getDescription() const override{return "SolarEclipse";}

};
class PotionsMerchant:public Event {
    string applyEvent(Player& player) override;
    string getDescription() const override{return "PotionsMerchant";}
};

