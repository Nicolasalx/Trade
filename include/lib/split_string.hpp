/*
** EPITECH PROJECT, 2024
** my_cpplib
** File description:
** split_string
*/

#ifndef SPLIT_STRING_HPP_
    #define SPLIT_STRING_HPP_

    #include <string>
    #include <concepts>

namespace my::concepts {
    template<typename T>
    concept push_back_string = requires(T &data)
    {
        data.push_back(std::string());
    };
}

namespace my
{
    template<typename T>
    requires my::concepts::push_back_string<T>
        && std::same_as<typename T::value_type, std::string>
    void split_string(const std::string &str, const std::string &delimiter, T &dest)
    {
        size_t start = 0;

        for (size_t i = 0; i <= str.size(); ++i) {
            if (i == str.size() || delimiter.find(str[i]) != std::string::npos) {
                if (i > start) {
                    dest.push_back(str.substr(start, i - start));
                }
                start = i + 1;
            }
        }
    }
}

#endif /* !SPLIT_STRING_HPP_ */
