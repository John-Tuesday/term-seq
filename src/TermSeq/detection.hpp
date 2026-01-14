#pragma once

#ifndef TERMSEQ_DETECTION_HPP
#define TERMSEQ_DETECTION_HPP

#include <iostream>

#ifndef TERMSEQ_ENABLE_POSIX_TERM_DETECTION
#if defined(__linux__) || defined(__DARWIN__)
#define TERMSEQ_ENABLE_POSIX_TERM_DETECTION 1
#else
#define TERMSEQ_ENABLE_POSIX_TERM_DETECTION 0
#endif
#endif

#if defined(TERMSEQ_ENABLE_POSIX_TERM_DETECTION) && \
    TERMSEQ_ENABLE_POSIX_TERM_DETECTION
#include "private/detection_posix.hpp"
#endif

namespace termseq {

inline bool isStdoutBuffer(const std::streambuf*);
inline bool isStdoutBuffer(const std::wstreambuf*);

inline bool isStderrBuffer(const std::streambuf*);
inline bool isStderrBuffer(const std::wstreambuf*);

/**
 * Returns a pointer to the underlying stream buffer or wrapped stream buffer.
 */
template <typename Stream>
  requires std::derived_from<
      std::remove_cvref_t<Stream>,
      std::basic_ostream<typename std::remove_cvref_t<Stream>::char_type>>
auto bufferOf(Stream&& stream) -> decltype(auto);

inline bool isTerminalOutputBuffer(const std::streambuf*);
inline bool isTerminalOutputBuffer(const std::wstreambuf*);

template <typename T>
  requires std::derived_from<
      std::remove_cvref_t<T>,
      std::basic_ostream<typename std::remove_cvref_t<T>::char_type>>
bool isTerminalOutputStream(T&& stream);

}  // namespace termseq

inline bool termseq::isStdoutBuffer(const std::streambuf* buf) {
  return buf == std::cout.rdbuf();
}
inline bool termseq::isStdoutBuffer(const std::wstreambuf* buf) {
  return buf == std::wcout.rdbuf();
}

inline bool termseq::isStderrBuffer(const std::streambuf* buf) {
  return buf == std::cerr.rdbuf() || buf == std::clog.rdbuf();
}
inline bool termseq::isStderrBuffer(const std::wstreambuf* buf) {
  return buf == std::wcerr.rdbuf() || buf == std::wclog.rdbuf();
}

inline bool termseq::isTerminalOutputBuffer(const std::streambuf* buf) {
#if TERMSEQ_ENABLE_POSIX_TERM_DETECTION
  return (isStdoutBuffer(buf) && termseq::posix::isStdoutTerminal()) ||
         (isStderrBuffer(buf) && termseq::posix::isStderrTerminal());
#else
  return isStdoutBuffer(buf) || isStderrBuffer(buf);
#endif
}

inline bool termseq::isTerminalOutputBuffer(const std::wstreambuf* buf) {
#if TERMSEQ_ENABLE_POSIX_TERM_DETECTION
  return (isStdoutBuffer(buf) && termseq::posix::isStdoutTerminal()) ||
         (isStderrBuffer(buf) && termseq::posix::isStderrTerminal());
#else
  return isStdoutBuffer(buf) || isStderrBuffer(buf);
#endif
}

template <typename Stream>
  requires std::derived_from<
      std::remove_cvref_t<Stream>,
      std::basic_ostream<typename std::remove_cvref_t<Stream>::char_type>>
auto termseq::bufferOf(Stream&& stream) -> decltype(auto) {
  using R = std::remove_cvref_t<Stream>;
  if constexpr (requires {
                  requires std::derived_from<
                      R, std::basic_osyncstream<typename R::char_type,
                                                typename R::traits_type,
                                                typename R::allocator_type>>;
                }) {
    return std::forward<Stream>(stream).get_wrapped();
  } else {
    return std::forward<Stream>(stream).rdbuf();
  }
}

template <typename T>
  requires std::derived_from<
      std::remove_cvref_t<T>,
      std::basic_ostream<typename std::remove_cvref_t<T>::char_type>>
bool termseq::isTerminalOutputStream(T&& stream) {
  return isTerminalOutputBuffer(termseq::bufferOf(std::forward<T>(stream)));
}

#endif
