#pragma once

#ifndef TERMCOLOR_PRIVATE_DETECTION_POSIX_HPP
#define TERMCOLOR_PRIVATE_DETECTION_POSIX_HPP

#ifdef __has_include
#if __has_include(<unistd.h>)
#else
#error "Missing header <unistd.h>"
#endif
#endif

#include <unistd.h>

namespace sgr::posix {

bool isStdoutTerminal() { return isatty(STDOUT_FILENO) == 1; }

bool isStderrTerminal() { return isatty(STDERR_FILENO) == 1; }

} // namespace sgr::posix

#endif
