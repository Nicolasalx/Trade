/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** main
*/

#include "trade.hpp"
#include "my_log.hpp"

int main(void)
{
    Tr::Trade trade;

    std::srand(time(nullptr));
    try {
        trade.engineTrading();
    } catch (const std::exception &exception) {
        my::log::error(exception.what());
        return 84;
    }
    return 0;
}
