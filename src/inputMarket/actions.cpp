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

void Tr::Trade::checkOnePair()
{
    // Make action to check if we buy sell or pass
}

void Tr::Trade::checkMMLongAndShort()
{
    if (_listCandles.size() < 50) {
        return;
    }
    checkOnePair();
}

void Tr::Trade::manageAnAction()
{
    computeShortMovingAverage();
    computeLongMovingAverage();
    computeBollingerBands();

    // Indicator to check if the moving average short change of trend with moving average long
    checkMMLongAndShort();

    checkSignal();

    if (_stack.USDT > 100) {
        buyOnMarket(0.1);
    }
}

/* Algorithm to use

- Check if the switch doesn't appear to fast (Set a locktime where we can't place order on this pair, only on this pair)

*/
