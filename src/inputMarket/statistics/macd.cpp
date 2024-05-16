/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** macd
*/

#include "trade.hpp"

double Tr::Trade::computeEMA(std::size_t period)
{
    double multiplier = 2.0 / (period + 1);
    double ema = this->_listCandles.at(period - 1).close;

    for (std::size_t i = this->_listCandles.size() - period; i < this->_listCandles.size(); ++i) {
        ema += (this->_listCandles.at(i).close - ema) * multiplier;
    }
    return ema;
}

void Tr::Trade::computeMACD()
{
    if (this->_listCandles.size() < 26) {
        return;
    }
    this->_listCandles.back().stats.macd.macd = computeEMA(12) - computeEMA(26);
    std::cerr << "MACD: " << this->_listCandles.back().stats.macd.macd << "\n";
}
