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

#ifndef DOCWIRE_WITH_SOURCE_LOCATION_H
#define DOCWIRE_WITH_SOURCE_LOCATION_H

#include "source_location.h"

namespace docwire::detail
{
    // This helper struct is implicitly constructed from a value of type T.
    // Its purpose is to capture the source location of the call site.
    template <typename T>
    struct with_source_location
    {
        T value;
        source_location location;

        constexpr with_source_location(T val, const source_location& loc = source_location::current())
            : value(val), location(loc) {}
    };
}

#endif // DOCWIRE_WITH_SOURCE_LOCATION_H