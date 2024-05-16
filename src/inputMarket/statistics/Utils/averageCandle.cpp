/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** averageCandle
*/

#include "trade.hpp"

void Tr::Trade::averageCandle(std::size_t period)
{
    std::size_t idx = this->_listCandles.size() - period - 1;
    bool hasPassedFrstValue = false;

    if (this->_listCandles.size() < period + 1) {
        return;
    }
    this->_listCandles.back().stats.rgs.movingAverage = 0.0;
    for (; idx < this->_listCandles.size(); ++idx) {
        if (hasPassedFrstValue == true && this->_listCandles.at(idx - 1).close < this->_listCandles.at(idx).close) {
            this->_listCandles.back().stats.rgs.movingAverage += this->_listCandles.at(idx).close - this->_listCandles.at(idx - 1).close;
        }
        hasPassedFrstValue = true;
    }
    this->_listCandles.back().stats.rgs.movingAverage /= period;
}
