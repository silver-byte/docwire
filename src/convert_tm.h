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

#ifndef DOCWIRE_CONVERT_TM_H
#define DOCWIRE_CONVERT_TM_H

#include "convert_base.h"
#include <ctime>
#include <optional>
#include <string_view>

namespace docwire::convert
{

DOCWIRE_CORE_EXPORT std::optional<tm> convert_impl(std::string_view s, dest_type_tag<tm>) noexcept;

}

#endif // DOCWIRE_CONVERT_TM_H
