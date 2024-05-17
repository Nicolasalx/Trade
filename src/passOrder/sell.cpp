/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** sell
*/

#include "trade.hpp"
#include "my_tracked_exception.hpp"

void Tr::Trade::sellOnMarket(double percentage)
{
    std::string namePair = "";
    std::string outputSell = "";

    try {
        getPairName(namePair);

        if (percentage > 0.0) {
            std::pair<double, double> lot_amountUSDT = computeSimpleOrder(SELL, percentage);// computeOrderSize(SELL, percentage);
            orderAction(namePair, lot_amountUSDT, SELL);
            outputSell = std::string("sell ") + namePair + " " + std::to_string(lot_amountUSDT.first);
            std::cout << outputSell << "\n";
            std::cerr << outputSell << "\n";
        } else {
            std::pair<double, double> lot_amountUSDT = computeLotSize(SELL);// computeOrderSize(SELL, percentage);
            orderAction(namePair, lot_amountUSDT, SELL);
            outputSell = std::string("sell ") + namePair + " " + std::to_string(lot_amountUSDT.first);
            std::cout << outputSell << "\n";
            std::cerr << outputSell << "\n";
        }
        orderOpen = false;
        std::cerr << "BTC: " << _stack.BTC << " / USDT: " << _stack.USDT << "\n"; 
    } catch(const my::tracked_exception &exception) {
        pass();
    }
}
