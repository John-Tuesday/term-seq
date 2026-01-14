#pragma once

#ifndef TERMCOLOR_CONTROL_SEQUENCE_HPP
#define TERMCOLOR_CONTROL_SEQUENCE_HPP

#include "TermColor/StaticString.hpp"

namespace sgr::codes {

/**
 * Escape Sequence Introducer
 */
inline constexpr term_color::StaticString ESC = "\x1b";

/**
 * Control Sequence Introducer
 */
inline constexpr term_color::StaticString CSI =
    term_color::joinStaticStrings(ESC, "[");

/**
 * Operating System Command
 */
inline constexpr term_color::StaticString OSC =
    term_color::joinStaticStrings(ESC, "]");

}  // namespace sgr::codes

#endif
