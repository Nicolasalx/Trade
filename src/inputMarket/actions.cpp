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
    computeMovingAverage200Volume();
}

void Tr::Trade::checkSwitchTendance()
{
    std::size_t idx = _listCandles.size() - 1;

    if (_listCandles.at(idx).stats.moving_average.lastMMShort > _listCandles.at(idx).stats.moving_average.lastMMLong
        && _listCandles.at(idx - 1).stats.moving_average.lastMMShort <= _listCandles.at(idx - 1).stats.moving_average.lastMMLong) {
            isInBearRun = false;
    }
    if (_listCandles.at(idx).stats.moving_average.lastMMShort < _listCandles.at(idx).stats.moving_average.lastMMLong
        && _listCandles.at(idx - 1).stats.moving_average.lastMMShort >= _listCandles.at(idx - 1).stats.moving_average.lastMMLong) {
            isInBearRun = true;
            _signal.action = SELL;
            _signal.percentage = 100000;
            _orderBook.clear();
    }
}

void Tr::Trade::checkRSIValue()
{
    if ((_listCandles.back().stats.rsi.rsi < 30 || _listCandles.back().close < _listCandles.back().stats.bollinger_bands.lowerBand) && orderOpen == false) {
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

#include <iomanip>

void Tr::Trade::checkMAVolume()
{
    /*
        This strategy consist to check the two last volume and if they are above the moving average 200 AND if they are both positive candle => It's a signal
    */

    std::size_t idx = _listCandles.size() - 1;
    //if (_listCandles.at(idx).volume > _listCandles.at(idx).stats.volume.movingAverage200 && _listCandles.at(idx).close > _listCandles.at(idx).open &&
    //    _listCandles.at(idx - 1).volume > _listCandles.at(idx - 1).stats.volume.movingAverage200 && _listCandles.at(idx - 1).close > _listCandles.at(idx - 1).open && orderOpen == false) {
    //    std::cerr << std::fixed << "VOLUME: " << std::setprecision(2) << _listCandles.back().volume << " / MA200: " << _listCandles.back().stats.volume.movingAverage200 << "\n";
    //    _signal.action = BUY;
    //}

    //if (_listCandles.at(idx).volume > _listCandles.at(idx).stats.volume.movingAverage200 && _listCandles.at(idx).close < _listCandles.at(idx).open) {
    //    _signal.action = PASS;
    //}

    double precedentMid = std::abs(_listCandles.at(idx - 1).close - _listCandles.at(idx - 1).open);
    double differenceMid = std::abs(_listCandles.back().close - _listCandles.back().open);
    double differenceLow = std::abs(_listCandles.back().close - _listCandles.back().low);
    if (differenceLow >= differenceMid && _listCandles.at(idx).close < _listCandles.at(idx).open &&
        precedentMid <= differenceMid) {
        std::cerr << "MAYBE PE: " << _listCandles.back().close << "\n";
        _signal.action = BUY;
        toDel = true;
    }
}

void Tr::Trade::analyseOfTheMarket()
{
    checkSwitchTendance();

    if (isInBearRun == true) {
        return;
    }

    //checkRSIValue();
    checkMAVolume();
    //checkMACD();
}

void Tr::Trade::manageAnAction()
{
    makeStatistics();
    analyseOfTheMarket();

    checkTPSL();
    checkSignal();
}
