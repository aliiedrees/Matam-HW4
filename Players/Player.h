
#pragma once
#include <memory>
#include <string>
#include "Player.h"
#include <vector>
#include <set>
#include <map>
#include "Character.h"
#include "Job.h"
#include <iostream>>
#include "Utilities.h"
#include "Job.h"
#include "Character.h"
using namespace std;
using std::string;
class Character;
class Job;

class Player {
 string Name;
  int Level = 1;
  int Force = 5;
  int CurrentHp = 100;
  int MaxHp = 100;
  int Coins = 10;
protected : std::unique_ptr<Character> Character;
  std::unique_ptr<Job> Job;
public:
 Player(string Name , string Behavior , string Job);
 int getCombatPoawer() const ;
    string getDescription() const;

    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    string getName() const;
 const std::unique_ptr<Character>& getCharacter() const;
 const std::unique_ptr<Job>& getJob() const;
    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    int getLevel() const;
void buffLevel();
    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    int getForce() const;
 int setForce(int force);
    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    int getHealthPoints() const;
 int getMaxHealthPoints() const;
    void setHealthPoints(int newHealthPoints);
    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    int getCoins() const;
    void setCoins(int newCoins);
 bool operator>(Player& other);
};
class PlayerFactory {

public:
        static std::set<std::unique_ptr<Player>> playerList;

        ~PlayerFactory() = default;

    static void readPlayers(std::istream& playersStream);
};
