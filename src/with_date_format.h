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

#ifndef DOCWIRE_WITH_DATE_FORMAT_H
#define DOCWIRE_WITH_DATE_FORMAT_H

#include <string_view>

namespace with::date_format
{

struct iso8601 { std::string_view v; };

struct openoffice_legacy { std::string_view v; };

struct asn1 { std::string_view v; };

} // namespace with::date_format

#endif // DOCWIRE_WITH_DATE_FORMAT_H
