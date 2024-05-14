/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** computeLotSize
*/

#include "trade.hpp"

std::pair<double, double> Tr::Trade::computeLotSize(action_e action, double accountBalance, double priceEntry, double stopLoss)
{
    /*
        Les paramètres sont les suivants:
            riskPercentage = 2%
            accountBalance = Si c'est du BUY alors on donne _stack.USDT / Si c'est du SELL alors on donne (_stack.BTC * _listCandle.back().close)
            priceEntry = PE qu'on a défini
            stopLoss = SL qu'on a défini
    */

    double riskPercentage = 2.0;
    double riskAmount = (riskPercentage / 100.0) * accountBalance;
    double difference = std::abs(priceEntry - stopLoss);
    double sizeLot = riskAmount / difference;
    double amountToBet = sizeLot * priceEntry;
    order_t order;

    // Part with transaction fees
    if (action == BUY) {
        double amountAfterFees = amountToBet - (amountToBet * (_settings.transaction_fee_percent / 100.0));
        double newSizeLot = (amountAfterFees * sizeLot) / amountToBet;

        //order.stopLoss = stopLoss;
        //order.takeProfit = takeProfit;
        //order.action = BUY;
        //order.lotSize = newSizeLot;
        //_orderBook.push_back(order);

        //for (const auto &ord: _orderBook) {
        //    std::cout << ord.lotSize << "\n";
        //}

        // We return amountToBet and not amountAfterFees because only the sizeLot decrease
        return std::make_pair(newSizeLot, amountToBet);
    } else {
        double sizeLotAfterFees = sizeLot - (sizeLot * (_settings.transaction_fee_percent / 100.0));
        double newamountToBet = (sizeLotAfterFees * amountToBet) / sizeLot;

        //order.stopLoss = stopLoss;
        //order.takeProfit = takeProfit;
        //order.action = SELL;
        //order.lotSize = sizeLot;
        //_orderBook.push_back(order);

        //for (const auto &ord: _orderBook) {
        //    std::cout << ord.lotSize << "\n";
        //}

        // We return sizeLot and not sizeLotAfterFees because only the amountToBet decrease
        return std::make_pair(sizeLot, newamountToBet);
    }
}
