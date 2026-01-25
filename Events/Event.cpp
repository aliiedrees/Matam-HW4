#include "Event.h"
#include "Utilities.h"
#include <string>
#include "../Players/Job.h"
#include "../Players/Character.h"
#include "../Players/Player.h"
using namespace std;
string Encounter::apply(Player& player) {
    if(this->getCombatPower() >= player.getCombatPower()) {
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

int Encounter::getLoot() const {
    return this->loot;
}

int Encounter::getCombatPower() const {

    return this->combatPower;
}

int Encounter::getDamage() const {
    return this->damage;
}

string SolarEclipse::applyEvent(Player& player) {
    return player.getJob()->solarEclipse(player);
}

string PotionsMerchant::applyEvent(Player& player) {
    return player.getCharacter()->potionsMerchant(player);
}

void Pack::applyBalrogCombatPower(std::vector<std::unique_ptr<Encounter>>& monsters) {
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
    return "Pack of " + to_string(this->size) + " members (power " + to_string(this->combatPower) + 
    ", loot " + to_string(loot) + ", damage " + to_string(damage) + ")";
}
    
string Pack::applyEvent(Player &player) {
    std::string outcome = apply(player);
    applyBalrogCombatPower(this->monsters);
    return outcome;
}

std::unique_ptr<Pack> Pack::createPack(std::vector<std::unique_ptr<Encounter>> monsters, int size){
    auto pack = std::make_unique<Pack>();
    pack->monsters = std::move(monsters);
    pack->size = size;
    return pack;
}
