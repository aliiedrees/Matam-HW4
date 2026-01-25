#include "Player.h"
#include "Job.h"
#include "Character.h"
#include "../Utilities.h"
#include <memory>
#include <string>
using namespace std;
std::string Warrior::getType() const{
    return "Warrior";
}
int Warrior::calculateCombatPower(const Player &player) const {
    int combatPower = 2*player.getForce() + player.getLevel();
    return combatPower;
}
std::string Warrior::solarEclipse(Player &player) {
    if(player.getForce() <= 0 ) {
        return getSolarEclipseMessage(player,0);
    }
    int effect = -1 ;
    player.setForce(effect);
    return getSolarEclipseMessage(player,effect);
}
bool Warrior::checkIfRnaged() {
    return false;
}