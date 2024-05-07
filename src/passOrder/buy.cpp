/*
** EPITECH PROJECT, 2024
** Trade
** File description:
** buy
*/

#include "trade.hpp"

void Tr::Trade::buyOnMarket(double amount)
{
    std::string namePair = "";
    std::string outputBuy = "";

    try {
        getPairName(namePair);
        orderAction(namePair, amount, BUY);
        outputBuy = std::string("buy ") + namePair + " " + std::to_string(amount);
        std::cout << outputBuy << "\n";
    } catch(const std::exception &) {}
}
