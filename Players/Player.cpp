#include "Player.h"
#include "Job.h"
#include "Character.h"
#include "../Utilities.h"
#include <memory>
#include <string>
#include "Job.h"
#include "Character.h"
using namespace std;
/* Player::Player(std::string name, std::unique_ptr<Job> job, std::unique_ptr<Character> character)
  : Name(std::move(name)), Job(std::move(job)), Character(std::move(character)) {
 if (this->Job->getType() == "Warrior") {
  this->MaxHp = 150;
  CurrentHp = MaxHp;
 }
 else if (this->Job->getType() == "Archer") {
  this->Coins += 10;
 }
}
*/
string Player::getDescription() const {
 string description = this->Name  + "," + this->job->getType() + "with" + this->character->getType() +
 "( level" + to_string(this->Level) + ", force" + to_string(this->Force) + " )";
  return description;
}

string Player::getName() const {
return this->Name;
}

int Player::getLevel() const {
return this->Level;
}
void Player::buffLevel() {
 this->Level = this->Level + 1;
}
int Player::getForce() const {
return this->Force;
}
int Player::setForce(int force) {
 this->Force = this->Force + force;
}
int Player::getHealthPoints() const {
return this->CurrentHp;
}
int Player::getMaxHealthPoints() const {
 return this->MaxHp;
}
void Player::setHealthPoints(int newHealthPoints) {
 this->CurrentHp = newHealthPoints;
}
int Player::getCoins() const {
return this->Coins;
}
void Player::setCoins(int newCoins) {
  this->Coins = newCoins;
}
/*bool Player::operator>(Player& other) {
 {
  if (this->getLevel() == other.getLevel) {
   if (this->getCoins == other.getCoins) {
    return this->getName < other.getName;
   }
  int Force
   return this->getCoins > other.getCoins;
  }
  return this->getLevel > other.getLevel;
 }
};*/
int Player::getCombatPoawer() const {
 return this->job->calculateCombatPower(*this);
}
