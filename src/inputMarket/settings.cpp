/*
** EPITECH PROJECT, 2024
** Trade
** File description:
** settings
*/

#include "trade.hpp"
#include "my_tracked_exception.hpp"
#include "split_string.hpp"

void Tr::Trade::changeFormatCandle(const std::string &inputFormat)
{
    std::vector<std::string> vectorFormat;
    my::split_string(inputFormat, ",", vectorFormat);

    if (vectorFormat.size() != 7) {
        throw my::tracked_exception("Parsing Input: When you modify the candle format, the number of fields need to be at 7!");
    }
    _candleFormat.clear();
    for (const auto &field: vectorFormat) {
        if (field == "pair") {
            _candleFormat.push_back(PAIR);
        } else if (field == "date") {
            _candleFormat.push_back(DATE);
        } else if (field == "high") {
            _candleFormat.push_back(HIGH);
        } else if (field == "low") {
            _candleFormat.push_back(LOW);
        } else if (field == "open") {
            _candleFormat.push_back(OPEN);
        } else if (field == "close") {
            _candleFormat.push_back(CLOSE);
        } else if (field == "volume") {
            _candleFormat.push_back(VOLUME);
        } else {
            throw my::tracked_exception("Parsing Input: When you modify the candle format we have detected a field inexistant!");
        }
    }
}

void Tr::Trade::manageSettings(std::vector<std::string> lineTokens)
{
    if (lineTokens.size() != 3) {
        throw my::tracked_exception("Parsing Input: the number of arguments in a command settings need to be of 3!");
    }
    if (lineTokens[1] == "player_names") {
        _settings.player_names = lineTokens[2];
    } else if (lineTokens[1] == "your_bot") {
        _settings.your_bot = lineTokens[2];
    } else if (lineTokens[1] == "timebank") {
        _settings.timebank = getInt(lineTokens[2]);
    } else if (lineTokens[1] == "time_per_move") {
        _settings.time_per_move = getInt(lineTokens[2]);
    } else if (lineTokens[1] == "candle_interval") {
        _settings.candle_interval = getInt(lineTokens[2]);
    } else if (lineTokens[1] == "candle_format") {
        changeFormatCandle(lineTokens[2]);
    } else if (lineTokens[1] == "candles_total") {
        _settings.candles_total = getInt(lineTokens[2]);
    } else if (lineTokens[1] == "candles_given") {
        _settings.candles_given = getInt(lineTokens[2]);
    } else if (lineTokens[1] == "initial_stack") {
        _settings.initial_stack = getInt(lineTokens[2]);
        _stack.USDT = _settings.initial_stack;
    } else if (lineTokens[1] == "transaction_fee_percent") {
        _settings.transaction_fee_percent = getDouble(lineTokens[2]);
    } else {
        throw my::tracked_exception("Parsing Input: in the update the second argument is unrecognized!");
    }
}
