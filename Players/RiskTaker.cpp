#include <memory>
#include <string>
#include "Player.h"
#include "Character.h"
#include "Event.h"
#include "Utilities.h"
using std::string;
class player;
string RiskTaker::getType() const {
    return "RiskTaker";
}

string RiskTaker::potionsMerchant(Player& player) {
    int currentHP = player.getHealthPoints();
    int currentCoins = player.getCoins();
    if (currentHP < 50 && currentCoins > 5){
        player.setCoins(currentCoins - 5);
        player.setHealthPoints(currentHP + 10);
        return getPotionsPurchaseMessage(player, 1);
    }
    return getPotionsPurchaseMessage(player, 0);
}

