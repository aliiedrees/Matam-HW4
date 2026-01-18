#pragma once
#include <string>
using namespace std;
#include "Player.h"

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

class RiskMaker :public Character {
    string potionsMerchant(Player& player) override;
    string getType() const override;
};
