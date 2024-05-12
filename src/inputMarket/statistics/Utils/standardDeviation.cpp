/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** standardDeviation
*/

#include "trade.hpp"
#include <cmath>

double Tr::Trade::computeStandardDeviation(std::vector<candle_t> candlesCrypto, std::size_t period)
{
    double movAvgUDST_BTC = 0.0;
    double standardDeviation = 0.0;

    movAvgUDST_BTC = computeMovingAverage(candlesCrypto, period);
    std::size_t sizeList = candlesCrypto.size();
    std::size_t idx = sizeList - period;
    for (; idx < sizeList; ++idx) {
        standardDeviation += std::pow((candlesCrypto.at(idx).close - movAvgUDST_BTC), 2);
    }
    return std::sqrt(standardDeviation / period);
}
