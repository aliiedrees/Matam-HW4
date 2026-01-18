#pragma once
#include <string>
using namespace std;
class Player;
class Character {
    string type;
public:
    virtual string getType() const;
    virtual string potionsMerchant(Player& player);
};

class Responsible :public Character {
    string potionsMerchant(Player& player) override;
    string getType() const override;
};

class RiskTaker :public Character {
    string potionsMerchant(Player& player) override;
    string getType() const override;
};
