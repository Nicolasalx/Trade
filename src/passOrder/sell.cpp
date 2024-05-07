/*
** EPITECH PROJECT, 2024
** Trade
** File description:
** sell
*/

#include "trade.hpp"

void Tr::Trade::sellOnMarket(double amount)
{
    std::string namePair = "";
    std::string outputSell = "";

    try {
        getPairName(namePair);
        orderAction(namePair, amount, SELL);
        outputSell = std::string("sell ") + namePair + std::to_string(amount);
        std::cout << outputSell << "\n";
    } catch(const std::exception &) {}
}
