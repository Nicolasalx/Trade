/*
** EPITECH PROJECT, 2024
** Trade
** File description:
** getDouble
*/

#include "trade.hpp"
#include "my_tracked_exception.hpp"

double Tr::Trade::getDouble(const std::string &input)
{
    for (const auto &chr: input) {
        if (!std::isdigit(chr) && chr != '.') {
            throw my::tracked_exception("Parsing input: Failed to get a double");
        }
    }
    return (std::stod(input));    
}
