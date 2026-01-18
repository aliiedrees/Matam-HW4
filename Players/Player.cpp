#include "Player.h"
#include "Job.h"
#include "Character.h"
#include "../Utilities.h"
#include <memory>
#include <string>
using namespace std;

Player::Player(const string name, unique_ptr<Job> job, unique_ptr<Character> character)
: name(name), job(std::move(job)), character(std::move(character)) {
  if (this->job->getType() == "Warrior") {
      maxHp = 150;
      currentHp = maxHp;
  }
  else if (this->job->getType() == "Archer") {
      coins += 10;
  }
}

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
void Player::setForce(int force) {
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

bool Player::operator<(const Player &other) const {
  if (this->level == other.level) {
    if (this->coins == other.coins) {
      return name < other.name;  // Lexicographically smallest name first
    }
    return coins > other.coins;  // Highest force first
  }
  return level > other.level;  // Highest level first
}
