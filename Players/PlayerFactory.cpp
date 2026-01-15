#include "Player.h"
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>>
#include "Utilities.h"
using namespace std;
std::set<std::unique_ptr<Player>> PlayerFactory::playerList{};
void PlayerFactory::readPlayers(std::istream& playersStream) {
    string name, job, character;
    PlayerFactory playerFactory;

    while (playersStream >> name >> job >> character) {
        if (name.size() < 1 || name.size() > 15) {
            throw runtime_error("Invalid Players File");
        }

        for (char ch : name) {
            if (!((65 <= ch && ch <= 90) || ( 97 <= ch && ch <= 122))) {
                throw runtime_error("Invalid Players File");
            }
        }

        try {
            auto player = playerFactory.createPlayer(name, job, character);
            PlayerFactory::playerList.insert(std::move(player));
        } catch (const runtime_error& e) {
            throw runtime_error("Invalid Players File");
        }
        if (!playersStream.eof() && (playersStream.fail() || playersStream.bad())) {
            throw runtime_error("Invalid Players File");
        }
    }
}
