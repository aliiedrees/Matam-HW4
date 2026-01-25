#include "Event.h"
#include "../Utilities.h"
#include <string>
#include "../Players/Job.h"
#include "../Players/Character.h"
#include "../Players/Player.h"
using namespace std;
string Encounter::apply(Player& player) {
    if(this->getCombatPower() >= player.getCombatPower()) {
        if(player.getJob()->checkIfRnaged() == false) {
            player.setHealthPoints(player.getHealthPoints() - 10);
        }
        player.setHealthPoints(player.getHealthPoints() - this->getDamage());
        if (player.getHealthPoints() <= 0){
            player.setHealthPoints(0);
            player.wasted();
        }
        return getEncounterLostMessage(player,this->getDamage());
    }
    player.setCoins(player.getCoins() + this->getLoot());
    player.buffLevel();

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

string SolarEclipse::apply(Player& player) {
    return player.getJob()->solarEclipse(player);
}

string PotionsMerchant::apply(Player& player) {
    return player.getCharacter()->potionsMerchant(player);
}

void Pack::applyBalrogCombatPower(int balrogCounter) {
    this->setCombatPowers(2*balrogCounter);
}

string Pack::getDescription() const {
    return "Pack of " + to_string(this->size) + " members (power " + to_string(this->getCombatPower()) + 
    ", loot " + to_string(this->getLoot()) + ", damage " + to_string(this->getDamage()) + ")";
}
    
string Pack::applyEvent(Player &player) {
    std::string outcome = apply(player);
    applyBalrogCombatPower(this->balrogCounter);
    return outcome;
}

int Pack::getSize() const {
    return this->size;
}

std::unique_ptr<Pack> Pack::createPack(std::vector<std::unique_ptr<Encounter>> monsters, int size){
    auto pack = std::make_unique<Pack>();
    pack->monsters = std::move(monsters);
    int sumLoot = 0, sumPower = 0, sumDamage = 0, balrogCounter = 0;
    for(const auto& monster : pack->monsters) {
       sumLoot += monster->getLoot();
        sumDamage += monster->getDamage();
        sumPower += monster->getCombatPower();
        if(monster->getName() == "Balrog") {
            balrogCounter++;
        }

        if(monster->getName() == "Pack") {
            auto* pack = dynamic_cast<Pack*>(monster.get());
            balrogCounter+=pack->getBalrogCounter();
        }
    }

    pack->combatPower = sumPower;
    pack->damage = sumDamage;
    pack->loot = sumLoot;
    pack->balrogCounter = balrogCounter;
    pack->size = size;
    return pack;
}
void Encounter::setCombatPowers(int plus) {
    this->combatPower += plus;
}

