// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Copyright (C) 2017 Vicente J. Botet Escriba

#ifndef JASEL_FUNDAMENTAL_V3_STRONG_STRONG_INT_HPP
#define JASEL_FUNDAMENTAL_V3_STRONG_STRONG_INT_HPP

#if __cplusplus >= 201402L || defined JASEL_DOXYGEN_INVOKED

#include <experimental/fundamental/v3/strong/tagged.hpp>
#include <experimental/fundamental/v3/strong/underlying_type.hpp>
#include <experimental/type_traits.hpp>

#include <limits>
#include <functional>
#include <iosfwd>


namespace std
{
namespace experimental
{
inline namespace fundamental_v3
{

  /**
  `strong_int` is a strongly type tagged by the tag @c Tag that wraps an integral type @c UT and behaves like an @c UT
  The main goal is to be able to define strong integers that don't mix between them.
  No implicit conversion to the underlying integer type is provided.

  Note that this is not a safe int, it just forbids the conversions between
  different strong integers types with non compatible tags.

  Example
  <code>
  using X = strong_int<XTag, int>;
  using Y = strong_int<YTag, int>;
  void f(X, Y);

  f(X(1), Y(1));

  </code>
  */

  template <class Tag, class UT>
  struct strong_int final : private_tagged<Tag, UT>
  {
      static_assert(is_integral<UT>::value, "UT must be integral");

      using base_type = private_tagged<Tag, UT>;
      using base_type::base_type;

      // todo add conversions from other strong_int
      strong_int() = default;
      strong_int(strong_int const&) = default;

      template <class UT2
      //fixme  error: constructor cannot be redeclared when using , typename = typename enable_if<>::type
        , enable_if_t<
            is_constructible_v<UT, UT2 const&> &&
            is_convertible_v<UT2 const&, UT>
            , bool> = false
      >
      strong_int(strong_int<Tag, UT2> const& other)
        : base_type(other.underlying())
      {}

      template <class UT2
        ,  typename = enable_if_t<
            is_constructible_v<UT, UT2 const&> &&
            ! is_convertible_v<UT2 const&, UT>
          >
      >
      explicit strong_int(strong_int<Tag, UT2> const& other)
        : base_type(other.underlying())
      {}

      // todo add assignment?

      // additive operators
      constexpr strong_int& operator+=(strong_int y)  noexcept
      { this->value += y.underlying(); return *this; }
      constexpr strong_int operator++()  noexcept
      { return strong_int(++this->value); }
      constexpr strong_int operator++(int)  noexcept
      { return strong_int(this->value++); }

      constexpr strong_int& operator-=(strong_int y)  noexcept
      { this->value -= y.underlying(); return *this; }
      constexpr strong_int operator--()  noexcept
      { return strong_int(--this->value); }
      constexpr strong_int operator--(int)  noexcept
      { return strong_int(this->value--); }

      //  Multiplicative operators
      // fixme: Should the * parameter be int?
      constexpr strong_int& operator*=(strong_int y)  noexcept
      { this->value *= y.underlying(); return *this; }

      // fixme: Should the / parameter be int? Or both as in std::chrono::duration
      constexpr strong_int& operator/=(strong_int y)  noexcept
      { this->value /= y.underlying(); return *this; }

      constexpr strong_int& operator%=(strong_int y)  noexcept
      { this->value %= y.underlying(); return *this; }

      constexpr strong_int& operator&=(strong_int y)  noexcept
      { this->value &= y.underlying(); return *this; }
      constexpr strong_int& operator|=(strong_int y)  noexcept
      { this->value |= y.underlying(); return *this; }
      constexpr strong_int& operator^=(strong_int y)  noexcept
      { this->value ^= y.underlying(); return *this; }

      // fixme: do we want the Bitwise logic operators for an integer? if strong_int should be a replacement of any int, yes.
      // This doesn't mean that we cannot have more specialized types

      // Bitwise logic operators
      // fixme: Should the << parameter be int?
      constexpr strong_int& operator<<=(strong_int y)  noexcept
      { this->value <<= y.value; return *this; }
      constexpr strong_int& operator>>=(strong_int y)  noexcept
      { this->value >>= y.value; return *this; }

  };

  template <class Tag, class R>
  constexpr strong_int<Tag, R> make_strong_int(R x)
  {
    return strong_int<Tag, R>(x);
  }

  // additive operators
  template <class Tag, class R>
  constexpr strong_int<Tag,R> operator+(strong_int<Tag,R> x)  noexcept
  {
    return x;
  }

  template <class Tag, class R1, class R2>
  constexpr auto operator+(strong_int<Tag,R1> x, strong_int<Tag,R2> y)  noexcept -> decltype(make_strong_int<Tag>(x.underlying() + y.underlying()))
  {
    return make_strong_int<Tag>(x.underlying() + y.underlying());
  }

  template <class Tag, class R>
  constexpr auto operator-(strong_int<Tag,R> x)  noexcept -> decltype(make_strong_int<Tag>(-x.underlying()))
  {
    return make_strong_int<Tag>(-x.underlying());
  }

  template <class Tag, class R1, class R2>
  constexpr auto operator-(strong_int<Tag,R1> x, strong_int<Tag,R2> y)  noexcept -> decltype(make_strong_int<Tag>(x.underlying() - y.underlying()))
  {
    return make_strong_int<Tag>(x.underlying() - y.underlying());
  }

  //  Multiplicative operators
  template <class Tag, class R1, class R2>
  constexpr auto operator*(strong_int<Tag,R1> x, strong_int<Tag,R2> y)  noexcept -> decltype(make_strong_int<Tag>(x.underlying() * y.underlying()))
  {
    return make_strong_int<Tag>(x.underlying() * y.underlying());
  }

  template <class Tag, class R1, class R2>
  constexpr auto operator/(strong_int<Tag,R1> x, strong_int<Tag,R2> y)  noexcept -> decltype(make_strong_int<Tag>(x.underlying() / y.underlying()))
  {
    return make_strong_int<Tag>(x.underlying() / y.underlying());
  }

  template <class Tag, class R1, class R2>
  constexpr auto operator%(strong_int<Tag,R1> x, strong_int<Tag,R2> y)  noexcept -> decltype(make_strong_int<Tag>(x.underlying() * y.underlying()))
  {
    return make_strong_int<Tag>(x.underlying() % y.underlying());
  }


  // Bitwise logic operators

  template <class Tag, class R>
  constexpr strong_int<Tag,R> operator~(strong_int<Tag,R> x)  noexcept
  {
    return strong_int<Tag,R>(~x.underlying());
  }

  template <class Tag, class R1, class R2>
  constexpr auto operator&(strong_int<Tag,R1> x, strong_int<Tag,R2> y)  noexcept -> decltype(make_strong_int<Tag>(x.underlying() & y.underlying()))
  {
    return make_strong_int<Tag>(x.underlying() & y.underlying());
  }

  template <class Tag, class R1, class R2>
  constexpr auto operator|(strong_int<Tag,R1> x, strong_int<Tag,R2> y)  noexcept -> decltype(make_strong_int<Tag>(x.underlying() | y.underlying()))
  {
    return make_strong_int<Tag>(x.underlying() | y.underlying());
  }

  template <class Tag, class R1, class R2>
  constexpr auto operator^(strong_int<Tag,R1> x, strong_int<Tag,R2> y)  noexcept -> decltype(make_strong_int<Tag>(x.underlying() ^ y.underlying()))
  {
    return make_strong_int<Tag>(x.underlying() ^ y.underlying());
  }

  template <class Tag, class R1, class R2>
  constexpr auto operator<<(strong_int<Tag,R1> x, strong_int<Tag,R2> y)  noexcept -> decltype(make_strong_int<Tag>(x.underlying() << y.underlying()))
  {
    return make_strong_int<Tag>(x.underlying() << y.underlying());
  }

  template <class Tag, class R1, class R2>
  constexpr auto operator>>(strong_int<Tag,R1> x, strong_int<Tag,R2> y)  noexcept -> decltype(make_strong_int<Tag>(x.underlying() >> y.underlying()))
  {
    return make_strong_int<Tag>(x.underlying() >> y);
  }

  // relational operators
  template <class Tag, class R1, class R2>
  constexpr auto operator==(strong_int<Tag,R1> x, strong_int<Tag,R2> y)  noexcept -> decltype(x.underlying() == y.underlying())
  {
    return x.underlying() == y.underlying();
  }

  template <class Tag, class R1, class R2>
  constexpr auto operator!=(strong_int<Tag,R1> x, strong_int<Tag,R2> y)  noexcept -> decltype(x.underlying() != y.underlying())
  {
    return x.underlying() != y.underlying();
  }

  template <class Tag, class R1, class R2>
  constexpr auto operator<(strong_int<Tag,R1> x, strong_int<Tag,R2> y)  noexcept -> decltype(x.underlying() < y.underlying())
  {
    return x.underlying() < y.underlying();
  }

  template <class Tag, class R1, class R2>
  constexpr auto operator>(strong_int<Tag,R1> x, strong_int<Tag,R2> y)  noexcept -> decltype(x.underlying() > y.underlying())
  {
    return x.underlying() > y.underlying();
  }

  template <class Tag, class R1, class R2>
  constexpr auto operator<=(strong_int<Tag,R1> x, strong_int<Tag,R2> y)  noexcept -> decltype(x.underlying() <= y.underlying())
  {
    return x.underlying() <= y.underlying();
  }

  template <class Tag, class R1, class R2>
  constexpr auto operator>=(strong_int<Tag,R1> x, strong_int<Tag,R2> y)  noexcept -> decltype(x.underlying() >= y.underlying())
  {
    return x.underlying() >= y.underlying();
  }

  // fixme do we need swap?



  //! underlying_type specialization for strong_int
  template <class Tag, class UT>
  struct underlying_type<strong_int<Tag,UT>> { using type = UT; };

  static_assert(std::is_pod<strong_int<bool,int>>::value, "");
  static_assert(std::is_trivially_default_constructible<strong_int<bool,int>>::value, "");
  static_assert(std::is_trivially_copyable<strong_int<bool,int>>::value, "");
  static_assert(std::is_standard_layout<strong_int<bool,int>>::value, "");
  static_assert(std::is_trivial<strong_int<bool,int>>::value, "");

  // stream operators

  //! input function.
  //! @par Effects:<br> Extracts a T from is and stores it in the passes x.
  //! @param is the input stream
  //! @param x the \c strong_int
  //! @par Returns:<br> \c is.

  template <class CharT, class Traits, class Tag, class T >
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, strong_int<Tag, T>& x)
  {
    T v;
    is >> v;
    x = strong_int<Tag, T>(v);
    return is;
  }

  //! output function.
  //! @param os the output stream
  //! @param x the \c strong_int
  //!
  //! @par Returns:<br> the result of the following expression
  //! @code
  //! os << x.undelying()
  //! @endcode

  template <class CharT, class Traits, class Tag, class T >
  std::basic_ostream<CharT, Traits>&
  operator<<(std::basic_ostream<CharT, Traits>& os, const strong_int<Tag, T>& x)
  {
    return os << x.underlying();
  }

}
}

  template <class Tag, class UT>
  struct hash<experimental::strong_int<Tag,UT>>
    : experimental::wrapped_hash<experimental::strong_int<Tag, UT>> {};

  template <class Tag, class UT>
  struct numeric_limits<experimental::strong_int<Tag,UT>> : numeric_limits<UT> {  };


}
#endif
#endif // header
