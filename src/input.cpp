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

#include "input.h"

#include "log.h"
#include "parser.h"

using namespace docwire;

ParsingChain
InputChainElement::operator|(ChainElement &chainElement) const
{
  return ParsingChain(*this, chainElement);
}

ParsingChain
InputChainElement::operator|(ChainElement &&chainElement) const
{
  return ParsingChain(*this, chainElement);
}

ParsingChain
InputChainElement::operator|(ParsingChain &parsingChain)
{
  parsingChain.process(*this);
  return parsingChain;
}

ParsingChain
InputChainElement::operator|(ParsingChain &&parsingChain)
{
  parsingChain.process(*this);
  return parsingChain;
}

void
InputChainElement::process(ChainElement& chain_element) const
{
  docwire_log_func();
  docwire_log_var(m_tag);
  Info info{m_tag};
  chain_element.process(info);
}
