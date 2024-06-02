/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** macd
*/

#include "trade.hpp"

void Tr::Trade::computeMovingAverageVolume()
{
    int period = 20;

    double movingAverage = 0;
    std::size_t idx = _listCandles.size() - period;

    for (; idx < _listCandles.size(); ++idx) {
        movingAverage += _listCandles.at(idx).volume;
    }
    movingAverage /= static_cast<double>(period);
    _listCandles.back().stats.volume.movingAverage = movingAverage;
}

void Tr::Trade::computeMovingAvgOpenClose()
{
    int period = 10;

    double movingAverage = 0;
    std::size_t idx = _listCandles.size() - period;

    for (; idx < _listCandles.size(); ++idx) {
        double neg = _listCandles.back().open - _listCandles.back().close;
        movingAverage += (neg);
    }
    movingAverage /= static_cast<double>(period);
    _listCandles.back().stats.volume.diffOpenClose = movingAverage;
}
