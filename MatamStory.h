
#pragma once

#include <iostream>
#include "Events/EventFactory.h"
#include "Players/Player.h"
#include "Events/Event.h"
using std::unique_ptr;

class MatamStory{
private:
   // unsigned int m_turnIndex;

   // vector<unique_ptr<Event>> eventsQueue;
    //vector<unique_ptr<Player>> playersQueue;
    EventFactory eventFactory; // Map of events
     unsigned int m_turnIndex;
 /**
     * Create a sorted leaderboard
     *
     * @return - std::set of players references
    */

    //std::set<Player *> createLeaderBoard(const std::vector<std::unique_ptr<Player>> &players);
    std::vector<Player*>createLeaderBoard(const std::vector<std::unique_ptr<Player>>& players);
    /**
     * Playes a single turn for a player
     *
     * @param player - the player to play the turn for
     *
     * @return - void
    */
    void playTurn(Player& player);

    /**
     * Plays a single round of the game
     *
     * @return - void
    */
    void playRound();

    /**
     * Checks if the game is over
     *
     * @return - true if the game is over, false otherwise
    */
    bool isGameOver() const;
/*
    void loadEvents(istream& eventsStream);
    void loadPlayers(istream& playersStream);
    
    vector<unique_ptr<Encounter>> prepareEncounterVector(string line);

    void addSnail();
    void addSlime();
    void addBarlog();
    void addPack(vector<unique_ptr<Encounter>> encounterPack, int size);
    void addSolarEclipse();
    void addPotionsMerchant();

    int getRanking(const Player& player) const;*/
public:
    /**
     * Constructor of MatamStory class
     *
     * @param eventsStream - events input stream (file)
     * @param playersStream - players input stream (file)
     *
     * @return - MatamStory object with the given events and players
     *
    */
    MatamStory(std::istream& eventsStream, std::istream& playersStream);

    /**
     * Plays the entire game
     *
     * @return - void
    */
    void play();
};
