// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Copyright (C) 2016 Vicente J. Botet Escriba

#ifndef JASEL_FUNDAMENTAL_V3_TUPLE_HPP
#define JASEL_FUNDAMENTAL_V3_TUPLE_HPP

#include <experimental/make.hpp>
#include <experimental/meta.hpp>
#include <tuple>

namespace std
{
  // There is no way to have a variadic type constructor so we opt for a type constructor with a single type holder

  // Holder customization
  template <>
  struct tuple<experimental::_t> : experimental::meta::quote<tuple> {};

namespace experimental
{
inline namespace fundamental_v3
{
  using tuple_tc = tuple<experimental::_t>;

  // type_constructor customization
  template <class ...Ts>
  struct type_constructor<tuple<Ts...>> : meta::id<tuple_tc> {};

#if __cplusplus == 201402L || (__cplusplus > 201402L and defined __GNUC__ and ! defined __clang__)


      namespace detail {

        template <class Function, class Tuple, std::size_t... i>
        decltype(auto) apply_impl(Function &&fn,
                                  Tuple &&tuple,
                                  std::index_sequence<i...>) {
          return std::forward<Function>(fn)(std::get<i>(std::forward<Tuple>(tuple))...);
        }

      } // detail

      /* C++17 std::apply */

      template <class Function, class Tuple>
      decltype(auto) apply(Function &&fn, Tuple &&tuple) {
        return detail::apply_impl(std::forward<Function>(fn),
                          std::forward<Tuple>(tuple),
                          std::make_index_sequence<
                          std::tuple_size<std::decay_t<Tuple>>::value>());
      }
#endif
}
}
}

#endif // header
