/*
** EPITECH PROJECT, 2024
** my_cpplib
** File description:
** tracked_exception
*/

#include "my_tracked_exception.hpp"
#include <iostream>

static std::string indent_excepetion(const std::string &str)
{
    std::string result;

    for (char c : str) {
        result += c;
        if (c == '\n') {
            result += "│ ";
        }
    }
    return result;
}

my::tracked_exception::tracked_exception(const std::string &message,
    const std::source_location location)
{
    message_ += indent_excepetion(message);
    message_ += this->format_src_location(location);
}

const char *my::tracked_exception::what() const noexcept
{
    return message_.c_str();
}
