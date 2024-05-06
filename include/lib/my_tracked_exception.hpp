/*
** EPITECH PROJECT, 2024
** my_cpplib
** File description:
** my_tracked_exception
*/

#ifndef MY_TRACKED_EXCEPTION_HPP_
    #define MY_TRACKED_EXCEPTION_HPP_

    #include <string>
    #include <exception>
    #include <source_location>

namespace my
{
    class tracked_exception : public std::exception
    {
    private:
        std::string message_;

        [[nodiscard]]
        std::string format_src_location(const std::source_location &info);
        [[nodiscard]]
        std::string format_src_location(void);

    public:
        explicit tracked_exception(const std::string &message,
            std::source_location location = std::source_location::current());

        [[nodiscard]]
        const char *what() const noexcept override;
    };
}

#endif /* !MY_TRACKED_EXCEPTION_HPP_ */
