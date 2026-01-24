#pragma once

#ifndef TERMSEQ_SCOPEDRESET_HPP
#define TERMSEQ_SCOPEDRESET_HPP

#include <TermSeq>

namespace termseq {

/**
 * Reset formatting on destruction RAII.
 */
template <typename T>
  requires requires(T t) {
    { t << termseq::reset };
  }
class ScopedReset {
 public:
  using Stream = T;

  template <typename S>
  ScopedReset(S&& out) : m_valid{true}, m_out{std::forward<S>(out)} {};

  ~ScopedReset() {
    if (valid()) {
      release();
    }
  }

  void release() noexcept {
    m_valid = false;
    m_out << termseq::reset;
  }

  bool valid() const noexcept { return m_valid; }

 private:
  bool m_valid{false};
  Stream m_out;
};

template <typename T>
ScopedReset(T&) -> ScopedReset<T&>;
template <typename T>
ScopedReset(T&&) -> ScopedReset<T>;

}  // namespace termseq

#endif
