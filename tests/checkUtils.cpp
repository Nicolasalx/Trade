/*
** EPITECH PROJECT, 2024
** B-CNA-410-PAR-4-1-trade-thibaud.cathala
** File description:
** checkUtils
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "trade.hpp"
#include "my_tracked_exception.hpp"

Test(trade, get_double_valid_input)
{
    Tr::Trade trade;
    double result = trade.getDouble("123.45");

    cr_assert_eq(result, 123.45, "getDouble returned incorrect value for valid input");
}

Test(trade, get_double_invalid_input)
{
    Tr::Trade trade;

    try {
        trade.getDouble("12a.45");
        cr_assert_fail("getDouble did not throw exception for invalid input");
    } catch (const my::tracked_exception &ex) {
        const char* expected_prefix = "Parsing input: Failed to get a double";
        const char* actual_message = ex.what();
        cr_assert(strncmp(actual_message, expected_prefix, strlen(expected_prefix)) == 0,
            "Exception message does not start with the expected prefix");
    }
}

Test(trade, get_int_valid_input)
{
    Tr::Trade trade;
    int result = trade.getInt("12345");

    cr_assert_eq(result, 12345, "getInt returned incorrect value for valid input");
}

Test(trade, get_int_invalid_input)
{
    Tr::Trade trade;

    try {
        trade.getInt("12a45");
        cr_assert_fail("getInt did not throw exception for invalid input");
    } catch (const my::tracked_exception &ex) {
        const char* expected_prefix = "Parsing input: Failed to get a int";
        const char* actual_message = ex.what();
        cr_assert(strncmp(actual_message, expected_prefix, strlen(expected_prefix)) == 0,
            "Exception message does not start with the expected prefix");
    }
}
