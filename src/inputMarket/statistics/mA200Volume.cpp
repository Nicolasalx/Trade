/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** MA200Volume
*/

#include "trade.hpp"

void Tr::Trade::computeMovingAverage200Volume()
{
    int period = 200;

    if (_listCandles.size() < std::size_t(period)) {
        return;
    }

    double movingAverage = 0;
    std::size_t idx = _listCandles.size() - period;

    for (; idx < _listCandles.size(); ++idx) {
        movingAverage += _listCandles.at(idx).volume;
    }

    _listCandles.back().stats.volume.movingAverage200 = (movingAverage /= static_cast<double>(period));
}