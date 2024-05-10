/*
** EPITECH PROJECT, 2024
** Trade
** File description:
** actions
*/

#include "trade.hpp"
#include <cstring>

void Tr::Trade::checkSignal()
{
    if (_signal.action == BUY) {
        buyOnMarket(_signal.amount);
    } else if (_signal.action == SELL) {
        sellOnMarket(_signal.amount);
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

void Tr::Trade::analyseOfTheMarket()
{

}

void Tr::Trade::manageAnAction()
{
    makeStatistics();
    analyseOfTheMarket();

    //checkSignal();
    if (_stack.USDT > 100 && _listCandles.size() > 20) {
        buyOnMarket(0.001);
    } else {
        pass();
    }
}

/* Algorithm to use

- Check if the switch doesn't appear to fast (Set a locktime where we can't place order on this pair, only on this pair)

*/
