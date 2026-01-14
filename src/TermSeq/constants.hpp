#pragma once

#ifndef TERMSEQ_CONSTANTS_HPP
#define TERMSEQ_CONSTANTS_HPP

#include "Sgr.hpp"

namespace termseq {

inline constexpr auto reset = Sgr<0>{};
inline constexpr auto bold = Sgr<1>{};
inline constexpr auto italic = Sgr<3>{};
inline constexpr auto underline = Sgr<4>{};
inline constexpr auto normalIntensity = Sgr<22>{};
inline constexpr auto noItalic = Sgr<23>{};
inline constexpr auto noUnderline = Sgr<24>{};

}  // namespace termseq

#endif
