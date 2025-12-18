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

#ifndef DOCWIRE_XML_ROOT_ELEMENT_H
#define DOCWIRE_XML_ROOT_ELEMENT_H

#include "xml_children.h"
#include "xml_node_ref.h"
#include "make_error.h"

namespace docwire::xml
{

template <safety_policy safety_level>
node_ref<safety_level> root_element(reader<safety_level>& reader)
{
    for (auto node: children(reader))
    {
        if (node.type() == node_type::element)
            return node;
    }
    throw DOCWIRE_MAKE_ERROR("No root element found");
}

}

#endif // DOCWIRE_XML_ROOT_ELEMENT_H
