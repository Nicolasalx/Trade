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
    double ema = 0.0;

    for (int i = (this->_listCandles.size() - 1);
        i >= (int(this->_listCandles.size()) - period - 1); --i)
    {
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
    this->_listCandles.back().stats.macd.signal = computeEMA(9);
    std::cerr << "MACD: " << this->_listCandles.back().stats.macd.macd <<
        ", signal: " << this->_listCandles.back().stats.macd.signal << "\n";
}
