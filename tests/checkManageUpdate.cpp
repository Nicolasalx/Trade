/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** checkManageUpdate
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "trade.hpp"
#include "my_tracked_exception.hpp"

Test(trade, manage_an_update_next_candles_valid_input)
{
    Tr::Trade trade;
    trade.initCandleFormat();
    std::vector<std::string> lineTokens = {"update", "game", "next_candles", "USDT_BTC,1624536000,35000.0,34500.0,34800.0,34600.0,10000.0"};
    trade.manageAnUpdate(lineTokens);

    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, manage_an_update_stacks_valid_input)
{
    Tr::Trade trade;

    trade.initCandleFormat();
    std::vector<std::string> lineTokens = {"update", "game", "stacks", "BTC:0.5,USDT:100"};
    trade.manageAnUpdate(lineTokens);
    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, manage_an_update_invalid_input)
{
    Tr::Trade trade;

    std::vector<std::string> lineTokens = {"update", "game", "invalid_command", "BTC:0.5,USDT:100,ETH:10"};
    trade.initCandleFormat();

    cr_assert_throw(trade.manageAnUpdate(lineTokens), my::tracked_exception,
        "Exception not thrown for invalid input");
}
