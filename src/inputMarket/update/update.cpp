/*
** EPITECH PROJECT, 2024
** Trade
** File description:
** update
*/

#include "trade.hpp"
#include "my_tracked_exception.hpp"

void Tr::Trade::manageAnUpdate(std::vector<std::string> lineTokens)
{
    if (lineTokens.size() != 4) {
        throw my::tracked_exception("Parsing Input: In the Update command, the list need to be of size 3!");
    }
    if (lineTokens.at(2) == "next_candles") {
        addCandle(lineTokens.at(3));
    } else if (lineTokens.at(2) == "stacks") {
        handleStacks(lineTokens.at(3));
    } else {
        throw my::tracked_exception("Parsing input: In the Update command, a inexistant command had been detected!");
    }
}
