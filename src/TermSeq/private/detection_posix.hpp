#pragma once

#ifndef TERMSEQ_PRIVATE_DETECTION_POSIX_HPP
#define TERMSEQ_PRIVATE_DETECTION_POSIX_HPP

#ifdef __has_include
#if __has_include(<unistd.h>)
#else
#error "Missing header <unistd.h>"
#endif
#endif

#include <unistd.h>

namespace termseq::posix {

inline bool isStdoutTerminal() {
  return isatty(STDOUT_FILENO) == 1;
}

inline bool isStderrTerminal() {
  return isatty(STDERR_FILENO) == 1;
}

}  // namespace termseq::posix

#endif
