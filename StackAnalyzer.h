#pragma once

#include "CardDealer.h"
#include <vector>
#include <map>

struct StackStatistics
{
    std::map<int, int> lengthCounts; 
    double averageLength;
    double medianLength;
    int mostCommonLength;
    double mostCommonPercentage;
    int totalStacks;
};

class StackAnalyzer
{
private:
    std::vector<int> stackLengths;

    double calculateMedian(std::vector<int> lengths) const;

public:
    
    StackStatistics analyzeStacks(CardDealer& dealer, int numCards);

    
    void printStatistics(const StackStatistics& stats) const;

    
    void runExperiment(int numSuits, int minRanks, int maxRanks, int numCards, int iterations = 100);
};