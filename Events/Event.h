#pragma once
#include <string>
using namespace std;
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