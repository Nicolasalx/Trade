/*
** EPITECH PROJECT, 2024
** Trade
** File description:
** bollingerBands
*/

#include "trade.hpp"

void Tr::Trade::checkOnePairBolBand(std::size_t period, double inputMoney, double outputMoney)
{
    double centralBand = 0;
    double upperBand = 0;
    double lowerBand = 0;

    centralBand = computeMovingAverage(_listCandles, period);
    upperBand = centralBand + (2 * computeStandardDeviation(_listCandles, period));
    lowerBand = centralBand - (2 * computeStandardDeviation(_listCandles, period));

    (void)upperBand;
    (void)lowerBand;
    (void)inputMoney;
    (void)outputMoney;
}

// Bande de Bollinger
void Tr::Trade::computeBollingerBands()
{
    std::size_t period = 20;

    if (_listCandles.size() < period) {
        return;
    }
    checkOnePairBolBand(period, _stack.USDT, _stack.BTC);
}
