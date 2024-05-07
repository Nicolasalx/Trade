/*
** EPITECH PROJECT, 2024
** Trade
** File description:
** shortMovingAverage
*/

#include "trade.hpp"

// Moyenne mobile sur 20 jours
void Tr::Trade::computeShortMovingAverage()
{
    int period = 20;

    if (_listCandles.size() < std::size_t(period)) {
        return;
    }
    double movAvgUSDTBTC = computeMovingAverage(_listCandles, period);

    _listCandles.back().stats.lastMMShort = movAvgUSDTBTC;

    //std::cout << "Short USDT_BTC => " << std::to_string(movAvgUSDTBTC) << "\n";
}
