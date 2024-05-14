/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** sell
*/

#include "trade.hpp"

void Tr::Trade::sellOnMarket(double percentage)
{
    std::string namePair = "";
    std::string outputSell = "";

    try {
        getPairName(namePair);
        std::pair<double, double> lot_amountUSDT = computeLotSize(SELL, _stack.USDT, 60000, 58000);
        orderAction(namePair, lot_amountUSDT, SELL);
        outputSell = std::string("sell ") + namePair + " " + std::to_string(lot_amountUSDT.first);
        std::cout << outputSell << "\n";
    } catch(const std::exception &) {}
}
