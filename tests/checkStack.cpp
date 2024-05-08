/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** checkStack
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "trade.hpp"
#include "my_tracked_exception.hpp"

Test(trade, set_amount_to_one_crypto_BTC_valid_input)
{
    Tr::Trade trade;

    std::string dataCrypto = "BTC:0.5";
    trade.setAmountToOneCrypto(dataCrypto);
    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, set_amount_to_one_crypto_USDT_valid_input)
{
    Tr::Trade trade;

    std::string dataCrypto = "USDT:100";
    trade.setAmountToOneCrypto(dataCrypto);
    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, set_amount_to_one_crypto_invalid_input)
{
    Tr::Trade trade;

    std::string dataCrypto = "BTC";
    
    cr_assert_throw(trade.setAmountToOneCrypto(dataCrypto), my::tracked_exception,
        "Exception not thrown for invalid input");
}

Test(trade, handle_stacks_valid_input)
{
    Tr::Trade trade;

    std::string inputStacks = "BTC:0.5,USDT:100";
    trade.handleStacks(inputStacks);
    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, handle_stacks_invalid_input)
{
    Tr::Trade trade;

    std::string inputStacks = "BTC:0.5,USDT:100;ETH:100";

    cr_assert_throw(trade.handleStacks(inputStacks), my::tracked_exception,
        "Exception not thrown for invalid input");
}
