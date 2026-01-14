#pragma once

#ifndef TERMCOLOR_STATIC_STRING_HPP
#define TERMCOLOR_STATIC_STRING_HPP

#include <format>
#include <string_view>

namespace term_color {

template <std::size_t>
struct StaticString;

template <std::ranges::sized_range... Args>
  requires(std::same_as<char, std::ranges::range_value_t<Args>> && ...)
consteval auto joinStaticStrings(Args&&... args)
    -> StaticString<(std::ranges::size(args) + ...) - sizeof...(args) + 1>;

}  // namespace term_color

template <std::size_t N>
struct std::formatter<term_color::StaticString<N>, char>
    : public std::formatter<std::string_view, char> {
  using std::formatter<std::string_view, char>::parse;

  template <typename FormatContext>
  FormatContext::iterator format(const term_color::StaticString<N>& s,
                                 FormatContext& ctx) const {
    return std::formatter<std::string_view, char>::format(s, ctx);
  }
};

template <std::size_t N>
struct term_color::StaticString {
  constexpr StaticString() {}

  constexpr StaticString(const StaticString&) = default;

  constexpr StaticString(const char (&cstr)[N]) {
    std::ranges::copy_n(cstr, N, m_data);
  }

  constexpr StaticString(const std::array<char, N>& cstr) {
    std::ranges::copy(cstr, m_data);
  }

  constexpr operator std::string_view() const {
    return std::string_view{data(), size()};
  }

  constexpr auto begin(this auto&& self) { return self.data(); }

  constexpr auto end(this auto&& self) { return self.data() + self.size(); }

  constexpr auto data(this auto&& self) { return self.m_data; }

  static constexpr std::size_t size() { return N; }

 private:
  char m_data[N]{};
};

template <std::ranges::sized_range... Args>
  requires(std::same_as<char, std::ranges::range_value_t<Args>> && ...)
consteval auto term_color::joinStaticStrings(Args&&... args)
    -> StaticString<(std::ranges::size(args) + ...) - sizeof...(args) + 1> {
  std::array<char, (std::ranges::size(args) + ...) - sizeof...(args) + 1>
      data{};
  auto it = data.begin();
  ((it = std::ranges::copy_n(std::ranges::begin(args),
                             std::ranges::size(args) - 1, it)
             .out),
   ...);
  return StaticString{data};
}

#endif
