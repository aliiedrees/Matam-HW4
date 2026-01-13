#include <memory>
#include <string>
#include "Player.h"
#include "Character.h"
#include "Event.h"
#include "Utilities.h"
using std::string;
class player;
string RiskMaker::getType() const {
    return "RiskMaker";
}

string RiskMaker::PotionsMerchant(Player& player) {
    int amount = 0;
    if(player.getHealthPoints() < 50 && player.getCoins() >= 5) {
        player.setHealthPoints(player.getHealthPoints() + 10);
        player.setCoins(player.getCoins() - 5);
        amount++;
    }
   return getPotionsPurchaseMessage(player,amount);
}

