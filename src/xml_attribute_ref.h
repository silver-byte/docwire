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

#ifndef DOCWIRE_XML_ATTRIBUTE_REF_H
#define DOCWIRE_XML_ATTRIBUTE_REF_H

#include "safety_policy.h"
#include "xml_reader.h"
#include <functional>
#include <string_view>

namespace docwire::xml
{

template <safety_policy safety_level = default_safety_level>
class attribute_ref
{
 public:
  explicit attribute_ref(const reader<safety_level>& reader) : m_reader(reader) {}
  std::string_view name() const { return m_reader.get().name(); }
  std::string_view value() const { return m_reader.get().content(); }

 private:
    std::reference_wrapper<const reader<safety_level>> m_reader;
};

}

#endif // DOCWIRE_XML_ATTRIBUTE_REF_H