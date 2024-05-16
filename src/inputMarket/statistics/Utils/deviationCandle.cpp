/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** deviationCandle
*/

#include "trade.hpp"
#include <cmath>

void Tr::Trade::deviationCandle(std::size_t period)
{
    int idx = this->_listCandles.size() - period;
    double standardDeviation = 0.0;
    double averageTemperature = 0.0;
    std::size_t weatherSize = this->_listCandles.size();

    if (idx < 0) {
        idx = 0;
    }
    if (weatherSize < period) {
        return;
    }
    for (int i = idx; i < int(weatherSize); ++i) {
        averageTemperature += this->_listCandles.at(i).close;
    }
    averageTemperature /= period;
    for (int i = idx; i < int(weatherSize); ++i) {
        standardDeviation += std::pow((this->_listCandles.at(i).close - averageTemperature), 2);
    }
    this->_listCandles.back().stats.rgs.standardDeviation = std::sqrt(standardDeviation / period);
}
