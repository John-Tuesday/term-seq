#pragma once

#ifndef TERMSEQ_SGR_HPP
#define TERMSEQ_SGR_HPP

#include <algorithm>
#include <array>
#include <charconv>
#include <format>
#include <string_view>

/**
 * **Select Graphic Rendition** style terminal text.
 */
namespace termseq {

/**
 * Constructs an `SGR` character sequence with codes `Ns...` in order.
 */
template <std::size_t... Ns>
struct Sgr {
  static constexpr std::string_view str() {
    return std::string_view{m_chars.begin(), m_chars.end()};
  }

  constexpr operator std::string_view() { return str(); }

 private:
  static consteval std::size_t digitsOf(std::size_t num);
  static consteval auto toChars() -> decltype(auto);

  static constexpr std::string_view prefix = "\33[";
  static constexpr std::string_view suffix = "m";
  static constexpr std::string_view sep = ";";
  static constexpr std::array m_chars{toChars()};
};

}  // namespace termseq

template <std::size_t... Ns>
struct std::formatter<termseq::Sgr<Ns...>, char> {
  template <typename ParseContext>
  constexpr ParseContext::iterator parse(ParseContext& ctx) {
    return ctx.begin();
  }

  template <typename FmtContext>
  FmtContext::iterator format(termseq::Sgr<Ns...>, FmtContext& ctx) const {
    return std::ranges::copy(termseq::Sgr<Ns...>::str(), ctx.out()).out;
  }
};

template <std::size_t... Ns>
consteval std::size_t termseq::Sgr<Ns...>::digitsOf(std::size_t num) {
  if (num == 0)
    return 1;
  std::size_t digits{0};
  for (std::size_t n{num}; n > 0; ++digits)
    n /= 10u;
  return digits;
}

template <std::size_t... Ns>
consteval auto termseq::Sgr<Ns...>::toChars() -> decltype(auto) {
  std::array<char, 1 + prefix.size() + suffix.size() +
                       (sep.size() * sizeof...(Ns) - 1) + (digitsOf(Ns) + ...)>
      arr{'\0'};
  auto it = std::ranges::copy(prefix, arr.begin()).out;
  (((it = std::to_chars(it, it + digitsOf(Ns), Ns).ptr),
    (it = std::ranges::copy(sep, it).out)),
   ...);
  std::ranges::copy(suffix, arr.begin() + arr.size() - suffix.size() - 1);
  return arr;
}

#endif
