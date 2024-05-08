/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** checkCandle
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "trade.hpp"
#include "my_tracked_exception.hpp"

Test(trade, set_pair_to_candle_valid_input)
{
    Tr::Trade trade;

    std::string pairName = "USDT_BTC";
    trade.setPairToCandle(pairName);

    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, set_pair_to_candle_invalid_input)
{
    Tr::Trade trade;

    std::string pairName = "ETH_BTC";
    cr_assert_throw(trade.setPairToCandle(pairName), my::tracked_exception,
        "Exception not thrown for invalid input");
}

Test(trade, add_crypto_candle_valid_input)
{
    Tr::Trade trade;

    trade.initCandleFormat();
    std::string cryptoLine = "USDT_BTC,1624536000,35000.0,34500.0,34800.0,34600.0,10000.0";
    trade.addCryptoCandle(cryptoLine);

    cr_assert(true, "No exception thrown for valid input");
}

Test(trade, add_crypto_candle_invalid_input)
{
    Tr::Trade trade;

    trade.initCandleFormat();
    std::string cryptoLine = "USDT_BTC,1624536000,35000.0,34500.0,34800.0,34600.0";
    cr_assert_throw(trade.addCryptoCandle(cryptoLine), my::tracked_exception,
        "Exception not thrown for invalid input");
}
