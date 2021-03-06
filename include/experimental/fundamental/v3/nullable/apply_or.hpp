//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file // LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//////////////////////////////////////////////////////////////////////////////

#ifndef JASEL_FUNDAMENTAL_V3_NULLABLE_APPLY_OR_HPP
#define JASEL_FUNDAMENTAL_V3_NULLABLE_APPLY_OR_HPP

#include <experimental/fundamental/v2/config.hpp>
#include <experimental/fundamental/v3/nullable/none.hpp>
#include <experimental/meta.hpp>
#include <utility>

namespace std
{
namespace experimental
{
inline  namespace fundamental_v3
{
namespace nullable
{
  /**
   * nullable::apply_or
   * @par Returns
   *  The contained value or the parameter
   */
  template <class N, class F, class T
  // todo add constraint on T and F
  //, class = enable_if_t<
  //    is_nullable_v<meta::uncvref_t<N>>
  // && is_convertible_v< T, value_type_t<meta::uncvref_t<N>> >
  //>
  >
  BOOST_CXX14_CONSTEXPR
  value_type_t<meta::uncvref_t<N>>
  apply_or(N&& n, F&& f, T&& v)
  {
    if (nullable::has_value(forward<N>(n)))
    {
      return JASEL_INVOKE(std::forward<F>(f), nullable::deref(forward<N>(n)));
    }
    return forward<T>(v);
  }

} // nullable
}}
}
#endif // header
