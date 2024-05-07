/*
** EPITECH PROJECT, 2024
** Trade
** File description:
** movingAverage
*/

#include "trade.hpp"

double Tr::Trade::computeMovingAverage(std::vector<candle_t> candlesCrypto, int period)
{
    double movingAverage = 0;
    std::size_t idx = candlesCrypto.size() - period;

    for (idx = 0; idx < candlesCrypto.size(); ++idx) {
        //std::cout << "Close value for index " << idx << ": " << candlesCrypto.at(idx).close << std::endl;
        movingAverage += candlesCrypto.at(idx).close;
    }
    return (movingAverage /= static_cast<double>(period));
}
