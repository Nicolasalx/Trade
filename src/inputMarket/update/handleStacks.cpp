/*
** EPITECH PROJECT, 2024
** Trade
** File description:
** handleStacks
*/

#include "trade.hpp"
#include "split_string.hpp"
#include "my_tracked_exception.hpp"

void Tr::Trade::setAmountToOneCrypto(const std::string &dataCrypto)
{
    std::vector<std::string> dataAmount;
    my::split_string(dataCrypto, ":", dataAmount);

    if (dataAmount.size() != 2) {
        throw my::tracked_exception("Parsing Input: In the command stacks when we delimited by ':' we need to have a currency and an amount!");
    }
    if (dataAmount.at(0) == "BTC") {
        _stack.BTC = getDouble(dataAmount.at(1));
    } else if (dataAmount.at(0) == "USDT") {
        _stack.USDT = getDouble(dataAmount.at(1));        
    } else {
        throw my::tracked_exception("Parsing Input: In the command stacks, the currency was not recognized");
    }
}

void Tr::Trade::handleStacks(const std::string &inputStacks)
{
    std::vector<std::string> dataEachAmount;
    my::split_string(inputStacks, ",", dataEachAmount);

    if (dataEachAmount.size() != 3) {
        throw my::tracked_exception("Parsing Input: In the command stacks the 3 pairs are not present!");
    }
    for (const auto &crypto: dataEachAmount) {
        setAmountToOneCrypto(crypto);
    }
}
