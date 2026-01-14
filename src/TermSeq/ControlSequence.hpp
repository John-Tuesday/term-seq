#pragma once

#ifndef TERMSEQ_CONTROL_SEQUENCE_HPP
#define TERMSEQ_CONTROL_SEQUENCE_HPP

#include "StaticString.hpp"

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
