/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** relativeCandle
*/

#include "trade.hpp"

void Tr::Trade::relativeCandle(std::size_t period)
{
    std::size_t idx = this->_listCandles.size() - period - 1;
    double firstTemp = 0.0;
    double lastTemp = 0.0;

    if (this->_listCandles.size() <= period) {
        return;
    }
    firstTemp = this->_listCandles.at(idx).close;
    lastTemp = this->_listCandles.back().close;
    this->_listCandles.back().stats.rgs.relative = ((lastTemp * 100) / firstTemp) - 100;
}
