#include "Player.h"

std::vector<std::unique_ptr<Player>> PlayerFactory::playersQueue{};
map<string, CharacterLambda> PlayerFactory::characterMap;
map<string, JobLambda> PlayerFactory::jobMap;

PlayerFactory::PlayerFactory(){
        // Register Jobs
    jobMap["Warrior"] = []() ->unique_ptr<Job> { return make_unique<Warrior>(); };
    jobMap["Magician"] = []() ->unique_ptr<Job> { return make_unique<Magician>(); };
    jobMap["Archer"] = []() ->unique_ptr<Job> { return make_unique<Archer>(); };

        // Register Characters
    characterMap["Responsible"] = []() ->unique_ptr<Character> { return make_unique<Responsible>(); };
    characterMap["RiskTaking"] = []() ->unique_ptr<Character> { return make_unique<RiskTaker>(); };
}
bool isAlpha(string name) {

    for (auto c : name) {
        if (!(c >= 'a' && c <= 'z' )&&!(c >= 'A' && c <= 'Z')) {
            return false;
        }
    }
    return true;
}
void PlayerFactory::loadPlayers(std::istream& playersStream) {
    string name, job, character;
    PlayerFactory playerFactory;

    while (playersStream >> name >> job >> character) {
        // Check if name length is valid
        if(name.empty() || !isAlpha(name)|| jobMap.find(job) == jobMap.end() || characterMap.find(character) == characterMap.end()) {
            throw runtime_error("Invalid Players File");
        }
        if (name.size() < 3 || name.size() > 15) {
            throw runtime_error("Invalid Players File");
        }

        // Attempt to create a player using the players factory
        try {
            auto player = playerFactory.createPlayer(name, job, character);
            PlayerFactory::playersQueue.push_back(std::move(player));
        } catch (const runtime_error& e) {
            throw runtime_error(e);
        }
    }
    if (playersQueue.size() < 2 || playersQueue.size() > 6) {
        throw std::runtime_error("Invalid Players File");
    }
}

unique_ptr<Player> PlayerFactory::createPlayer(const string& name, const string& job, const string& character) {
    auto jobIt = jobMap.find(job);
    if (jobIt == jobMap.end()) {
        throw std::runtime_error("Invalid Players File");
    }

        // Check if the character exists
    auto characterIt = characterMap.find(character);
    if (characterIt == characterMap.end()) {
        throw std::runtime_error("Invalid Players File");
    }
       // Create the job and the character
    auto jobPtr = jobIt->second();
    auto characterPtr = characterIt->second();

        // Create the player with the generate job and character
    return make_unique<Player>(name, std::move(jobPtr), std::move(characterPtr));
}

