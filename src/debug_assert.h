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

#ifndef DOCWIRE_DEBUG_ASSERT_H
#define DOCWIRE_DEBUG_ASSERT_H

#include "make_error.h"
#include "with_source_location.h"

// In debug builds (when NDEBUG is not defined), DOCWIRE_DEBUG_ASSERT checks a condition
// and if it's false, prints a message and terminates the program.
// In release builds (when NDEBUG is defined), it compiles to nothing.
#ifndef NDEBUG
namespace docwire::errors
{
    [[noreturn]] DOCWIRE_CORE_EXPORT void panic(std::exception_ptr eptr);
}
#endif // NDEBUG

namespace docwire
{

#ifndef NDEBUG

template<typename... Context>
void debug_assert(detail::with_source_location<bool> condition, Context&&... context)
{
    if (!condition.value)
    {
        errors::panic(make_error_ptr_from_tuple(condition.location, std::make_tuple(std::forward<Context>(context)...)));
    }
}

#else

template<typename... Context>
constexpr void debug_assert(detail::with_source_location<bool> /*condition*/, Context&&...) {}

#endif // NDEBUG

} // namespace docwire

#endif // DOCWIRE_DEBUG_ASSERT_H