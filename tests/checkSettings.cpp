/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** checkSettings
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "trade.hpp"
#include "my_tracked_exception.hpp"

Test(trade, change_format_candle_valid_input)
{
    Tr::Trade trade;

    std::string inputFormat = "pair,date,high,low,open,close,volume";
    trade.changeFormatCandle(inputFormat);
    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, change_format_candle_invalid_input)
{
    Tr::Trade trade;

    std::string inputFormat = "pair,date,high,low,open,close";
    cr_assert_throw(trade.changeFormatCandle(inputFormat), my::tracked_exception,
        "Exception not thrown for invalid input");
}

Test(trade, manage_settings_player_names_valid_input)
{
    Tr::Trade trade;
    std::vector<std::string> lineTokens = {"settings", "player_names", "Alice,Bob"};

    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, manage_settings_your_bot_valid_input)
{
    Tr::Trade trade;
    std::vector<std::string> lineTokens = {"settings", "your_bot", "Alice"};
    trade.manageSettings(lineTokens);

    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, manage_settings_invalid_input)
{
    Tr::Trade trade;
    std::vector<std::string> lineTokens = {"settings", "invalid_argument", "value"};

    cr_assert_throw(trade.manageSettings(lineTokens), my::tracked_exception,
        "Exception not thrown for invalid input");
}
