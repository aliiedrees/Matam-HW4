#include "Event.h"
#include "Utilities.h"
#include <string>
#include "Job.h"
#include "Character.h"
#include "Player.h"
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
    if(player.getJob()->checkIfRnaged(player) == false) {
        player.setHealthPoints(player.getHealthPoints() - 10);
    }
    return getEncounterWonMessage(player,this->getLoot());
}
string Barlog::apply(Player& player) {
    string s = this->apply(player);
    this->setCombatPowers(2);
    return s;
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


int Pack::getCombatPower() const {
int totalCombatPower = 0;
    for(Monsters e : this->monsters) {
        totalCombatPower += e.getCombatPower();
        e.setCombatPowers(2);
        }
    return totalCombatPower;
    }
int Pack::getLoot() const {
    int totalLoot = 0;
    for(Monsters e : this->monsters) {
        totalLoot += e.getLoot();
    }
    return totalLoot;
}
int Pack::getDamage() const {
    int totalDamage = 0;
    for(Monsters e : this->monsters) {
        totalDamage += e.getDamage();
    }
    return totalDamage;
}
string SolarEclipse::apply(Player& player) {
    return player.getJob()->solarEclipse(player);
}
string PotionsMerchant::apply(Player& player) {
    return player.getCharacter()->potionsMerchant(player);
}