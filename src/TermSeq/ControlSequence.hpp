#pragma once

#ifndef TERMSEQ_CONTROL_SEQUENCE_HPP
#define TERMSEQ_CONTROL_SEQUENCE_HPP

#include "TermSeq/StaticString.hpp"

#include <iostream>
#include <print>

namespace termseq::codes {

/**
 * Escape Sequence Introducer
 */
inline constexpr termseq::StaticString ESC = "\x1b";

/**
 * Control Sequence Introducer
 */
inline constexpr termseq::StaticString CSI =
    termseq::joinStaticStrings(ESC, "[");

/**
 * Operating System Command
 */
inline constexpr termseq::StaticString OSC =
    termseq::joinStaticStrings(ESC, "]");

}  // namespace termseq::codes

namespace termseq {

/**
 * Save cursor position, formatting attributes, etc..
 */
inline constexpr termseq::StaticString saveCursor =
    termseq::joinStaticStrings(termseq::codes::ESC, "7");

/**
 * Restore cursor from previous `termseq::saveCursor`.
 */
inline constexpr termseq::StaticString restoreCursor =
    termseq::joinStaticStrings(termseq::codes::ESC, "8");

/**
 * Erase entire line.
 */
inline constexpr termseq::StaticString eraseLine =
    termseq::joinStaticStrings(termseq::codes::CSI, "2K");

/**
 * Move the cursor forward by `offset` lines.
 */
inline void cursorNextLine(std::ostream& out, std::size_t offset) {
  std::print(out, "{}{}{}", termseq::codes::CSI, offset, "E");
}

/**
 * Move the cursor `offset` previous lines.
 */
inline void cursorPreviousLine(std::ostream& out, std::size_t offset) {
  std::print(out, "{}{}{}", termseq::codes::CSI, offset, "F");
}

template <std::ranges::sized_range... Args>
  requires(std::same_as<char, std::ranges::range_value_t<Args>> && ...)
constexpr auto makeSgr(Args&&... args) {
  // TODO: add seperator
  return termseq::joinStaticStrings(termseq::codes::CSI,
                                    std::forward<Args>(args)..., "m");
}

inline constexpr termseq::StaticString reset = termseq::makeSgr();
inline constexpr termseq::StaticString bold = termseq::makeSgr("1");
inline constexpr termseq::StaticString italic = termseq::makeSgr("3");
inline constexpr termseq::StaticString underline = termseq::makeSgr("4");
inline constexpr termseq::StaticString noItalic = termseq::makeSgr("23");
inline constexpr termseq::StaticString noUnderline = termseq::makeSgr("24");

template <typename T>
constexpr auto sgr8BitForeground(T&& t) -> decltype(auto) {
  return termseq::makeSgr("38;5;", std::forward<T>(t));
}

template <typename T>
constexpr auto sgr8BitBackground(T&& t) -> decltype(auto) {
  return termseq::makeSgr("48;5;", std::forward<T>(t));
}

template <std::size_t N>
struct Color8Bit {
  template <std::ranges::sized_range Spec>
    requires(std::same_as<char, std::ranges::range_value_t<Spec>>)
  consteval Color8Bit(Spec&& spec)
      : foreground{sgr8BitForeground(std::forward<Spec>(spec))},
        background{sgr8BitBackground(std::forward<Spec>(spec))} {}

  const termseq::StaticString<N> foreground{};
  const termseq::StaticString<N> background{};
};

template <std::ranges::sized_range Spec>
  requires(std::same_as<char, std::ranges::range_value_t<Spec>>)
Color8Bit(Spec&& spec)
    -> Color8Bit<decltype(sgr8BitForeground(std::forward<Spec>(spec)))::size()>;

inline constexpr Color8Bit black{"0"};
inline constexpr Color8Bit red{"1"};
inline constexpr Color8Bit green{"2"};
inline constexpr Color8Bit yellow{"3"};
inline constexpr Color8Bit blue{"4"};
inline constexpr Color8Bit magenta{"5"};
inline constexpr Color8Bit cyan{"6"};
inline constexpr Color8Bit white{"7"};

}  // namespace termseq

#endif
