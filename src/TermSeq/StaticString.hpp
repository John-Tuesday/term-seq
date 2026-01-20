#pragma once

#ifndef TERMSEQ_STATIC_STRING_HPP
#define TERMSEQ_STATIC_STRING_HPP

#include <format>
#include <string_view>

namespace termseq {

template <std::size_t>
struct StaticString;

template <std::ranges::sized_range... Args>
  requires(std::same_as<char, std::ranges::range_value_t<Args>> && ...)
consteval auto joinStaticStrings(Args&&... args)
    -> StaticString<(std::ranges::size(args) + ...) - sizeof...(args) + 1>;

}  // namespace termseq

template <std::size_t N>
struct std::formatter<termseq::StaticString<N>, char>
    : public std::formatter<std::string_view, char> {
  using std::formatter<std::string_view, char>::parse;

  template <typename FormatContext>
  FormatContext::iterator format(const termseq::StaticString<N>& s,
                                 FormatContext& ctx) const {
    return std::formatter<std::string_view, char>::format(s, ctx);
  }
};

template <std::size_t N>
struct termseq::StaticString {
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

template <std::size_t L, std::size_t R>
constexpr bool operator==(const termseq::StaticString<L>& lhs,
                          const termseq::StaticString<R>& rhs) {
  return static_cast<std::string_view>(lhs) ==
         static_cast<std::string_view>(rhs);
}

template <std::ranges::sized_range... Args>
  requires(std::same_as<char, std::ranges::range_value_t<Args>> && ...)
consteval auto termseq::joinStaticStrings(Args&&... args)
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
