#include "CardDealer.h"
#include <algorithm>
#include <stdexcept>

CardDealer::CardDealer(int numSuits, int numRanks) : numSuits(numSuits), numRanks(numRanks), currentCardIndex(0), rng(std::random_device{}())
{
    if (numSuits <= 0)
    {
        throw std::invalid_argument("The number of suits must be positive");
    }
    if (numRanks < 2)
    {
        throw std::invalid_argument("The number of ranks must be at least 2");
    }

    resetDeck();
    shuffleDeck();
}

void CardDealer::resetDeck()
{
    deck.clear();
    deck.reserve(numSuits * numRanks);

    // // Create the deck: numRanks cards for each suit (ranks 1 to numRanks)
    for (int suit = 0; suit < numSuits; ++suit)
    {
        for (int rank = 1; rank <= numRanks; ++rank)
        {
            deck.emplace_back(suit, rank);
        }
    }

    currentCardIndex = 0;
}

void CardDealer::shuffleDeck()
{
    std::shuffle(deck.begin(), deck.end(), rng);
}

Card CardDealer::operator()()
{
    
    if (currentCardIndex >= deck.size())
    {
        resetDeck();
        shuffleDeck();
    }

    return deck[currentCardIndex++];
}