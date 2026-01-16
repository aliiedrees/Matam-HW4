#pragma once
#include <string>
using namespace std;
class Player;

class Job {

public:
    Job() = default;
    virtual ~Job() = 0;
    virtual  int calculateCombatPower(const Player& player) const ;
    virtual std::string getType() const = 0;
    virtual string solarEclipse(Player& player);
    virtual bool checkIfRnaged();
};

class Warrior : public Job {

public:
    Warrior() = default ;
    bool checkIfRnaged() override;
    ~Warrior() override = default;
     int calculateCombatPower(const Player& player) const override ;
    string solarEclipse(Player& player) override;
    std::string getType()const override ;
};

class Magician : public Job {

public:
    Magician() = default;
    bool checkIfRnaged() override;
    ~Magician() override = default;
    int calculateCombatPower(const Player& player) const override ;
    string solarEclipse(Player& player) override;
    std::string getType() const override;
};

class Archer : public Job {

    public:
    Archer() = default;
    bool checkIfRnaged() override;
    int calculateCombatPower(const Player& player) const override ;
    string solarEclipse(Player& player) override;
    ~Archer() override = default;
    std::string getType() const override ;
};

