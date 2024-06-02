/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** movingAverage
*/

#include "trade.hpp"

double Tr::Trade::computeMovingAverage(std::vector<candle_t> candlesCrypto, int period)
{
    double movingAverage = 0;
    std::size_t idx = candlesCrypto.size() - period;

    for (; idx < candlesCrypto.size(); ++idx) {
        movingAverage += candlesCrypto.at(idx).close;
    }
    movingAverage /= static_cast<double>(period);
    return movingAverage;
}
