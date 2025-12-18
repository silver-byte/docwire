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

#ifndef DOCWIRE_XML_NODE_REF_H
#define DOCWIRE_XML_NODE_REF_H

#include <memory>
#include "xml_iterator_state.h"
#include "not_null.h"
#include "ranged.h"

namespace docwire::xml
{

template <safety_policy safety_level = default_safety_level>
class node_ref
{
public:
    explicit node_ref(not_null<std::shared_ptr<iterator_state<safety_level>>, safety_level> state)
        : m_state(std::move(state)) {}
    std::string_view name() const { return m_state->xml_reader.name(); }
    std::string_view full_name() const { return m_state->xml_reader.full_name(); }
    std::string_view content() const { return m_state->xml_reader.content(); }
    std::string_view string_value() const { return m_state->xml_reader.string_value(); }
    non_negative<int, safety_level> depth() const { return m_state->xml_reader.depth(); }
    node_type type() const { return m_state->xml_reader.type(); }
    const not_null<std::shared_ptr<iterator_state<safety_level>>, safety_level>& state() const { return m_state; }

private:
    not_null<std::shared_ptr<iterator_state<safety_level>>, safety_level> m_state;
};

}

#endif