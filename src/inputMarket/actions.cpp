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
    computeMovingAvgOpenClose();
    computeMovingAverageVolume();
    computeShortMovingAverage();
    computeExtremelyLongMovingAverage();
    computeLongMovingAverage();
    computeBollingerBands();
    computeRSI();
    computeMACD();
    averageCandle(20);
    relativeCandle(20);
    deviationCandle(20);
}

void Tr::Trade::checkSwitchTendance()
{
    std::size_t idx = _listCandles.size() - 1;

    // if (_listCandles.at(idx).stats.moving_average.lastMMShort20 > _listCandles.at(idx).stats.moving_average.lastMMLong50
    //         && _listCandles.at(idx - 1).stats.moving_average.lastMMShort20 <= _listCandles.at(idx - 1).stats.moving_average.lastMMLong50) {
    //             isInBearRun = false;
    //     }
    //     if (_listCandles.at(idx).stats.moving_average.lastMMShort20 < _listCandles.at(idx).stats.moving_average.lastMMLong50
    //         && _listCandles.at(idx - 1).stats.moving_average.lastMMShort20 >= _listCandles.at(idx - 1).stats.moving_average.lastMMLong50) {
    //             isInBearRun = true;
    //             _signal.action = SELL;
    //             _signal.percentage = 100000;
    //             _orderBook.clear();
    //     }
    //     return;

    if (_listCandles.back().stats.volume.diffOpenClose < -300) {
        if (_listCandles.at(idx).stats.moving_average.lastMMShort20 > _listCandles.at(idx).stats.moving_average.lastMMLong50
            && _listCandles.at(idx - 1).stats.moving_average.lastMMShort20 <= _listCandles.at(idx - 1).stats.moving_average.lastMMLong50) {
                isInBearRun = false;
        }
        if (_listCandles.at(idx).stats.moving_average.lastMMShort20 < _listCandles.at(idx).stats.moving_average.lastMMLong50
            && _listCandles.at(idx - 1).stats.moving_average.lastMMShort20 >= _listCandles.at(idx - 1).stats.moving_average.lastMMLong50) {
                isInBearRun = true;
                _signal.action = SELL;
                _signal.percentage = 100000;
                _orderBook.clear();
        }
        return;
    }

    if (_listCandles.at(idx).stats.moving_average.lastMMLong50 > _listCandles.at(idx).stats.moving_average.lastMMExtremelyLong200
        && _listCandles.at(idx - 1).stats.moving_average.lastMMLong50 <= _listCandles.at(idx - 1).stats.moving_average.lastMMExtremelyLong200) {
            isInBearRun = false;
    }
    if (_listCandles.at(idx).stats.moving_average.lastMMLong50 < _listCandles.at(idx).stats.moving_average.lastMMExtremelyLong200
        && _listCandles.at(idx - 1).stats.moving_average.lastMMLong50 >= _listCandles.at(idx - 1).stats.moving_average.lastMMExtremelyLong200) {
            isInBearRun = true;
            _signal.action = SELL;
            _signal.percentage = 100000;
            _orderBook.clear();
    }
}

void Tr::Trade::boolingerBandsRsiAlgorithm()
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

void Tr::Trade::candleAlgorithm()
{
    /*
        This strategy consist to check the two last volume and if they are above the moving average 200 AND if they are both positive candle => It's a signal
    */
    if (_listCandles.size() < 3) {
        return;
    }

    std::size_t idx = _listCandles.size() - 1;
    double precedentMid = std::abs(_listCandles.at(idx - 1).close - _listCandles.at(idx - 1).open);
    double differenceMid = std::abs(_listCandles.back().close - _listCandles.back().open);
    double differenceLow = std::abs(_listCandles.back().close - _listCandles.back().low);

    if (differenceLow >= differenceMid && _listCandles.at(idx).close < _listCandles.at(idx).open &&
        precedentMid <= differenceMid && orderOpen == false) {
        _signal.action = BUY;
        toDel = true;
    }
}

void Tr::Trade::displayBoardOrder()
{
    for (const auto &order: _finalBook) {
        if (order.action == BUY) {
            std::cerr << "BUY ORDER => ";
        }
        std::cerr << "Entry Price: " << order.priceEntry << " / Take Profit: " << order.takeProfit << " / Stop Loss: " << order.stopLoss << "\n";
    }
    std::cerr << "\n\n-------------------------------\n";
    std::cerr << "---   REPORT ORDER BOOK:" << "    ---\n";
    std::cerr << "---   NB WIN BUY: " << info_orders.winBuy << "         ---\n";
    std::cerr << "---   NB LOOSE BUY: " << info_orders.looseBuy << "       ---\n";
    std::cerr << "-------------------------------\n";
}

void Tr::Trade::analyseOfTheMarket()
{
    checkSwitchTendance();

    if (_listCandles.size() == this->_settings.candles_total) {
        displayBoardOrder();
        return;
    }
    if (isInBearRun == true) {
        return;
    }
    boolingerBandsRsiAlgorithm();
    candleAlgorithm();
}

void Tr::Trade::manageAnAction()
{
    makeStatistics();
    analyseOfTheMarket();

    checkTPSL();
    checkSignal();
}
