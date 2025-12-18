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

#ifndef DOCWIRE_XML_READER_H
#define DOCWIRE_XML_READER_H

#include "safety_policy.h"
#include "pimpl.h"
#include <string_view>
#include "ranged.h"
#include "xml_export.h"

namespace docwire::xml
{
enum class reader_blanks { keep, ignore };
enum class node_type
{
	none = 0,
	element = 1,
	attribute = 2,
	text = 3,
	cdata = 4,
	entity_reference = 5,
	entity = 6,
	processing_instruction = 7,
	comment = 8,
	document = 9,
	document_type = 10,
	document_fragment = 11,
	notation = 12,
	whitespace = 13,
	significant_whitespace = 14,
	end_element = 15,
	end_entity = 16,
	xml_declaration = 17
};

template <safety_policy safety_level = default_safety_level>
class DOCWIRE_XML_EXPORT reader : public with_pimpl<reader<safety_level>>
{
	using with_pimpl<reader<safety_level>>::impl;
public:
	explicit reader(std::string_view xml_sv, reader_blanks blanks_option = reader_blanks::keep);

	// Public low-level methods
	bool read_next() const;
	std::string_view content() const;
	std::string_view name() const;
	std::string_view full_name() const;
	std::string_view string_value() const;
	// Attribute traversal methods
	bool move_to_first_attribute() const;
	bool move_to_next_attribute() const;
	void move_to_element() const noexcept(safety_level == relaxed);

	non_negative<int, safety_level> depth() const;

	node_type type() const;
};
}
#endif // DOCWIRE_XML_READER_H