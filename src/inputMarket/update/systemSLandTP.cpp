/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** systemSLandTP
*/

#include "trade.hpp"

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
