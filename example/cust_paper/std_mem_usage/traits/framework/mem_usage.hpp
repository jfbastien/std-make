// Copyright (C) 2016 Vicente J. Botet Escriba
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef JASEL_EXAMPLE_FRAMEWORK_MEM_USAGE_HPP
#define JASEL_EXAMPLE_FRAMEWORK_MEM_USAGE_HPP

#if __cplusplus >= 201402L

#include <type_traits>
#include <experimental/meta.hpp>
#include <cstddef>

// mem_usage_able/mem_usage.hpp
namespace std
{
namespace experimental
{
inline namespace fundamental_v3
{
namespace mem_usage_able
{

  template <typename T, typename Enabler=void>
  struct mem_usage_traits : mem_usage_traits<T, meta::when<true>> {};
  template <typename T, bool B>
  struct mem_usage_traits<T, meta::when<B>>
  {
    static constexpr size_t apply(const T& v) = delete;
  };
  template <typename T>
  struct mem_usage_traits<T, meta::when<std::is_trivial<T>::value>>
  {
    static constexpr size_t apply(const T& v) noexcept { return sizeof v; }
  };

  template <typename T>
  constexpr auto mem_usage(const T& v) noexcept -> decltype(mem_usage_traits<T>::apply(v))
  {
    return mem_usage_traits<T>::apply(v);
  }
}
}
}
}
#endif

#endif