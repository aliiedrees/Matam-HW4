
#include "MatamStory.h"

#include "Utilities.h"

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    /*===== TODO: Open and read events file =====*/
    loadEvents(eventsStream);
    /*==========================================*/


    /*===== TODO: Open and Read players file =====*/
    loadPlayers(playersStream);
    /*============================================*/


    this->m_turnIndex = 1;
}
void MatamStory::loadEvents(istream& eventsStream){ // missing add events func
    string line;
    
    if(!getline(eventsStream, line)){
        throw std::runtime_error("Invalid Events File");
    }

    do {
        int length = line.length();
        if(length == 0){
            throw std::runtime_error("Invalid Events File");
        }
        int i = 0;
        string eventType = "";
        while (line[i] != ' ' && i < length){
            eventType += line[i];
            i++;
        }
        if(eventType == "Snail"){
            addSnail();
        } else if (eventType == "Slime"){
            addSlime();
        } else if (eventType == "Barlog"){
            addBarlog();
        } else if (eventType == "Pack"){
            if(i == length - 1){
                throw std::runtime_error("Invalid Events File");
            }
            int size = line [++i];
            addPack(std::move(prepareEncounterVector(line)), size);
        } else if (eventType == "SolarEclipse"){
            addSolarEclipse();
        } else if (eventType == "PotionsMerchant"){
            addPotionsMerchant();
        } else { // eventType is not included in our game
            throw std::runtime_error("Invalid Events File");
        }
    } while (getline(eventsStream, line));
}

void MatamStory::loadPlayers(istream& playersStream){ // implemented in other file
    string line;
    if(!getline(playersStream, line)){
        throw std::runtime_error("Invalid Players File");
    } do {
        int length = line.length();
        if (length == 0){
            throw std::runtime_error("Invalid Players File");
        }
        int i = 0;
        string name = "";
        while (line[i] != ' ' && i < length){
            name += line[i];
            i++;
        }
        int nameLength = name.length();
        if (nameLength < 3 || nameLength > 15){
            throw std::runtime_error("Invalid Players File");
        }
        string job = "";
        while (line[i] != ' ' && i < length){
            job += line[i];
            i++;
        }
        
    } while (getline(playersStream, line));
}

vector<unique_ptr<Encounter>> MatamStory::prepareEncounterVector(string line){
    vector<unique_ptr<Encounter>> pack;
    int length = line.length();
    
    int i = 0;
    while (i < length){
        while(i < length && line[i] == ' '){
            i++;
        }
        string encounterType = "";
        while(i < length && line[i] != ' '){
            encounterType += line[i];
            i++;
        }
        if(encounterType == "Snail"){
            pack.push_back(make_unique<Snail>());
        } else if (encounterType == "Slime"){
            pack.push_back(make_unique<Slime>());
        } else if (encounterType == "Barlog"){
            pack.push_back(make_unique<Barlog>());
        } else { // invalid encounter
            throw std::runtime_error("Invalid Events File");
        }
    }

    return pack;
}

void MatamStory::addSnail(){
    unique_ptr<Event> snail = make_unique<Snail>();
    this->eventsQueue.push_back(snail);
}

void MatamStory::addSlime(){
    unique_ptr<Event> slime = make_unique<Slime>();
    this->eventsQueue.push_back(slime);
}

void MatamStory::addBarlog(){
    unique_ptr<Event> barlog = make_unique<Barlog>();
    this->eventsQueue.push_back(barlog);
}

void MatamStory::addPack(vector<unique_ptr<Encounter>> encounterPack, int size){
    unique_ptr<Event> pack = make_unique<Pack>(size, encounterPack);
    this->eventsQueue.push_back(pack);
}

void MatamStory::addSolarEclipse(){
    unique_ptr<Event> solar = make_unique<SolarEclipse>();
    this->eventsQueue.push_back(solar);
}

void MatamStory::addPotionsMerchant(){
    unique_ptr<Event> merchant = make_unique<PotionsMerchant>();
    this->eventsQueue.push_back(merchant);
}

void MatamStory::playTurn(Player& player) {

    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Get the next event from the events list
     * 2. Print the turn details with "printTurnDetails"
     * 3. Play the event
     * 4. Print the turn outcome with "printTurnOutcome"
    */

    int eventIndex = (m_turnIndex % eventsQueue.size() - 1);
    eventIndex = eventIndex < 0 ? eventsQueue.size() - 1 : eventIndex;
    cout << eventsQueue[eventIndex]->getDescription() << endl;
    string outcome = eventsQueue[eventIndex]->playEvent(player);
    printTurnOutcome(outcome);
    m_turnIndex++;
}

int MatamStory::getRanking(const Player& player) const {
    int rank = 1;
    for (const unique_ptr<Player> &currentPlayer: playersQueue) {
        if (currentPlayer->getLevel() > player.getLevel()) {
            rank++;
        } else if (currentPlayer->getLevel() == player.getLevel()) {
            if (currentPlayer->getCoins() > player.getCoins()) {
                rank++;
            } else if (currentPlayer->getCoins() == player.getCoins()) {
                if (currentPlayer->getName() < player.getName()) {
                    rank++;
                }
            }
        }
    }
    return rank;
}

void MatamStory::playRound() {

    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/
    for (int i = 0; i < playersQueue.size(); i++){
        printTurnDetails(i, *(playersQueue[i].get()), *(eventsQueue[i].get()));
        playTurn(*(playersQueue[i].get()));
    }
    /*=============================================*/

    printRoundEnd();

    printLeaderBoardMessage();

    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/
    for (int i = 0; i < playersQueue.size(); i++){
        printLeaderBoardEntry()
    }
    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() const {
    /*===== TODO: Implement the game over condition =====*/
    return false; // Replace this line
    /*===================================================*/
}

void MatamStory::play() {
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/

    /*=========================================================================================*/
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/

    /*========================================================================*/
}
