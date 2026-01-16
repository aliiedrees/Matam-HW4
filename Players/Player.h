
#pragma once
#include <memory>
#include <string>
#include "Player.h"
#include <vector>
#include <functional>
#include <set>
#include <map>
#include "Character.h"
#include "Job.h"
#include <iostream>
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
   bool alive = true;
protected : 
   std::unique_ptr<Character> character;
   std::unique_ptr<Job> job;
public:
   Player(string Name , string Behavior , string Job);
   int getCombatPoawer() const ;
   string getDescription() const;
   void wasted(){
      alive = false;
   }
    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    string getName() const;
   const std::unique_ptr<Character> getCharacter() const;
   const std::unique_ptr<Job> getJob() const;
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
  bool operator<(const Player &other) const {
        if (this->Level == other.Level) {
            if (this->Coins == other.Coins) {
                return Name < other.Name;  // Lexicographically smallest name first
            }
            return Coins > other.Coins;  // Highest force first
        }
        return Level > other.Level;  // Highest level first
    }
};

class PlayerFactory {
private:
        // Maps for job and character creation
        map<string, function<unique_ptr<Job>()>> jobFactoryMap;
        map<string, function<unique_ptr<Character>()>> characterFactoryMap;
public:
        static std::vector<std::unique_ptr<Player>> playerList;

        ~PlayerFactory() = default;

        PlayerFactory(){
        // Register Jobs
        jobFactoryMap["Warrior"] = []() { return make_unique<Warrior>(); };
        jobFactoryMap["Magician"] = []() { return make_unique<Magician>(); };
        jobFactoryMap["Archer"] = []() { return make_unique<Archer>(); };

        // Register Characters
        characterFactoryMap["Responsible"] = []() { return make_unique<Responsible>(); };
        characterFactoryMap["RiskTaking"] = []() { return make_unique<RiskMaker>(); };
      }

    	// Add a new job dynamically
        void registerJob(const string& jobName, const function<unique_ptr<Job>()> &jobCreator){
            jobFactoryMap[jobName] = jobCreator;
        }

        // Add a new character dynamically
        void registerCharacter(const string& characterName, const function<unique_ptr<Character>()> &characterCreator){
          characterFactoryMap[characterName] = characterCreator;
        }

        // Create Player
         unique_ptr<Player> createPlayer(const string& name, const string& job, const string& character) const{
			// Check if the job exists
            auto jobIt = jobFactoryMap.find(job);
            if (jobIt == jobFactoryMap.end()) {
                throw std::runtime_error("Invalid Players File.");
            }

            // Check if the character exists
            auto characterIt = characterFactoryMap.find(character);
            if (characterIt == characterFactoryMap.end()) {
                throw std::runtime_error("Invalid Players File.");
            }

            // Create the job and the character
            auto jobPtr = jobIt->second();
            auto characterPtr = characterIt->second();

            // Create the player with the generate job and character
            return make_unique<Player>(name, std::move(jobPtr), std::move(characterPtr));
       
         }

        
    static void readPlayers(std::istream& playersStream);
};