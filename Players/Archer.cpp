#include "Player.h"
#include "Job.h"
#include "Character.h"
#include "../Utilities.h"
#include <memory>
#include <string>
using namespace std;
std::string Archer::getType() const {
    return "Archer";
}
int Archer::calculateCombatPower(const Player &player) const {
    int combatPower = player.getForce() + player.getLevel();
    return combatPower;
}
std::string Archer::solarEclipse(Player &player) {
    if(player.getForce() <= 0 ) {
        return getSolarEclipseMessage(player,0);
    }
    int effect = -1 ;
    player.setForce(effect);
    return getSolarEclipseMessage(player,effect);
}
bool Archer::checkIfRnaged() {
    return true;
}
