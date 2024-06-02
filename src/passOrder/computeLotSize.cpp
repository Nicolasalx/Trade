/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** computeLotSize
*/

#include "trade.hpp"
#include "my_tracked_exception.hpp"

double Tr::Trade::getAmountPortfolio()
{
    double amountUSDT = _stack.USDT;
    double amountBTC = _stack.BTC * _listCandles.back().close;

    return amountUSDT + amountBTC;
}

std::pair<double, double> Tr::Trade::computeOrderSize(action_e action, double percentage)
{
    if (action == BUY) {
        double amountPortfolio = getAmountPortfolio();
        double amountToBet = amountPortfolio - (amountPortfolio * ((100.0 - percentage) * 0.01));
        double amountAfterFees = amountToBet - ((amountToBet * _settings.transaction_fee_percent) / 100.0);
        double sizeLot = amountAfterFees / _listCandles.back().close;

        if (_stack.USDT - amountToBet < 0) {
            amountToBet = _stack.USDT;
            amountAfterFees = amountToBet - ((amountToBet * _settings.transaction_fee_percent) / 100.0);
            sizeLot = amountAfterFees / _listCandles.back().close;
        }
        return std::make_pair(sizeLot, amountToBet);
    } else {
        double amountPortfolio = getAmountPortfolio();
        double amountToBet = amountPortfolio - (amountPortfolio * ((100.0 - percentage) * 0.01));
        double amountAfterFees = amountToBet - ((amountToBet * _settings.transaction_fee_percent) / 100.0);
        double sizeLot = amountAfterFees / _listCandles.back().close;
        double newSizeLot = sizeLot;

        if (_stack.BTC - sizeLot < 0) {
            newSizeLot = _stack.BTC;
            amountAfterFees = (newSizeLot * amountAfterFees) / sizeLot;
        }
        return std::make_pair(newSizeLot, amountAfterFees);
    }
}

std::pair<double, double> Tr::Trade::computeLotSize2(action_e action, double percentage)
{
    double percentageTP = 5.0;
    double percentageSL = 5.0;

    if (action == BUY) {
        double amountToBet = _stack.USDT - (_stack.USDT * ((100.0 - percentage) * 0.01));
        double amountAfterFees = amountToBet - ((amountToBet * _settings.transaction_fee_percent) / 100.0);
        double sizeLot = amountAfterFees / _listCandles.back().close;

        order_t order;

        order.action = BUY;
        order.amountUSDT = amountToBet;
        order.lotSize = sizeLot;
        order.priceEntry = _listCandles.back().close;
        order.takeProfit = order.priceEntry * (1 + (percentageTP * 0.01));
        order.stopLoss = order.priceEntry * (1 - (percentageSL * 0.01));

        _orderBook.push_back(order);
        _finalBook.push_back(order);
        return std::make_pair(sizeLot, amountToBet);

    } else {
        double sizeLot = _stack.BTC - (_stack.BTC * ((100.0 - percentage) * 0.01));
        double lotAfterFees = sizeLot - ((sizeLot * _settings.transaction_fee_percent) / 100.0);
        double amountToBet = lotAfterFees * _listCandles.back().close;

        order_t order;
        
        order.action = SELL;
        order.amountUSDT = amountToBet;
        order.lotSize = sizeLot;
        order.priceEntry = _listCandles.back().close;
        order.takeProfit = order.priceEntry * (1 + (percentageTP * 0.01));
        order.stopLoss = order.priceEntry * (1 - (percentageSL * 0.01));
        
        _orderBook.push_back(order);
        _finalBook.push_back(order);
        return std::make_pair(sizeLot, amountToBet);
    }
}

std::pair<double, double> Tr::Trade::computeSimpleOrder(action_e action, double amount)
{
    if (action == BUY) {
        double newSizeLot = amount - ((amount * _settings.transaction_fee_percent) / 100.0);
        double amountInUSDT = newSizeLot * _listCandles.back().close;

        if (_stack.USDT - amountInUSDT < 0) {
            double partToKeep = 2.0;
            amountInUSDT = _stack.USDT - ((_stack.USDT * partToKeep) / 100.0);
            double amountWithoutFees = amountInUSDT - ((amountInUSDT * _settings.transaction_fee_percent) / 100.0);
            amount = amountWithoutFees / _listCandles.back().close;
        }
        return std::make_pair(amount, amountInUSDT);
    } else {
        double newAmount = amount + ((amount * _settings.transaction_fee_percent) / 100.0);
        double sizeLot = newAmount / _listCandles.back().close;

        if (_stack.BTC - sizeLot <= 0) {
            double partToKeep = 1.0;
            sizeLot = _stack.BTC - ((_stack.BTC * partToKeep) / 100.0);
            double lotWithoutFees = sizeLot + ((sizeLot * _settings.transaction_fee_percent) / 100.0);
            amount = lotWithoutFees * _listCandles.back().close;
        }
        return std::make_pair(sizeLot, amount);
    }
}

std::pair<double, double> Tr::Trade::computeLotSize(action_e action)
{
    /*
        The parameters are as follows:
            riskPercentage = 2%
            accountBalance = If BUY then _stack.USDT / If SELL then (_stack.BTC * _listCandle.back().close)
            entryPrice = PE as defined
            stopLoss = SL as defined
    */

    double percentageTP = 4.0;
    double percentageSL = 3.0;
    double riskPercentage = 99.0;
    double riskPerTrade = riskPercentage / 100.0;
    double accountBalance = 0.0;
    double entryPrice = _listCandles.back().close;
    double stopLoss = 0.0;

    if (action == BUY) {
        stopLoss = entryPrice * (1 - (percentageSL * 0.01));
    } else {
        stopLoss = entryPrice * (1 + (percentageTP * 0.01));
    }

    if (action == BUY) {
        accountBalance = _stack.USDT;
    } else {
        accountBalance = _stack.BTC * entryPrice;
    }

    double riskAmount = accountBalance * riskPerTrade;
    double difference = entryPrice - stopLoss;
    double positionSize = riskAmount / difference;
    double amountToBet = positionSize * difference;
    double sizeLot = amountToBet / entryPrice;

    order_t order;

    if (action == BUY) {
        double amountAfterFees = amountToBet - (amountToBet * (_settings.transaction_fee_percent / 100.0));
        double newSizeLot = (amountAfterFees * sizeLot) / amountToBet;

        order_t order;

        order.action = BUY;
        order.amountUSDT = amountToBet;
        order.lotSize = newSizeLot;
        order.priceEntry = _listCandles.back().close;
        order.takeProfit = order.priceEntry * (1 + (percentageTP * 0.01));
        order.stopLoss = order.priceEntry * (1 - (percentageSL * 0.01));

        if (newSizeLot > 0 && amountToBet > 1 && _stack.USDT - amountToBet > 0) {
            _orderBook.push_back(order);
            _finalBook.push_back(order);
        } else {
            throw my::tracked_exception("Failed to BUY amount is 0!");
        }
        return std::make_pair(newSizeLot, amountToBet);
    } else {
        double sizeLotAfterFees = sizeLot - (sizeLot * (_settings.transaction_fee_percent / 100.0));
        double newAmountToBet = (sizeLotAfterFees * amountToBet) / sizeLot;

        order_t order;

        order.action = SELL;
        order.amountUSDT = newAmountToBet;
        order.lotSize = sizeLot;
        order.priceEntry = _listCandles.back().close;
        order.takeProfit = order.priceEntry * (1 + (percentageTP * 0.01));
        order.stopLoss = order.priceEntry * (1 - (percentageSL * 0.01));

        if (sizeLot > 0 && newAmountToBet > 1 && _stack.BTC - sizeLot > 0) {
            _orderBook.push_back(order);
            _finalBook.push_back(order);

        } else {
            throw my::tracked_exception("Failed to SELL amount is 0!");
        }
        return std::make_pair(sizeLot, newAmountToBet);
    }
}
