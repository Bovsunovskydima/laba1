#include "Card.h"
#include <string>

Card::Card(int suit, int rank) : suit(suit), rank(rank)
{
    if (rank < 1)
    {
        throw std::invalid_argument("Card rank must be at least 1.");
    }
    if (suit < 0)
    {
        throw std::invalid_argument("Card suit cannot be negative.");
    }
}