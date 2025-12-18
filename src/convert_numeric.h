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

#ifndef DOCWIRE_CONVERT_NUMERIC_H
#define DOCWIRE_CONVERT_NUMERIC_H

#include "convert_base.h"
#include <charconv>

namespace docwire::convert {

// Concept for types supported by std::from_chars in C++20.
// This excludes bool, which is only supported from C++23.
template<typename T>
concept is_from_chars_compatible = (std::is_integral_v<T> && !std::is_same_v<T, bool>) || std::is_floating_point_v<T>;

template<is_from_chars_compatible To, std::convertible_to<std::string_view> From>
requires (noexcept(std::string_view(std::declval<const From&>())))
std::optional<To> convert_impl(const From& s, dest_type_tag<To>) noexcept
{
	To value{};
	const std::string_view sv(s);
	auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value);
	if (ec == std::errc() && ptr == sv.data() + sv.size())
		return value;
	return std::nullopt;
}

} // namespace docwire::convert

#endif // DOCWIRE_CONVERT_NUMERIC_H
