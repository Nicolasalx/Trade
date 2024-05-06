/*
** EPITECH PROJECT, 2024
** my_cpplib
** File description:
** format_src_location
*/

#include <ranges>
#include <algorithm>
#include "my_tracked_exception.hpp"

static std::string get_func_name(const std::string &func)
{
    std::string func_name;

    for (int i = func.find_first_of('(') - 1; func[i] != ' ' && i >= 0; --i) {
        func_name.push_back(func[i]);
    }
    std::ranges::reverse(func_name.begin(), func_name.end());
    return func_name;
}

std::string my::tracked_exception::format_src_location(const std::source_location &info)
{
    return std::string("\n└ \033[1;95mexception throw from: \033[0;1m") +
        info.file_name() + ": \033[1m" + get_func_name(info.function_name()) +
        ": \033[1;96m" + std::to_string(info.line()) + "\033[0m";
}

std::string my::tracked_exception::format_src_location(void)
{
    return "\n└ \033[1;95mexception throw from:\033[0;1m unknown\033[0m";
}
