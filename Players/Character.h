#pragma once
#include <string>
using namespace std;
class Player;
class Character {
public:
    virtual string getType() const = 0;
    virtual string potionsMerchant(Player& player) = 0;
    virtual ~Character() = default;
protected:
    Character() = default;
};

class Responsible :public Character {
    public:
    string potionsMerchant(Player& player) override;
    string getType() const override;


    ~Responsible() override = default;
    Responsible() = default;
};

class RiskTaker :public Character {
    public:
    string potionsMerchant(Player& player) override;
    string getType() const override;

    ~RiskTaker() override = default;
    RiskTaker() = default;
};
