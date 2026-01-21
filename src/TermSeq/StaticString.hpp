#pragma once

#ifndef TERMSEQ_STATIC_STRING_HPP
#define TERMSEQ_STATIC_STRING_HPP

#include <format>
#include <string_view>

namespace termseq {

/**
 * Compile-time string.
 *
 * Size includes the null-terminator.
 */
template <std::size_t>
struct StaticString;

/**
 * Join character array-like objects into a single `termseq::StaticString`.
 */
template <std::ranges::sized_range... Args>
  requires(std::same_as<char, std::ranges::range_value_t<Args>> && ...)
consteval auto joinStaticStrings(Args&&... args)
    -> StaticString<(std::ranges::size(args) + ...) - sizeof...(args) + 1>;

}  // namespace termseq

template <std::size_t N>
struct termseq::StaticString {
  /**
   * Constructs default empty character array
   */
  constexpr StaticString() {}

  constexpr StaticString(const StaticString&) = default;

  /**
   * Copys the c-string verbatim.
   */
  constexpr StaticString(const char (&cstr)[N]) {
    std::ranges::copy_n(cstr, N, m_data);
  }

  /**
   * Identical to `StaticString(const char(&)[N])`.
   *
   * Facilitates easier concatenation.
   */
  constexpr StaticString(const std::array<char, N>& cstr) {
    std::ranges::copy(cstr, m_data);
  }

  /**
   * Converts into a view of the string contents.
   */
  constexpr operator std::string_view() const {
    return std::string_view{data(), size() - 1};
  }

  /**
   * First iterator of the characters.
   */
  constexpr auto begin(this auto&& self) { return self.data(); }

  /**
   * Iterator just past the last position.
   */
  constexpr auto end(this auto&& self) { return self.data() + self.size(); }

  /**
   * Returns the underlying pointer.
   */
  constexpr auto data(this auto&& self) { return self.m_data; }

  /**
   * Size of the character array as it is stored.
   */
  static constexpr std::size_t size() { return N; }

 private:
  char m_data[N]{};
};

/**
 * Compares `termseq::StaticString` by first converting to `std::string_view`,
 * then using its implementation.
 */
template <std::size_t L, std::size_t R>
constexpr bool operator==(const termseq::StaticString<L>& lhs,
                          const termseq::StaticString<R>& rhs) noexcept {
  return static_cast<std::string_view>(lhs) ==
         static_cast<std::string_view>(rhs);
}

/**
 * Compares `termseq::StaticString` by first converting to `std::string_view`,
 * then using its implementation.
 */
template <std::size_t L>
constexpr bool operator==(const termseq::StaticString<L>& lhs,
                          std::string_view rhs) noexcept {
  return static_cast<std::string_view>(lhs) == rhs;
}

/**
 * Compares `termseq::StaticString` by first converting to `std::string_view`,
 * then using its implementation.
 */
template <std::size_t L, std::size_t R>
constexpr std::strong_ordering operator<=>(
    const termseq::StaticString<L>& lhs,
    const termseq::StaticString<R>& rhs) noexcept {
  return static_cast<std::string_view>(lhs) <=>
         static_cast<std::string_view>(rhs);
}

/**
 * Concatenates given character sequences into a singular
 * `termseq::StaticString`.
 */
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

/**
 * Formatter which borrows its implementation from the `std::string_view`
 * formatter.
 */
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

#endif
