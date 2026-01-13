#pragma once
#include <string>
using namespace std;
class Player;
class Character {
    string type;
public:
   virtual string getType() const;
    virtual string PotionsMerchant(Player& player);
};

class Responsable :public Character {
    string PotionsMerchant(Player& player) override;
    string getType() const override;
};

class RiskMaker :public Character {
    string PotionsMerchant(Player& player) override;
    string getType() const override;
};
