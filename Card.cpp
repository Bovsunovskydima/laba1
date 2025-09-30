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

std::strong_ordering Card::operator<=>(const Card &other) const
{
    return rank <=> other.rank;
}

std::ostream &operator<<(std::ostream &os, const Card &card)
{
    std::string rankStr;
    if (card.rank == 1)
    {
        rankStr = "A";
    }
    else if (card.rank == 11)
    {
        rankStr = "J";
    }
    else if (card.rank == 12)
    {
        rankStr = "Q";
    }
    else if (card.rank == 13) 
    {
        rankStr = "K";
    }
    else
    {
        rankStr = std::to_string(card.rank);
    }

    const char *suits[] = {"S", "H", "D", "C"}; // Spades, Hearts, Diamonds, Clubs
    os << rankStr << suits[card.suit % 4];
    return os;
}