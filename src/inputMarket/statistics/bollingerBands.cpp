/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** bollingerBands
*/

#include "trade.hpp"

void Tr::Trade::checkOnePairBolBand(std::size_t period)
{
    double centralBand = 0;
    double upperBand = 0;
    double lowerBand = 0;

    centralBand = computeMovingAverage(_listCandles, period);
    upperBand = centralBand + (2 * computeStandardDeviation(_listCandles, period));
    lowerBand = centralBand - (2 * computeStandardDeviation(_listCandles, period));

    _listCandles.back().stats.bollinger_bands.upperBand = upperBand;
    _listCandles.back().stats.bollinger_bands.centralBand = centralBand;
    _listCandles.back().stats.bollinger_bands.lowerBand = lowerBand;
    _listCandles.back().stats.bollinger_bands.weirdness =
        (_listCandles.back().close - lowerBand) / (upperBand - lowerBand);
}

// Bande de Bollinger
void Tr::Trade::computeBollingerBands()
{
    std::size_t period = 20;

    if (_listCandles.size() < period) {
        return;
    }
    checkOnePairBolBand(period);
}
