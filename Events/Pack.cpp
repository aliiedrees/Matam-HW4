#include "Event.h"

Pack::Pack(int size, Encounter** monsters){
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
    
}