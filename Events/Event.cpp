#include "Event.h"
#include "Utilities.h"
#include <string>
#include "../Players/Job.h"
#include "../Players/Character.h"
#include "../Players/Player.h"
using namespace std;
string Monsters::apply(Player& player) {
    if(this->getCombatPower() >= player.getCombatPoawer()) {
        player.setHealthPoints(player.getHealthPoints() - this->getDamage());
    return getEncounterLostMessage(player,this->getDamage());
    }
     {
        player.setCoins(player.getCoins() + this->getLoot());
        player.buffLevel();
    }
    if(player.getJob()->checkIfRnaged() == false) {
        player.setHealthPoints(player.getHealthPoints() - 10);
    }
    if (player.getHealthPoints() <= 0){
        player.setHealthPoints(0);
        player.wasted();
    }
    return getEncounterWonMessage(player,this->getLoot());
}

int Monsters::getLoot() const {
    return this->Loot;
}

int Monsters::getCombatPower() const {

    return this->CombatPower;
}

int Monsters::getDamage() const {
    return this->Damage;
}

string SolarEclipse::applyEvent(Player& player) {
    return player.getJob()->solarEclipse(player);
}

string PotionsMerchant::applyEvent(Player& player) {
    return player.getCharacter()->potionsMerchant(player);
}

void Pack::applyBalrogCombatPower(std::vector<std::unique_ptr<Monsters>>& monsters) {
        for (auto& monster : monsters) {
            // Check if it's a "Balrog" and increase its CombatPower
            if (monster->getName() == "Balrog") {
                monster->setCombatPowers(2);
            }

            // If it's a pack, recursively check its members
            if (auto pack = dynamic_cast<Pack*>(monster.get())) {
                applyBalrogCombatPower(pack->monsters);
            }
        }
}

 string Pack::getDescription() const {
    unsigned int totalPower = this->getCombatPower();
    unsigned int totalLoot = this->getLoot();
    unsigned int totalDamage = this->getDamage();

    return "Pack of " + to_string(this->size) + " members (power " + to_string(totalPower) + 
    ", loot " + to_string(totalLoot) + ", damage " + to_string(totalDamage) + ")";
}
    
string Pack::applyEvent(Player &player) {
    std::string outcome = apply(player);
    applyBalrogCombatPower(this->monsters);
    return outcome;
}