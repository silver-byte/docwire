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

#ifndef DOCWIRE_CHECKED_H
#define DOCWIRE_CHECKED_H

#include "safety_policy.h"
#include "enforce.h"
#include <utility>

namespace docwire
{

/**
 * @brief A generic wrapper for dereferenceable types (like pointers and optionals)
 * that provides checked access based on a safety_policy.
 *
 * In `strict` mode, the dereference operators (`*`, `->`) check if the object is valid
 * and throw an exception if it does not.
 * In `relaxed` mode, this wrapper is a zero-cost abstraction with no runtime checks,
 * behaving like the underlying type.
 */
template <typename Dereferenceable, safety_policy safety_level = default_safety_level>
class checked
{
public:
    // Constructors to wrap the underlying type. These are not explicit to allow
    // implicit conversion from null-like types (e.g., nullptr -> unique_ptr -> checked).
    checked() = default;
    checked(const Dereferenceable& value) : m_value(value) {}
    checked(Dereferenceable&& value) noexcept(std::is_nothrow_move_constructible_v<Dereferenceable>) : m_value(std::move(value)) {}

    // Generic forwarding constructor for constructing the underlying object.
    // This is constrained to avoid interfering with copy/move constructors.
    template <typename... Args,
              typename = std::enable_if_t<std::is_constructible_v<Dereferenceable, Args...> && (sizeof...(Args) > 1)>>
    checked(Args&&... args)
        : m_value(std::forward<Args>(args)...) {}

    checked& operator=(const Dereferenceable& value) { m_value = value; return *this; }
    checked& operator=(Dereferenceable&& value) noexcept(std::is_nothrow_move_assignable_v<Dereferenceable>) { m_value = std::move(value); return *this; }

    // Checked dereference operators
    const auto& operator*() const
    {
        enforce<safety_level>(static_cast<bool>(m_value), "Attempted to dereference a null/empty value");
        return *m_value;
    }

    auto& operator*()
    {
        enforce<safety_level>(static_cast<bool>(m_value), "Attempted to dereference a null/empty value");
        return *m_value;
    }

    auto operator->() const
    {
        enforce<safety_level>(static_cast<bool>(m_value), "Attempted to dereference a null/empty value");
        return &this->operator*();
    }

    // Forwarded methods
    explicit operator bool() const noexcept { return static_cast<bool>(m_value); }
    auto get() const requires requires(const Dereferenceable& v) { v.get(); } { return m_value.get(); }

    bool has_value() const noexcept(noexcept(std::declval<const Dereferenceable&>().has_value()))
        requires requires(const Dereferenceable& v) { v.has_value(); }
    {
        return m_value.has_value();
    }

    template<typename... Args>
    void reset(Args&&... args) noexcept(noexcept(std::declval<Dereferenceable&>().reset(std::forward<Args>(args)...))) requires requires(Dereferenceable& v, Args&&... a) { v.reset(std::forward<Args>(a)...); }
    {
        m_value.reset(std::forward<Args>(args)...);
    }

    template<class... Args>
    auto& emplace(Args&&... args) requires requires(Dereferenceable v, Args&&... a) { v.emplace(std::forward<Args>(a)...); }
    {
        return m_value.emplace(std::forward<Args>(args)...);
    }

private:
    Dereferenceable m_value;
};

} // namespace docwire

#endif // DOCWIRE_CHECKED_H