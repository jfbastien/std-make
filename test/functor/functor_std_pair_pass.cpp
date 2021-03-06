// Copyright (C) 2016 Vicente J. Botet Escriba
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// <experimental/functor.hpp>
// <experimental/utility.hpp> pair

#include <experimental/utility.hpp>
#include <experimental/functor.hpp>
#include <experimental/product_type.hpp>

#include <boost/detail/lightweight_test.hpp>

int twice(int i) {
  return 2*i;
}

int main()
{
#if __cplusplus >= 201402L
  namespace stde = std::experimental;

  using T = std::pair<int, int>;

  static_assert(stde::is_product_type_v<T>, "ERROR");
  static_assert(stde::is_type_constructible_v<T>, "ERROR");
  static_assert(std::is_base_of<stde::functor::tag, stde::functor::traits<std::pair<stde::_t, stde::_t>>> ::value, "ERROR");
  static_assert(stde::is_functor<std::pair<stde::_t, stde::_t>>::value, "ERROR");

  {
    int v=1;
    T x = std::make_pair(v,v);
    BOOST_TEST(x.first == 1);
    BOOST_TEST(x.second == 1);
    T y = stde::functor::transform(x, twice);
    BOOST_TEST(y.first == 2);
    BOOST_TEST(y.second == 2);
  }
#endif

  return ::boost::report_errors();
}
