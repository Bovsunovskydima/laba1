/*
 * Compiler: g++ 
 * Standart: C++20
 * Build command: g++ -std=c++20 -Wall -Wextra -O2 main.cpp Card.cpp CardDealer.cpp StackAnalyzer.cpp -o card_game
 * Launch command: ./card_game
 */

#include <iostream>
#include <stdexcept>
#include <limits>
#include "Card.h"
#include "CardDealer.h"
#include "StackAnalyzer.h"


int getIntInput(const std::string& prompt, int minValue = 1)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value)
        {
            if (value >= minValue)
            {
                
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
            else
            {
                std::cout << "Error: value must be at least " << minValue << "\n";
            }
        }
        else
        {
            std::cout << "Error: Enter an integer\n";
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }
    }
}


void demonstrateDealer(CardDealer& dealer, int numCardsToShow = 20)
{
    std::cout << "\nDealer demonstration (first" << numCardsToShow << " cards):\n";
    for (int i = 0; i < numCardsToShow; ++i)
    {
        Card card = dealer();
        std::cout << card << " ";
        if ((i + 1) % 10 == 0)
            std::cout << "\n";
    }
    std::cout << "\n";
}

char getYesNoInput(const std::string& prompt)
{
    char value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> value;
        value = std::tolower(value);
        if (value == 'y' || value == 'n')
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Error: Enter 'y' or 'n'\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main()
{
    try
    {
        std::cout << "=== CARD STACK ANALYSIS PROGRAM ===\n\n";

        
        int numSuits = getIntInput("Enter the number of suits: ", 1);
        int numCards = getIntInput("Enter the number of cards to analyze: ", 1);

        
        std::cout << "\nCreating a dealer with " << numSuits << " suits and 13 ranks...\n";
        CardDealer dealer(numSuits, 13);

        
        char showDemo = getYesNoInput("Show a dealer demonstration? (y/n): ");
        if (showDemo == 'y' || showDemo == 'Y')
        {
            demonstrateDealer(dealer, std::min(20, numCards));
        }

        
        std::cout << "\nWe begin the analysis " << numCards << " cards...\n";
        StackAnalyzer analyzer;
        StackStatistics stats = analyzer.analyzeStacks(dealer, numCards);

        
        analyzer.printStatistics(stats);

        
        char runExperiment = getYesNoInput("Run an experiment based on the number of cards per suit? (y/n): ");
        if (runExperiment == 'y' || runExperiment == 'Y')
        {
            int numSuitsExp = getIntInput("Number of suits for the experiment: ", 1);
            int minRanks = getIntInput("Minimum number of cards per suit (ranks) for the experiment: ", 2);
            int maxRanks = getIntInput("Maximum number of cards per suit (ranks) for the experiment: ", minRanks);
            int expCards = getIntInput("Number of cards for the experiment: ", 100);

            std::cout << "An experiment is launched...\n";
            analyzer.runExperiment(numSuitsExp, minRanks, maxRanks, expCards, 100);
        }

        std::cout << "\nThe program completed successfully!\n";

        std::cout << "Press Enter to exit...";
        std::cin.ignore();
        std::cin.get();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error!\n";
        return 1;
    }

    return 0;
}