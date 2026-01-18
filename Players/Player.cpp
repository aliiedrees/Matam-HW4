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
 string description = this->name  + "," + this->job->getType() + "with" + this->character->getType() +
 "( level" + to_string(this->level) + ", force" + to_string(this->force) + " )";
  return description;
}

string Player::getName() const {
return this->name;
}

int Player::getLevel() const {
return this->level;
}
void Player::buffLevel() {
 this->level = this->level + 1;
}
int Player::getForce() const {
return this->force;
}
int Player::setForce(int force) {
 this->force = this->force + force;
}
int Player::getHealthPoints() const {
return this->currentHp;
}
int Player::getMaxHealthPoints() const {
 return this->maxHp;
}
void Player::setHealthPoints(int newHealthPoints) {
 this->currentHp = newHealthPoints;
}
int Player::getCoins() const {
return this->coins;
}
void Player::setCoins(int newCoins) {
  this->coins = newCoins;
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
int Player::getCombatPower() const {
 return this->job->calculateCombatPower(*this);
}
