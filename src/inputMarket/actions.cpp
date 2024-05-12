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

bool buy = false;
bool sell = false;

void Tr::Trade::manageAnAction()
{
    makeStatistics();
    analyseOfTheMarket();

    //checkSignal();
    if (_listCandles.size() > 20) {
        if (buy == false) {
            buyOnMarket(0.001);
            buy = true;
        } else if (sell == false) {
            sellOnMarket(0.001);
            sell = true;
        } else {
            pass();
        }
    } else {
        pass();
    }
}

/* Algorithm to use

- Check if the switch doesn't appear to fast (Set a locktime where we can't place order on this pair, only on this pair)

*/
