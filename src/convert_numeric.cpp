#include "convert_numeric.h"
#include <string>
#include <cstdlib>
#include <cerrno>
#include <cctype>

namespace docwire::convert::detail {

template <typename T>
std::optional<T> from_chars_fallback_impl(std::string_view sv, bool allow_partial) noexcept
{
    static_assert(std::is_same_v<T, float> || std::is_same_v<T, double> || std::is_same_v<T, long double>,
                  "T must be float, double, or long double");
    try
    {
        std::string str(sv);
        // std::from_chars does not skip leading whitespace.
        if (!str.empty() && std::isspace(static_cast<unsigned char>(str[0])))
            return std::nullopt;

        char* end = nullptr;
        errno = 0;
        T value{};
        if constexpr (std::is_same_v<T, float>)
            value = std::strtof(str.c_str(), &end);
        else if constexpr (std::is_same_v<T, double>)
            value = std::strtod(str.c_str(), &end);
        else if constexpr (std::is_same_v<T, long double>)
            value = std::strtold(str.c_str(), &end);

        if (errno == ERANGE)
            return std::nullopt;

        if (end == str.c_str())
            return std::nullopt;

        if (!allow_partial)
            if (end != str.c_str() + str.size())
                return std::nullopt;

        return value;
    }
    catch (...)
    {
        return std::nullopt;
    }
}

std::optional<float> from_chars_fallback(std::string_view sv, bool allow_partial, dest_type_tag<float>) noexcept
{
    return from_chars_fallback_impl<float>(sv, allow_partial);
}

std::optional<double> from_chars_fallback(std::string_view sv, bool allow_partial, dest_type_tag<double>) noexcept
{
    return from_chars_fallback_impl<double>(sv, allow_partial);
}

std::optional<long double> from_chars_fallback(std::string_view sv, bool allow_partial, dest_type_tag<long double>) noexcept
{
    return from_chars_fallback_impl<long double>(sv, allow_partial);
}

} // namespace docwire::convert::detail
