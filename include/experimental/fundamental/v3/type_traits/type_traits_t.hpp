//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file // LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//////////////////////////////////////////////////////////////////////////////

#ifndef JASEL_V3_FUNDAMENTAL_TYPE_TRAITS_TYPE_TRAITS_T_HPP
#define JASEL_V3_FUNDAMENTAL_TYPE_TRAITS_TYPE_TRAITS_T_HPP

#include <type_traits>

#if __cplusplus == 201103L
namespace std
{
  template< class T >
  using add_pointer_t = typename add_pointer<T>::type;

  template< class... T >
  using common_type_t = typename common_type<T...>::type;

  template< bool B, class T, class F >
  using conditional_t = typename conditional<B,T,F>::type;

  template< class T >
  using decay_t = typename decay<T>::type;

  template< bool B, class T = void >
  using enable_if_t = typename enable_if<B,T>::type;

  template< class T >
  using remove_reference_t = typename remove_reference<T>::type;

  template< class T >
  using remove_cv_t = typename remove_cv<T>::type;

}
#endif
#endif // header
