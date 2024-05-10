/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** rsi
*/

#include "trade.hpp"

void Tr::Trade::computeRSI()
{
    std::size_t period = 14;
    std::vector<double> changes;
    std::vector<double> gains;
    std::vector<double> losses;
    double avg_gain = 0.0;
    double avg_loss = 0.0;
    std::size_t idx = 0;
    double rs = 0.0;
    double rsi = 0.0;

    if (_listCandles.size() <= period) {
        return;
    }
    idx = _listCandles.size() - period;
    for (; idx < _listCandles.size(); ++idx) {
        changes.push_back(_listCandles.at(idx).close - _listCandles.at(idx - 1).close);
    }
    for (const auto &chg: changes) {
        if (chg > 0) {
            gains.push_back(chg);
        } else {
            losses.push_back(chg);
        }
    }
    for (const auto &gain: gains) {
        avg_gain += gain;
    }
    for (const auto &loss: losses) {
        avg_loss += -loss;
    }
    avg_gain /= period;
    avg_loss /= period;
    rs = avg_gain / avg_loss;
    rsi = 100.0 - (100.0 / (1.0 + rs));
    _listCandles.back().stats.rsi.rsi = rsi;

    // std::cout << "RSI: " << rsi << "\n";
}
