/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** checkInputMarket
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "trade.hpp"
#include "my_tracked_exception.hpp"

Test(trade, select_command_valid_input)
{
    Tr::Trade trade;

    std::string input = "settings candle_interval 3600";
    trade.selectCommand(input);

    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, select_command_invalid_input)
{
    Tr::Trade trade;

    std::string input = "invalid_command";

    cr_assert_throw(trade.selectCommand(input), my::tracked_exception,
        "Exception not thrown for invalid input");
}
