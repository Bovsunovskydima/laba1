#pragma once

#include <compare>
#include <iostream>

class Card
{
private:
    int suit; // suit (0, 1, 2, ...)
    int rank; // Rank (1-13, where 1=Ace, 11=Jack, 12=Queen, 13=King)

public:
    Card(int suit = 0, int rank = 1);

    std::strong_ordering operator<=>(const Card &other) const;

    int getSuit() const { return suit; }
    int getRank() const { return rank; }

    friend std::ostream &operator<<(std::ostream &os, const Card &card);
};