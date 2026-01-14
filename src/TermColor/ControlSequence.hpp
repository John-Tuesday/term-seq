#pragma once

#ifndef TERMCOLOR_CONTROL_SEQUENCE_HPP
#define TERMCOLOR_CONTROL_SEQUENCE_HPP

#include "TermColor/StaticString.hpp"

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

#endif
