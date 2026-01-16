#include "Event.h"
#include "../Utilities.h"
#include <string>
#include "../Players/Job.h"
#include "../Players/Character.h"
#include "../Players/Player.h"
using namespace std;
// helper
string playEventHelper(Player& player,unsigned int combatPower, unsigned int loot, unsigned int damage){
    int playerCombatPower = player.getForce() + player.getLevel();
    if (playerCombatPower > combatPower){
        player.buffLevel();
        player.setCoins(player.getCoins() + loot);
        if(player.getJob() == "Warrior"){ //deal later virtual func
            player.setHealthPoints(player.getHealthPoints() - 10);
        }
        return getEncounterWonMessage(player, loot);
    } else {
        player.setHealthPoints(player.getHealthPoints() - damage);
        return getEncounterLostMessage(player, damage);
    }
}

// Snail
string Snail::playEvent(Player& player) const{
    return playEventHelper(player, combatPower, loot, damage);
}

// Slime
string Slime::playEvent(Player& player) const{
    return playEventHelper(player, combatPower, loot, damage);
}

// Barlog
string Slime::playEvent(Player& player) const{
    return playEventHelper(player, combatPower, loot, damage);
}

// Pack
Pack::Pack(int size, vector<unique_ptr<Encounter>> monsters){
    unsigned int totalPower = 0;
    unsigned int totalLoot = 0;
    unsigned int totalDamage = 0;

    for(int i = 0; i < size; i++){
        totalPower += monsters[i]->getCombatPower();
        totalLoot += monsters[i]->getLoot();
        totalDamage += monsters[i]->getDamage();
    }
    this->combatPower = totalPower;
    this->loot = totalLoot;
    this->damage = totalDamage;
}

string Pack::getDescription() const{
    unsigned int totalPower = this->getCombatPower();
    unsigned int totalLoot = this->getLoot();
    unsigned int totalDamage = this->getDamage();

    return "Pack of " + to_string(this->size) + " members (power " + to_string(totalPower) + 
    ", loot " + to_string(totalLoot) + ", damage " + to_string(totalDamage) + ")";
}

string Pack::playEvent(Player& player) const{
    return playEventHelper(player, this->combatPower, this->loot, this->damage);
}

// SolarEclipse
string SolarEclipse::playEvent(Player& player) const{
    int character = player.getJob();
    if(character == "Magician"){
        player.setForce(player.getForce() + 1);
        return getSolarEclipseMessage(player, 1);
    } else {
        player.setForce(player.getForce() - 1);
        return getSolarEclipseMessage(player, -1);
    }
}

// PotionsMerchant
string PotionsMerchant::playEvent(Player& player) const{
    int currentHP = player.getHealthPoints();
    int currentCoins = player.getCoins();
    if(player.getCharacter() == "RiskMaker"){
        if (currentHP < 50 && currentCoins > 5){
        player.setCoins(currentCoins - 5);
        player.setHealthPoints(currentHP + 10);
        }
    } else {
        int potionsAmmount = 0;
        while (currentHP + 10 * potionsAmmount < 100 || potionsAmmount * 5 <= currentCoins){
            potionsAmmount++;
        }
        potionsAmmount = (potionsAmmount * 5 ) > currentCoins ? potionsAmmount - 1 : potionsAmmount;
        player.setCoins(currentCoins - potionsAmmount * 5);
        player.setHealthPoints(currentHP + potionsAmmount * 10);
    }
}




/*string Encounter::playEvent(Player& player) {
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
}*/