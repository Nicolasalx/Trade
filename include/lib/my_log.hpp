/*
** EPITECH PROJECT, 2024
** my_cpplib
** File description:
** my_log
*/

#ifndef MY_LOG_HPP_
    #define MY_LOG_HPP_

    #include <stdexcept>
    #include <string>
    #include <source_location>
    #include <format>
    #include <iostream>

namespace my::log
{
    void info(const std::string &msg,
        std::source_location info = std::source_location::current())
    {
        std::cerr << std::format("\033[1m{}:\033[96m{}\033[0;1m: "
        "\033[96minfo: \033[0m{}\n", info.file_name(), info.line(), msg);
    }
    
    void warning(const std::string &msg,
        std::source_location info = std::source_location::current())
    {
        std::cerr << std::format("\033[1m{}:\033[96m{}\033[0;1m: "
        "\033[95mwarning: \033[0m{}\n", info.file_name(), info.line(), msg);
    }

    void error(const std::string &msg,
        std::source_location info = std::source_location::current())
    {
        std::cerr << std::format("\033[1m{}:\033[96m{}\033[0;1m: "
        "\033[91merror: \033[0m{}\n", info.file_name(), info.line(), msg);
    }
}

#endif /* !MY_LOG_HPP_ */
