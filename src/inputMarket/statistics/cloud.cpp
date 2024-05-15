/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** cloud
*/

#include "trade.hpp"

double Tr::Trade::cloudAverage(std::size_t period)
{
    double average = 0.0;

    for (int i = (this->_listCandles.size() - 1);
        i >= (int(this->_listCandles.size()) - period - 1); --i)
    {
        average = this->_listCandles.at(i).low + this->_listCandles.at(i).high;
    }
    return average / 2.0;
}

void Tr::Trade::computeCloud()
{
    if (this->_listCandles.size() <= 26) {
        return;
    }
    this->_listCandles.back().stats.cloud.tenkanSen9 = cloudAverage(9);
    this->_listCandles.back().stats.cloud.kijunSen26 = cloudAverage(26);
    
    this->_listCandles.back().stats.cloud.lagging26 =
        this->_listCandles.at(this->_listCandles.size() - 26 - 1).close;

    this->_listCandles.back().stats.cloud.senkouSpanA = (
        this->_listCandles.back().stats.cloud.tenkanSen9 +
        this->_listCandles.back().stats.cloud.kijunSen26) / 2.0;

    this->_listCandles.back().stats.cloud.senkouSpanB = cloudAverage(26);

    std::cerr << this->_listCandles.back().stats.cloud.tenkanSen9 << "___"
        << this->_listCandles.back().stats.cloud.kijunSen26 << "___"
        << this->_listCandles.back().stats.cloud.lagging26 << "___"
        << this->_listCandles.back().stats.cloud.senkouSpanA << "___"
        << this->_listCandles.back().stats.cloud.senkouSpanB << '\n';
}
