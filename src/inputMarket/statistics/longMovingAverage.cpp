/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** longMovingAverage
*/

#include "trade.hpp"

// Moyenne mobile sur 50 jours
void Tr::Trade::computeLongMovingAverage()
{
    int period = 50;

    if (_listCandles.size() < std::size_t(period)) {
        return;
    }
    double movAvgUSDTBTC = computeMovingAverage(_listCandles, period);

    _listCandles.back().stats.moving_average.lastMMLong = movAvgUSDTBTC;
}
