/*
** EPITECH PROJECT, 2024
** Trade
** File description:
** orderAction
*/

#include "trade.hpp"
#include "split_string.hpp"
#include "my_tracked_exception.hpp"

void Tr::Trade::increaseAmount(const std::string &currency, double amount)
{
    if (currency == "USDT") {
        _stack.USDT += amount;
    } else if (currency == "BTC") {
        _stack.BTC += amount;
    } else {
        throw my::tracked_exception("Order Action: The pair gived has not been recognized!");
    }
}

void Tr::Trade::decreaseAmount(const std::string &currency, double amount)
{
    double amountToDecrease = _listCandles.back().close * amount;

    if (currency == "USDT" && (_stack.USDT - amountToDecrease) > 0) {
        _stack.USDT -= (amountToDecrease + amountToDecrease * _settings.transaction_fee_percent);
    } else if (currency == "BTC" && (_stack.BTC - amountToDecrease) > 0) {
        _stack.BTC -= (amountToDecrease + amountToDecrease * _settings.transaction_fee_percent);
    } else {
        throw my::tracked_exception("Order Action: The pair gived has not been recognized!");
    }
}

void Tr::Trade::orderAction(const std::string &pair, double amount, action_e action)
{
    std::vector<std::string> lineTokens;
    my::split_string(pair, "_", lineTokens);

    if (lineTokens.size() != 2) {
        throw my::tracked_exception("Order Action: The pair need to have 2 arguments!");
    }
    if (action == BUY) {
        decreaseAmount(lineTokens[0], amount);
        increaseAmount(lineTokens[1], amount);
    } else if (action == SELL) {
        decreaseAmount(lineTokens[1], amount);
        increaseAmount(lineTokens[0], amount);
    }
}
