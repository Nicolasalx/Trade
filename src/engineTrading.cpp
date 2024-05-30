/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** engineTrading
*/

#include "trade.hpp"

void Tr::Trade::engineTrading()
{
    initCandleFormat();
    while (!_stopLoop) {
        parseInputMarket();
        if (this->_stopLoop) {
            break;
        }
    }
}
