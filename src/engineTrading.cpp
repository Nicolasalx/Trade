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

        /*std::cout << "---------------------------------------------- SETTINGS ----------------------------------------------\n";
        std::cout << "Player Names: " << _settings.player_names << std::endl;
        std::cout << "Your Bot: " << _settings.your_bot << std::endl;
        std::cout << "Timebank: " << _settings.timebank << std::endl;
        std::cout << "Time per Move: " << _settings.time_per_move << std::endl;
        std::cout << "Candle Interval: " << _settings.candle_interval << std::endl;
        std::cout << "Candle Format: " << _settings.candle_format << std::endl;
        std::cout << "Candles Total: " << _settings.candles_total << std::endl;
        std::cout << "Candles Given: " << _settings.candles_given << std::endl;
        std::cout << "Initial Stack: " << _settings.initial_stack << std::endl;
        std::cout << "Transaction Fee Percent: " << _settings.transaction_fee_percent << std::endl;
        std::cout << "---------------------------------------------- STACKS ----------------------------------------------\n";
        std::cout << "BTC: " << _stack.BTC << std::endl;
        std::cout << "ETH: " << _stack.ETH << std::endl;
        std::cout << "USDT: " << _stack.USDT << std::endl;
        std::cout << "---------------------------------------------- ALL CANDLES ----------------------------------------------\n";
        for (const auto& candleMap : _listCandles) {
            std::cout << "--------------- CANDLE ---------------\n";
            for (const auto& pairCandle : candleMap) {
                std::cout << "Pair: " << pairCandle.first << std::endl;
                const candle_t& candle = pairCandle.second;
                std::cout << "Date: " << candle.date << std::endl;
                std::cout << "High: " << candle.high << std::endl;
                std::cout << "Low: " << candle.low << std::endl;
                std::cout << "Open: " << candle.open << std::endl;
                std::cout << "Close: " << candle.close << std::endl;
                std::cout << "Volume: " << candle.volume << std::endl;
            }
        }
        std::cout << "---------------------------------------------- END ----------------------------------------------\n";
        */
    }
}
