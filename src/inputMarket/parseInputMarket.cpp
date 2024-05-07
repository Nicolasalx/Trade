/*
** EPITECH PROJECT, 2024
** Trade
** File description:
** parsing
*/

#include "trade.hpp"
#include "split_string.hpp"
#include "my_tracked_exception.hpp"

void Tr::Trade::initCandleFormat()
{
    _candleFormat.push_back(PAIR);
    _candleFormat.push_back(DATE);
    _candleFormat.push_back(HIGH);
    _candleFormat.push_back(LOW);
    _candleFormat.push_back(OPEN);
    _candleFormat.push_back(CLOSE);
    _candleFormat.push_back(VOLUME);
}

void Tr::Trade::selectCommand(const std::string &input)
{
    std::vector<std::string> lineTokens;
    my::split_string(input, " ", lineTokens);

    if (lineTokens.empty()) {
        return;
    }
    if (lineTokens[0] == "settings") {
        manageSettings(lineTokens);
    } else if (lineTokens[0] == "update" && lineTokens[1] == "game") {
        manageAnUpdate(lineTokens);
    } else if (lineTokens[0] == "action") {
        manageAnAction();
    } else {
        throw my::tracked_exception("Parsing Input: Input string contains a mysterious command!");
    }
}

void Tr::Trade::parseInputMarket()
{
    std::string input;

    if (!std::getline(std::cin, input)) {
        this->_stopLoop = true;
        return;
    }
    selectCommand(input);
}
