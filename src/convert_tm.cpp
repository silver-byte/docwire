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

#include "convert_tm.h"
#include "convert_numeric.h" // IWYU pragma: keep
#include "log_scope.h"

namespace docwire::convert
{

namespace
{

bool try_to_int(std::string_view sv, int& out) noexcept
{
    if (auto val = try_to<int>(sv))
    {
        out = *val;
        return true;
    }
    return false;
}

std::optional<tm> finalize_and_validate_tm(tm date) noexcept
{
    // Perform basic range validation before attempting normalization.
    if (date.tm_year < 1900 || date.tm_mon < 1 || date.tm_mon > 12 ||
        date.tm_mday < 1 || date.tm_mday > 31 || date.tm_hour < 0 || date.tm_hour > 23 ||
        date.tm_min < 0 || date.tm_min > 59 ||
        date.tm_sec < 0 || date.tm_sec > 60)  // 60 for leap seconds
    {
        return std::nullopt;
    }

    // Store original day and month for validation after normalization.
    int original_day = date.tm_mday;
    int original_mon = date.tm_mon;

    // Adjust to the format expected by mktime.
    date.tm_year -= 1900;
    date.tm_mon--;
    date.tm_isdst = -1; // Let system determine DST

    // mktime normalizes the date (e.g., April 31 becomes May 1).
    // If the day or month changes after normalization, the original date was invalid.
    if (std::mktime(&date) != -1 && date.tm_mday == original_day && (date.tm_mon + 1) == original_mon)
        return date;

    return std::nullopt;
}

std::optional<tm> try_parse_iso_8601(std::string_view s) noexcept
{
    tm date{};
    if (s.length() >= 19 &&
        try_to_int(s.substr(0, 4), date.tm_year) && s[4] == '-' &&
        try_to_int(s.substr(5, 2), date.tm_mon) && s[7] == '-' &&
        try_to_int(s.substr(8, 2), date.tm_mday) && s[10] == 'T' &&
        try_to_int(s.substr(11, 2), date.tm_hour) && s[13] == ':' &&
        try_to_int(s.substr(14, 2), date.tm_min) && s[16] == ':' &&
        try_to_int(s.substr(17, 2), date.tm_sec))
        return finalize_and_validate_tm(date);

    return std::nullopt;
}

std::optional<tm> try_parse_openoffice_legacy_datetime(std::string_view s) noexcept
{
    tm date{};
    if (s.length() >= 17 && // YYYYMMDD;HHMMSSff
        try_to_int(s.substr(0, 4), date.tm_year) &&
        try_to_int(s.substr(4, 2), date.tm_mon) &&
        try_to_int(s.substr(6, 2), date.tm_mday) && s[8] == ';' &&
        try_to_int(s.substr(9, 2), date.tm_hour) &&
        try_to_int(s.substr(11, 2), date.tm_min) &&
        try_to_int(s.substr(13, 2), date.tm_sec))
        return finalize_and_validate_tm(date);

    return std::nullopt;
}

} // anonymous namespace

std::optional<tm> convert_impl(std::string_view s, dest_type_tag<tm>) noexcept
{
    log_scope(s);

    if (auto date = try_parse_iso_8601(s))
        return date;

    if (auto date = try_parse_openoffice_legacy_datetime(s))
        return date;

    return std::nullopt;
}

} // namespace docwire::convert
