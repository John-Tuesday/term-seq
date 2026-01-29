#pragma once

#ifndef TERMSEQ_SCOPEDRESET_HPP
#define TERMSEQ_SCOPEDRESET_HPP

#include <TermSeq>

#include <cassert>
#include <utility>

/**
 * Type constraints.
 */
namespace termseq::concepts {

/**
 * An object of given type `R` can be inserted into another object of type `T`
 * using the operator `<<`.
 */
template <typename T, typename R>
concept InsertableInto = requires(T t, R r) { t << r; };

/**
 * Requires `T` to be a type which can be printed to and `R` to be formattable
 * using `CharT`.
 */
template <typename T, typename CharT, typename R>
concept PrintableWith = std::formattable<R, CharT> &&
                        requires(T t, R r) { std::print(t, "{}", r); };

}  // namespace termseq::concepts

namespace termseq {

/**
 * Write to given sequence to output on destruction.
 *
 * RAII style.
 */
template <typename T, typename S, typename C = char>
  requires termseq::concepts::PrintableWith<T, C, S> ||
           termseq::concepts::InsertableInto<T, S>
class ScopedOutput {
 public:
  using CharT = C;
  using Seq = S;
  using Stream = T;

  template <typename R, typename U>
  ScopedOutput(R&& out, U&& seq)
      : m_valid{true},
        m_out{std::forward<R>(out)},
        m_seq{std::forward<U>(seq)} {}

  ~ScopedOutput() {
    if (valid())
      release();
  }

  template <typename Self>
  auto out(this Self&& self) -> decltype(auto) {
    return std::forward_like<Self>(self.m_out);
  }

  void release(this auto&& self) {
    assert(self.valid());
    if constexpr (termseq::concepts::PrintableWith<Stream, CharT, Seq>) {
      std::print(self.out(), "{}", self.m_seq);
    } else if constexpr (termseq::concepts::InsertableInto<Stream, Seq>) {
      self.out() << self.m_seq;
    } else {
      std::unreachable();
    }
    self.m_valid = false;
  }

  bool valid() const { return m_valid; }

 private:
  bool m_valid{false};
  Stream m_out;
  Seq m_seq;
};

template <typename T, typename U>
ScopedOutput(T&, U&) -> ScopedOutput<T&, U&>;
template <typename T, typename U>
ScopedOutput(T&&, U&&) -> ScopedOutput<T, U>;

/**
 * Restore cursor on destruction.
 *
 * RAII style.
 */
template <typename T>
class ScopedRestoreCursor
    : public termseq::ScopedOutput<T, decltype(termseq::restoreCursor)> {
  using Parent = termseq::ScopedOutput<T, decltype(termseq::restoreCursor)>;

 public:
  template <typename S>
  ScopedRestoreCursor(S&& out)
      : Parent{std::forward<S>(out), termseq::restoreCursor} {}
};

template <typename T>
ScopedRestoreCursor(T&) -> ScopedRestoreCursor<T&>;
template <typename T>
ScopedRestoreCursor(T&&) -> ScopedRestoreCursor<T>;

/**
 * Reset formatting on destruction RAII.
 */
template <typename T>
class ScopedReset : public termseq::ScopedOutput<T, decltype(termseq::reset)> {
  using ScopedOutputParent = termseq::ScopedOutput<T, decltype(termseq::reset)>;

 public:
  template <typename S>
  ScopedReset(S&& out)
      : ScopedOutputParent{std::forward<S>(out), termseq::reset} {}
};

template <typename T>
ScopedReset(T&) -> ScopedReset<T&>;
template <typename T>
ScopedReset(T&&) -> ScopedReset<T>;

}  // namespace termseq

#endif
