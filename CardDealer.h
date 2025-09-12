#pragma once

#include "Card.h"
#include <vector>
#include <random>

class CardDealer
{
private:
    int numSuits;
    int numRanks;
    std::vector<Card> deck;
    size_t currentCardIndex;
    std::mt19937 rng;

    void shuffleDeck();
    void resetDeck();

public:
    CardDealer(int numSuits, int numRanks = 13);

    
    Card operator()();

    
    int getNumSuits() const { return numSuits; }
    int getNumRanks() const { return numRanks; }
};