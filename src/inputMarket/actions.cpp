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
    _signal.percentage = 0;
}

void Tr::Trade::makeStatistics()
{
    computeShortMovingAverage();
    computeLongMovingAverage();
    computeBollingerBands();
    computeRSI();
    computeMACD();
    averageCandle(20);
    relativeCandle(20);
    deviationCandle(20);
}

void Tr::Trade::checkIntersectionMovingAverage()
{
    std::size_t idx = _listCandles.size() - 1;

    if (_listCandles.at(idx).stats.moving_average.lastMMShort > _listCandles.at(idx).stats.moving_average.lastMMLong
        && _listCandles.at(idx - 1).stats.moving_average.lastMMShort <= _listCandles.at(idx - 1).stats.moving_average.lastMMLong) {
            isInBearRun = false;
    }
    if (_listCandles.at(idx).stats.moving_average.lastMMShort < _listCandles.at(idx).stats.moving_average.lastMMLong
        && _listCandles.at(idx - 1).stats.moving_average.lastMMShort >= _listCandles.at(idx - 1).stats.moving_average.lastMMLong) {
            isInBearRun = true;
    }
}

void Tr::Trade::checkRSIValue()
{
    if ((_listCandles.back().stats.rsi.rsi > 70 || _listCandles.back().close > _listCandles.back().stats.bollinger_bands.upperBand) && orderOpen == true) {
        _signal.action = Tr::Trade::SELL;
        _signal.percentage = 0.0;
    } else if ((_listCandles.back().stats.rsi.rsi < 30 || _listCandles.back().close < _listCandles.back().stats.bollinger_bands.lowerBand) && orderOpen == false) {
        _signal.action = Tr::Trade::BUY;
        _signal.percentage = 0.0;
    }
}

void Tr::Trade::checkMACD()
{
    std::size_t idx = _listCandles.size() - 1;

    if (this->_listCandles.at(idx).stats.macd.macd > this->_listCandles.at(idx).stats.macd.signal &&
        this->_listCandles.at(idx - 1).stats.macd.macd < this->_listCandles.at(idx - 1).stats.macd.signal) {
            _signal.action = BUY;
    }
}

void Tr::Trade::analyseOfTheMarket()
{
    checkIntersectionMovingAverage();
    
    if (isInBearRun == true) {
        return;
    } 
    checkRSIValue();
    //checkMACD();

    //this->_signal.percentage =
    //    (_listCandles.back().stats.bollinger_bands.weirdness * 100.0)
    //        * (this->_max_order_percentage / 100.0);
    //if (this->_signal.percentage > 0) {
    //    this->_signal.action = Tr::Trade::BUY;
    //    this->_signal.percentage = 0.0;
    //} else if (this->_signal.percentage < 0) {
    //    this->_signal.percentage = 0.0;
    //    this->_signal.action = Tr::Trade::SELL;
    //} else {
    //    this->_signal.action = Tr::Trade::PASS;
    //}
}

void Tr::Trade::manageAnAction()
{
    makeStatistics();
    analyseOfTheMarket();

    checkTPSL();
    checkSignal();
}
