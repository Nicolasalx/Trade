/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** example
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "trade.hpp"
#include "my_tracked_exception.hpp"

Test(trade, increase_amount_USDT_valid_input)
{
    Tr::Trade trade;

    std::string currency = "USDT";
    trade.increaseAmount(currency, 10.0);
    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, increase_amount_BTC_valid_input)
{
    Tr::Trade trade;

    std::string currency = "BTC";
    trade.increaseAmount(currency, 1.0);
    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, increase_amount_invalid_input)
{
    Tr::Trade trade;
    std::string currency = "INVALID";
    double amount = 10.0;

    cr_assert_throw(trade.increaseAmount(currency, amount), my::tracked_exception,
        "Exception not thrown for invalid input");
}

Test(trade, decrease_amount_USDT_valid_input)
{
    Tr::Trade trade;

    trade.initCandleFormat();
    std::string cryptoLine = "USDT_BTC,1624536000,35000.0,34500.0,34800.0,34600.0,10000.0";
    trade.addCryptoCandle(cryptoLine);

    std::string currency = "USDT";
    trade.handleStacks("BTC:1000,USDT:1000");
    trade.decreaseAmount(currency, 0.01);

    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, decrease_amount_BTC_valid_input)
{
    Tr::Trade trade;

    std::string currency = "BTC";

    trade.initCandleFormat();
    std::string cryptoLine = "USDT_BTC,1624536000,35000.0,34500.0,34800.0,34600.0,10000.0";
    trade.addCryptoCandle(cryptoLine);

    trade.handleStacks("BTC:1000,USDT:1000");
    trade.decreaseAmount(currency, 0.01);

    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, decrease_amount_invalid_input)
{
    Tr::Trade trade;

    std::string currency = "INVALID";
    trade.initCandleFormat();
    std::string cryptoLine = "USDT_BTC,1624536000,35000.0,34500.0,34800.0,34600.0,10000.0";
    trade.addCryptoCandle(cryptoLine);
    trade.handleStacks("BTC:1000,USDT:1000");

    cr_assert_throw(trade.decreaseAmount(currency, 0.01), my::tracked_exception,
        "Exception not thrown for invalid input");
}

Test(trade, order_action_buy_valid_input)
{
    Tr::Trade trade;

    trade.handleStacks("BTC:1000,USDT:1000");
    trade.initCandleFormat();
    std::string cryptoLine = "USDT_BTC,1624536000,35000.0,34500.0,34800.0,34600.0,10000.0";
    trade.addCryptoCandle(cryptoLine);
    std::string pair = "USDT_BTC";
    trade.orderAction(pair, std::make_pair(0.01, 0.1), Tr::Trade::BUY);
    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, order_action_sell_valid_input)
{
    Tr::Trade trade;

    trade.handleStacks("BTC:1000,USDT:1000");
    trade.initCandleFormat();
    std::string cryptoLine = "USDT_BTC,1624536000,35000.0,34500.0,34800.0,34600.0,10000.0";
    trade.addCryptoCandle(cryptoLine);
    std::string pair = "BTC_USDT";
    trade.orderAction(pair, std::make_pair(0.01, 0.1), Tr::Trade::BUY);
    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, order_action_invalid_pair)
{
    Tr::Trade trade;

    trade.handleStacks("BTC:1000,USDT:1000");
    std::string pair = "INVALID_PAIR";
    trade.initCandleFormat();
    std::string cryptoLine = "USDT_BTC,1624536000,35000.0,34500.0,34800.0,34600.0,10000.0";
    trade.addCryptoCandle(cryptoLine);

    cr_assert_throw(trade.orderAction(pair, std::make_pair(0.01, 0.1), Tr::Trade::BUY), my::tracked_exception,
        "Exception not thrown for invalid pair");
}
