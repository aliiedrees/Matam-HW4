#pragma once

#include "Character.h"
#include "Job.h"

#include <memory>
#include <map>
#include <vector>
#include <string>

using std::string;
using std::unique_ptr;
using JobLambda = unique_ptr<Job>(*)();
using CharacterLambda = unique_ptr<Character>(*)();
class Player {
    string name;
    int level = 1;
    int force = 5;
    int currentHp = 100;
    int maxHp = 100;
    int coins = 10;
    bool alive = true;
    unique_ptr<Character> character;
    unique_ptr<Job> job;

public:
    int getCombatPower() const;
    string getDescription() const;
    string getName() const;
    const unique_ptr<Character>& getCharacter() const;
    const unique_ptr<Job>& getJob() const;
    int getLevel() const;
    void buffLevel();
    int getForce() const;
    int getHealthPoints() const;
    int getMaxHealthPoints() const;
    int getCoins() const;
    
    void wasted();
    int setForce(int force);
    void setHealthPoints(int newHealthPoints);
    void setCoins(int newCoins);
};

class PlayerFactory {
    static map<string, CharacterLambda> characterMap;
    static map<string, JobLambda> jobMap;
public:
    static vector<unique_ptr<Player>> playersQueue;

    ~PlayerFactory() = default;
    PlayerFactory();

    // maybe add add job/character method;

    unique_ptr<Player> createPlayer(const string& name, const string& job, const string& chatacter);

    void loadPlayers(std::istream& playersStream);

};
