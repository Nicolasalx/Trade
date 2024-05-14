/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** actions
*/

#include "trade.hpp"
#include <cstring>

void Tr::Trade::checkSignal()
{
    if (_signal.action == BUY) {
        buyOnMarket(_signal.percentage);
    } else if (_signal.action == SELL) {
        sellOnMarket(_signal.percentage);
    } else {
        pass();
    }
    _signal.action = PASS;
}

void Tr::Trade::makeStatistics()
{
    computeShortMovingAverage();
    computeLongMovingAverage();
    computeBollingerBands();
    computeRSI();
    computeMACD();
}

void Tr::Trade::checkIntersectionMovingAverage()
{

}

void Tr::Trade::analyseOfTheMarket()
{
    checkIntersectionMovingAverage();
    std::cerr << "To Buy = " <<
        (_listCandles.back().stats.bollinger_bands.weirdness * 100.0)
            * (this->_max_order_percentage / 100.0) << '\n';
}

void Tr::Trade::manageAnAction()
{
    makeStatistics();
    analyseOfTheMarket();

    checkSignal();
}

/* Algorithm to use

- Check if the switch doesn't appear to fast (Set a locktime where we can't place order on this pair, only on this pair)

*/
