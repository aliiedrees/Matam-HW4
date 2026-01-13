#include <memory>
#include <string>
#include "Player.h"
#include "Character.h"
#include "Event.h"
#include "Utilities.h"
using std::string;
class player;
string Responsable::getType() const {
    return "Responsable";
}

string Responsable::PotionsMerchant(Player& player) {
    int amount = 0;
    while(player.getHealthPoints() <= player.getMaxHealthPoints() && player.getCoins() >= 5) {
        player.setHealthPoints(player.getHealthPoints() + 10);
        player.setCoins(player.getCoins() - 5);
        amount++;
    }
    if(player.getHealthPoints() > player.getMaxHealthPoints()) {
        player.setHealthPoints(player.getMaxHealthPoints());
    }
    return getPotionsPurchaseMessage(player,amount);
}
