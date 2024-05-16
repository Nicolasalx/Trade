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
    computeCloud();
}

void Tr::Trade::checkIntersectionMovingAverage()
{
    if (_listCandles.size() >= 50) {
        std::size_t idx = _listCandles.size() - 1;

        if (_listCandles.at(idx).stats.moving_average.lastMMShort > _listCandles.at(idx).stats.moving_average.lastMMLong) {
            if (_listCandles.at(idx - 1).stats.moving_average.lastMMShort <= _listCandles.at(idx - 1).stats.moving_average.lastMMLong) {
                _signal.action = Tr::Trade::BUY;
                _signal.percentage = 0.0;
            }
        }
    }
}

void Tr::Trade::checkRSIValue()
{
    if (_listCandles.size() > 20) {

        //if (_listCandles.at(idx).stats.rsi.rsi > 70 && _listCandles.at(idx - 1).stats.rsi.rsi <= 70 && _listCandles.at(idx).close > _listCandles.at(idx).stats.bollinger_bands.upperBand) {
        //    _signal.action = Tr::Trade::SELL;
        //    _signal.percentage = 0.0;
        if (_listCandles.back().stats.rsi.rsi < 30 && _listCandles.back().close < _listCandles.back().stats.bollinger_bands.lowerBand) {
            _signal.action = Tr::Trade::BUY;
            _signal.percentage = 0.0;
        }
    }
}

void Tr::Trade::analyseOfTheMarket()
{
    //checkIntersectionMovingAverage();
    //checkRSIValue();

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

void Tr::Trade::checkTPSL()
{
    if (_listCandles.size() < 20) {
        return;
    }
    std::list<order_t> newListOrder;
    bool has_take_one_order = false;

    for (const auto &order: _orderBook) {
        if (order.action == BUY && _listCandles.back().close > order.priceEntry && _listCandles.back().close > order.takeProfit && !has_take_one_order) {
            std::cout << "WIN TRADE WITH BUY\n";
            _signal.action = Tr::Trade::SELL;
            _signal.percentage = order.amountUSDT;
            has_take_one_order = true;
            info_orders.winBuy += 1;

        } else if (order.action == BUY && _listCandles.back().close < order.priceEntry && _listCandles.back().close < order.stopLoss && !has_take_one_order) {
            std::cout << "LOOSE TRADE WITH BUY\n";
            _signal.action = Tr::Trade::SELL;
            _signal.percentage = order.amountUSDT;
            has_take_one_order = true;
            info_orders.looseBuy += 1;

        } else if (order.action == SELL && _listCandles.back().close < order.priceEntry && _listCandles.back().close < order.takeProfit && !has_take_one_order) {
            std::cout << "WIN TRADE WITH SELL\n";
            _signal.action = Tr::Trade::BUY;
            _signal.percentage = order.lotSize;
            has_take_one_order = true;
            info_orders.winSell += 1;

        } else if (order.action == SELL && _listCandles.back().close > order.priceEntry && _listCandles.back().close > order.stopLoss && !has_take_one_order) {
            std::cout << "LOOSE TRADE WITH SELL\n";
            _signal.action = Tr::Trade::BUY;
            _signal.percentage = order.lotSize;
            info_orders.looseSell += 1;
            has_take_one_order = true;
        } else {
            newListOrder.push_back(order);
        }
    }
    _orderBook.clear();
    for (const auto &order: newListOrder) {
        _orderBook.push_back(order);
    }
}

void Tr::Trade::manageAnAction()
{
    makeStatistics();
    analyseOfTheMarket();

    // checkTPSL();
    checkSignal();
}
