#include "StackAnalyzer.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>

StackStatistics StackAnalyzer::analyzeStacks(CardDealer& dealer, int numCards)
{
    if (numCards <= 0)
    {
        throw std::invalid_argument("The number of cards must be positive");
    }

    stackLengths.clear();

    int currentStackLength = 1;
    Card previousCard = dealer();

    
    for (int i = 1; i < numCards; ++i)
    {
        Card currentCard = dealer();

        
        if (currentCard >= previousCard)
        {
            currentStackLength++;
        }
        else
        {
            
            stackLengths.push_back(currentStackLength);
            currentStackLength = 1;
        }

        previousCard = currentCard;
    }

    
    stackLengths.push_back(currentStackLength);

    
    StackStatistics stats;
    stats.totalStacks = stackLengths.size();

    
    for (int length : stackLengths)
    {
        stats.lengthCounts[length]++;
    }

    
    int totalLength = std::accumulate(stackLengths.begin(), stackLengths.end(), 0);
    stats.averageLength = static_cast<double>(totalLength) / stats.totalStacks;

    
    stats.medianLength = calculateMedian(stackLengths);

    
    int maxCount = 0;
    for (const auto& pair : stats.lengthCounts)
    {
        if (pair.second > maxCount)
        {
            maxCount = pair.second;
            stats.mostCommonLength = pair.first;
        }
    }
    stats.mostCommonPercentage = 100.0 * maxCount / stats.totalStacks;

    return stats;
}

double StackAnalyzer::calculateMedian(std::vector<int> lengths) const
{
    if (lengths.empty())
        return 0.0;

    std::sort(lengths.begin(), lengths.end());
    size_t n = lengths.size();

    if (n % 2 == 0)
    {
        return (lengths[n / 2 - 1] + lengths[n / 2]) / 2.0;
    }
    else
    {
        return lengths[n / 2];
    }
}

void StackAnalyzer::printStatistics(const StackStatistics& stats) const
{
    std::cout << "\n=== RATE STATISTICS ===\n";
    std::cout << "Total number of stacks: " << stats.totalStacks << "\n";
    std::cout << "Average stack length: " << std::fixed << std::setprecision(2)
        << stats.averageLength << "\n";
    std::cout << "Median stack length: " << std::fixed << std::setprecision(2)
        << stats.medianLength << "\n";
    std::cout << "The most common stack length: " << stats.mostCommonLength
        << " (" << std::fixed << std::setprecision(1) << stats.mostCommonPercentage << "%)\n";

    std::cout << "\nDistribution of stack lengths:\n";
    std::cout << "Length\tQuantity\tPercentage\n";
    std::cout << "-------\t---------\t--------\n";

    for (const auto& pair : stats.lengthCounts)
    {
        double percentage = 100.0 * pair.second / stats.totalStacks;
        std::cout << pair.first << "\t" << pair.second << "\t\t"
            << std::fixed << std::setprecision(1) << percentage << "%\n";
    }
}

void StackAnalyzer::runExperiment(int numSuits, int minRanks, int maxRanks, int numCards, int iterations)
{
    std::cout << "\n=== EXPERIMENT: DEPENDENCE ON THE NUMBER OF CARDS PER SUIT ===\n";
    std::cout << "Number of cards for analysis: " << numCards << "\n";
    std::cout << "Number of iterations for each experiment: " << iterations << "\n\n";

    std::cout << "Ranks\tAverage length\tMedian length\n";
    std::cout << "-----\t---------------\t----------------\n";

    for (int numRanks = minRanks; numRanks <= maxRanks; ++numRanks)
    {
        double avgSum = 0.0;
        std::vector<int> allStackLengths;

        for (int iter = 0; iter < iterations; ++iter)
        {
            CardDealer dealer(numSuits, numRanks);
            StackStatistics stats = analyzeStacks(dealer, numCards);
            avgSum += stats.averageLength;
            allStackLengths.insert(allStackLengths.end(), stackLengths.begin(), stackLengths.end());
        }

        double avgAverage = avgSum / iterations;
        double medianLength = calculateMedian(allStackLengths);

        std::cout << numRanks << "\t" << std::fixed << std::setprecision(3)
            << avgAverage << "\t\t" << medianLength << "\n";
    }
}