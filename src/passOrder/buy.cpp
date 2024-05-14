/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** buy
*/

#include "trade.hpp"

void Tr::Trade::buyOnMarket(double percentage)
{
    std::string namePair = "";
    std::string outputBuy = "";

    try {
        getPairName(namePair);
        std::pair<double, double> lot_amountUSDT = computeLotSize(BUY, _stack.USDT, 60000, 58000);
        orderAction(namePair, lot_amountUSDT, BUY);
        outputBuy = std::string("buy ") + namePair + " " + std::to_string(lot_amountUSDT.first);
        std::cout << outputBuy << "\n";
    } catch(const std::exception &exception) {
        std::cerr << exception.what() << "\n";
    }
}
