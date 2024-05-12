/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** getInt
*/

#include "trade.hpp"
#include "my_tracked_exception.hpp"

int Tr::Trade::getInt(const std::string &input)
{
    for (const auto &chr: input) {
        if (!std::isdigit(chr)) {
            throw my::tracked_exception("Parsing input: Failed to get a int");
        }
    }
    return (std::stoi(input));
}
