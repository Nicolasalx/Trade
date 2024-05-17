/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** buy
*/

#include "trade.hpp"
#include "my_tracked_exception.hpp"

void Tr::Trade::buyOnMarket(double percentage)
{
    std::string namePair = "";
    std::string outputBuy = "";

    try {
        getPairName(namePair);

        if (percentage > 0.0) {
            std::pair<double, double> lot_amountUSDT = computeSimpleOrder(BUY, percentage); // computeOrderSize(BUY, percentage);
            orderAction(namePair, lot_amountUSDT, BUY);
            outputBuy = std::string("buy ") + namePair + " " + std::to_string(lot_amountUSDT.first);
            std::cout << outputBuy << "\n";
        } else {
            std::pair<double, double> lot_amountUSDT = computeLotSize(BUY); // computeOrderSize(BUY, percentage);
            orderAction(namePair, lot_amountUSDT, BUY);
            outputBuy = std::string("buy ") + namePair + " " + std::to_string(lot_amountUSDT.first);
            std::cout << outputBuy << "\n";
        }
        orderOpen = true;
        std::cerr << "BTC: " << _stack.BTC << " / USDT: " << _stack.USDT << "\n"; 
    } catch(const my::tracked_exception &exception) {
        pass();
    }
}
