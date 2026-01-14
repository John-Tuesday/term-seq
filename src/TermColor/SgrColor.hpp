#pragma once

#ifndef TERMSEQ_SGR_COLOR_HPP
#define TERMSEQ_SGR_COLOR_HPP

#include "Sgr.hpp"

#include <cstddef>
#include <string_view>

namespace termseq {

inline namespace {

template <std::size_t I>
constexpr bool isValidColorIndex = I >= 0 && I <= 7;

}  // namespace

template <std::size_t I>
  requires isValidColorIndex<I>
struct SgrColor {
  using Index = std::size_t;
  static constexpr Index index = I;

  using Foreground4Bit = Sgr<I + 30u>;
  using Background4Bit = Sgr<I + 40u>;
  using Foreground = Sgr<38u, 5u, I>;
  using Background = Sgr<48u, 5u, I>;

  static constexpr auto foreground = Foreground{};
  static constexpr auto foreground4bit = Foreground4Bit{};
  static constexpr auto background = Background{};
  static constexpr auto background4bit = Background4Bit{};

  static constexpr std::string_view name();
};

using Black = SgrColor<0>;
template <>
constexpr std::string_view Black::name() {
  return "black";
}
using Red = SgrColor<1>;
template <>
constexpr std::string_view Red::name() {
  return "red";
}
using Green = SgrColor<2>;
template <>
constexpr std::string_view Green::name() {
  return "green";
}
using Yellow = SgrColor<3>;
template <>
constexpr std::string_view Yellow::name() {
  return "yellow";
}
using Blue = SgrColor<4>;
template <>
constexpr std::string_view Blue::name() {
  return "blue";
}
using Magenta = SgrColor<5>;
template <>
constexpr std::string_view Magenta::name() {
  return "magenta";
}
using Cyan = SgrColor<6>;
template <>
constexpr std::string_view Cyan::name() {
  return "cyan";
}
using White = SgrColor<7>;
template <>
constexpr std::string_view White::name() {
  return "white";
}

}  // namespace termseq

#endif
