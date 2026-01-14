#include "TermSeq/SgrColor.hpp"
#include "TermSeq/constants.hpp"

#include <iostream>
#include <print>

namespace termseq::test {

template <typename... Colors>
  requires requires {
    requires(std::same_as<termseq::SgrColor<Colors::index>, Colors> && ...);
  }
bool testColors();

template <std::size_t I, std::size_t N>
bool testSgrColor(termseq::SgrColor<I> color, termseq::SgrColor<N> other);

}  // namespace termseq::test

int main() {
  std::println(std::cout, "CTEST_FULL_OUTPUT");
  return termseq::test::testColors<
             termseq::Black, termseq::Red, termseq::Green, termseq::Yellow,
             termseq::Blue, termseq::Magenta, termseq::Cyan, termseq::White>()
             ? 0
             : 1;
}

template <typename... Colors>
  requires requires {
    requires(std::same_as<termseq::SgrColor<Colors::index>, Colors> && ...);
  }
bool termseq::test::testColors() {
  auto lam = []<typename C, typename... Cs>(C&& c, Cs&&... cs) -> bool {
    return (testSgrColor(std::forward<C>(c), std::forward<Cs>(cs)) && ...);
  };
  return (lam(Colors{}, Colors{}...) && ...);
}

template <std::size_t I, std::size_t N>
bool termseq::test::testSgrColor(termseq::SgrColor<I> color,
                                 termseq::SgrColor<N> other) {
  auto& os = std::cout;
  std::println(os, "Testing {}{}{} + {}{}{}", color.foreground, color.name(),
               termseq::reset, other.foreground, other.name(), termseq::reset);
  constexpr std::string_view norm = "normal";
  constexpr std::string_view alt = "4bit";
  std::println(os, "Using {:{}} {}{}colors{} foreground: {} and background: {}",
               norm, norm.size(), color.foreground, other.background,
               termseq::reset, color.name(), other.name());
  std::println(os, "Using {:{}} {}{}colors{} foreground: {} and background: {}",
               alt, norm.size(), color.foreground, other.background,
               termseq::reset, color.name(), other.name());
  std::println(os, "");
  return true;
}
