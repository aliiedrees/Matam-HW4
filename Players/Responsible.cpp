#include <string>
#include "Player.h"
#include "Character.h"
#include "Event.h"
#include "Utilities.h"
using std::string;
class player;
string Responsible::getType() const {
    return "Responsible";
}

string Responsible::potionsMerchant(Player& player) {
    int currentHP = player.getHealthPoints();
    int currentCoins = player.getCoins();
    int potionsAmmount = 0;
    while (currentHP + 10 * potionsAmmount < player.getMaxHealthPoints() && potionsAmmount * 5 <= currentCoins){
        potionsAmmount++;
    }
    potionsAmmount = (potionsAmmount * 5 ) > currentCoins ? potionsAmmount - 1 : potionsAmmount;
    player.setCoins(currentCoins - potionsAmmount * 5);
    player.setHealthPoints(currentHP + potionsAmmount * 10);
    return getPotionsPurchaseMessage(player, potionsAmmount);
}
