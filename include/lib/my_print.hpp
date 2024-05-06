/*
** EPITECH PROJECT, 2024
** my_cpplib
** File description:
** my_print
*/

#ifndef MY_PRINT_HPP_
    #define MY_PRINT_HPP_

    #include <iostream>
    #include <string>

namespace my::concepts {
    template<typename T>
    concept printable = requires(std::ostream &output_stream, const T &data)
    {
        output_stream << data;
    };
}

namespace my
{
    template<typename T>
    requires std::ranges::range<T>
        && my::concepts::printable<typename T::value_type>
    void printml(const T &container, const std::string &separator = "\n")
    {
        for (const typename T::value_type &current : container) {
            std::cout << current << separator;
        }
    }

    template<typename T, typename Func>
    requires std::ranges::range<T>
    void printml(const T &container, const Func &method,
        const std::string &separator = "\n")
    {
        for (const typename T::value_type &current : container) {
            method(current);
            std::cout << separator;
        }
    }

    template<typename T>
    requires std::ranges::range<T>
        && my::concepts::printable<typename T::value_type>
    void printsl(const T &container, const std::string &separator = ", ")
    {
        bool is_first = true;

        for (const typename T::value_type &current : container) {
            if (!is_first) {
                std::cout << separator;
            }
            std::cout << current;
            is_first = false;
        }
    }

    template<typename T, typename Func>
    requires std::ranges::range<T>
    void printsl(const T &container, const Func &method,
        const std::string &separator = ", ")
    {
        bool is_first = true;

        for (const typename T::value_type &current : container) {
            if (!is_first) {
                std::cout << separator;
            }
            method(current);
            is_first = false;
        }
    }
}

#endif /* !MY_PRINT_HPP_ */
