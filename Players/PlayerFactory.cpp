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
    characterMap["RiskTaker"] = []() ->unique_ptr<Character> { return make_unique<RiskTaker>(); };
}

void PlayerFactory::loadPlayers(std::istream& playersStream) {
    string name, job, character;
    PlayerFactory playerFactory;

    while (playersStream >> name >> job >> character) {
        // Check if name length is valid
        if (name.size() < 3 || name.size() > 15) {
            throw runtime_error("Invalid Players File");
        }

        for (char ch : name) {
            if (!((65 <= ch && ch <= 90) || ( 97 <= ch && ch <= 122))) {
                // Check if every character is a letter
                throw runtime_error("Invalid Players File");
            }
        }

        // Attempt to create a player using the players factory
        try {
            auto player = playerFactory.createPlayer(name, character, job);
            PlayerFactory::playersQueue.push_back(std::move(player));
        } catch (const runtime_error& e) {
            throw runtime_error("Invalid Players File");
        }

        // Check if the input stream ended in the middle of a player entry
        if (!playersStream.eof() && (playersStream.fail() || playersStream.bad())) {
            throw runtime_error("Invalid Players File");
        }
    }
}

unique_ptr<Player> PlayerFactory::createPlayer(const string& name, const string& job, const string& character) {
    auto jobIt = jobMap.find(job);
    if (jobIt == jobMap.end()) {
        throw std::runtime_error("Invalid Players File.");
    }

        // Check if the character exists
    auto characterIt = characterMap.find(character);
    if (characterIt == characterMap.end()) {
        throw std::runtime_error("Invalid Players File.");
    }
       // Create the job and the character
    auto jobPtr = jobIt->second();
    auto characterPtr = characterIt->second();

        // Create the player with the generate job and character
    return make_unique<Player>(name, std::move(jobPtr), std::move(characterPtr));
}