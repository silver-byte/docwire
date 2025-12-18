/*********************************************************************************************************************************************/
/*  DocWire SDK: Award-winning modern data processing in C++20. SourceForge Community Choice & Microsoft support. AI-driven processing.      */
/*  Supports nearly 100 data formats, including email boxes and OCR. Boost efficiency in text extraction, web data extraction, data mining,  */
/*  document analysis. Offline processing possible for security and confidentiality                                                          */
/*                                                                                                                                           */
/*  Copyright (c) SILVERCODERS Ltd, http://silvercoders.com                                                                                  */
/*  Project homepage: https://github.com/docwire/docwire                                                                                     */
/*                                                                                                                                           */
/*  SPDX-License-Identifier: GPL-2.0-only OR LicenseRef-DocWire-Commercial                                                                   */
/*********************************************************************************************************************************************/
#ifndef DOCWIRE_NAMED_H
#define DOCWIRE_NAMED_H
#include <string_view>
#include <utility>

namespace docwire::named
{
    template <typename T>
    struct value
    {
        std::string_view name;
        T value;

        template <size_t I>
        [[nodiscard]] constexpr decltype(auto) get() & noexcept
        {
            if constexpr (I == 0) return (name);
            else return (value);
        }

        template <size_t I>
        [[nodiscard]] constexpr decltype(auto) get() const& noexcept
        {
            if constexpr (I == 0) return (name);
            else return (value);
        }

        template <size_t I>
        [[nodiscard]] constexpr decltype(auto) get() && noexcept
        {
            if constexpr (I == 0) return (name);
            else return std::move(value);
        }
    };

    struct variable
    {
        const std::string_view name;

        template <typename T>
        [[nodiscard]] constexpr auto operator=(T&& val) const noexcept
        {
            return value<std::decay_t<T>>{name, std::forward<T>(val)};
        }
    };

    inline namespace literals
    {
        [[nodiscard]] constexpr variable operator""_v(const char* str, size_t len) noexcept
        {
            return {std::string_view{str, len}};
        }
    }
}

namespace docwire
{
    // Bring the _v literal into the docwire namespace for convenience.
    using namespace docwire::named::literals;
}

namespace std
{
    template <typename T>
    struct tuple_size<docwire::named::value<T>> : std::integral_constant<size_t, 2> {};

    template <size_t I, typename T>
    struct tuple_element<I, docwire::named::value<T>> : std::conditional<I == 0, std::string_view, T> {};
}

#endif // DOCWIRE_NAMED_H