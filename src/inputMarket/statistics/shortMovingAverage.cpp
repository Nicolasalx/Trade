/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** shortMovingAverage
*/

#include "trade.hpp"

void Tr::Trade::computeShortMovingAverage()
{
    int period = 20;

    if (_listCandles.size() < std::size_t(period)) {
        return;
    }
    double movAvgUSDTBTC = computeMovingAverage(_listCandles, period);

    _listCandles.back().stats.moving_average.lastMMShort = movAvgUSDTBTC;
}
