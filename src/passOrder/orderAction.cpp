/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** orderAction
*/

#include "trade.hpp"
#include "split_string.hpp"
#include "my_tracked_exception.hpp"

void Tr::Trade::increaseAmount(const std::string &currency, double amount)
{
    if (currency == "USDT" && amount > 0) {
        _stack.USDT += amount;
    } else if (currency == "BTC" && amount > 0) {
        _stack.BTC += amount;
    } else {
        throw my::tracked_exception("Order Action: The pair gived has not been recognized!");
    }
}

void Tr::Trade::decreaseAmount(const std::string &currency, double amount)
{
    if (currency == "USDT" && (_stack.USDT - amount) >= 1 && amount > 0) {
        _stack.USDT -= amount;
    } else if (currency == "BTC" && (_stack.BTC - amount) >= 0.000001 && amount > 0) {
        _stack.BTC -= amount;
    } else {
        throw my::tracked_exception("Order Action: The pair gived has not been recognized!");
    }
}

void Tr::Trade::orderAction(const std::string &pair, std::pair<double, double> lot_amountUSDT,action_e action)
{
    std::vector<std::string> lineTokens;
    my::split_string(pair, "_", lineTokens);

    if (lineTokens.size() != 2) {
        throw my::tracked_exception("Order Action: The pair need to have 2 arguments!");
    }
    if (std::abs(lot_amountUSDT.first) < 0.000001 || std::abs(lot_amountUSDT.second) < 0.000001) {
        throw my::tracked_exception("Order Action: Bad amount gived!");
    }
    if (action == BUY) {
        decreaseAmount(lineTokens[0], lot_amountUSDT.second);
        increaseAmount(lineTokens[1], lot_amountUSDT.first);
    } else if (action == SELL) {
        decreaseAmount(lineTokens[1], lot_amountUSDT.first);
        increaseAmount(lineTokens[0], lot_amountUSDT.second);
    }
}
