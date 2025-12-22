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

#ifndef DOCWIRE_CONVERT_BASE_H
#define DOCWIRE_CONVERT_BASE_H

#include <optional>
#include "error_tags.h"
#include "throw_if.h"
#include "type_name.h"

namespace docwire::convert
{

template<typename T>
struct dest_type_tag {};

template <typename To, typename From>
concept conversion_implementation_exists = requires(const From& from) {
    { convert_impl(from, convert::dest_type_tag<To>{}) } noexcept -> std::same_as<std::optional<To>>;
};

namespace detail
{

struct convert_cpo
{
    template<typename To, typename From>
    requires conversion_implementation_exists<To, From>
    constexpr std::optional<To> operator()(const From& from) const noexcept
    {
        return convert_impl(from, dest_type_tag<To>{});
    }
};

inline constexpr convert_cpo convert_cpo;

} // namespace detail

template<typename To, typename From>
requires conversion_implementation_exists<To, From>
constexpr std::optional<To> try_to(const From& from) noexcept
{
	return detail::convert_cpo.template operator()<To, From>(from);
}

template<typename To, typename From>
requires conversion_implementation_exists<To, From>
To to(const From& from)
{
	auto result = try_to<To>(from);
	throw_if(!result.has_value(), "Failed to convert value", std::make_pair("from_type", type_name::pretty<From>()), std::make_pair("to_type", type_name::pretty<To>()), errors::uninterpretable_data{});
	return *result;
}

} // namespace docwire::convert

#endif // DOCWIRE_CONVERT_BASE_H
