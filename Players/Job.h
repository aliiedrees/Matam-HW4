#pragma once
#include <string>
using namespace std;
class Player;
class Job {

public:
    virtual ~Job() = default;
    virtual  int calculateCombatPower(const Player& player) const ;
    virtual std::string getType() = 0;
    virtual string solarEclipse(Player& player);
    virtual bool checkIfRnaged(const Player& player);
};

class Warrior : public Job {

public:
    bool checkIfRnaged(const Player& player) override;
    ~Warrior() override = default;
     int calculateCombatPower(const Player& player) const override ;
    string solarEclipse(Player& player) override;
    std::string getType() override ;
};

class Magician : public Job {

public:
    bool checkIfRnaged(const Player& player) override;
    ~Magician() override = default;
    int calculateCombatPower(const Player& player) const override ;
    string solarEclipse(Player& player) override;
    std::string getType() override;
};

class Archer : public Job {
public:
    bool checkIfRnaged(const Player& player) override;
    int calculateCombatPower(const Player& player) const override ;
    string solarEclipse(Player& player) override;
    ~Archer() override = default;
    std::string getType() override ;
};

