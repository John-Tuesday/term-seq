#include "TermColor/SgrColor.hpp"
#include "TermColor/constants.hpp"

#include <iostream>
#include <print>

namespace sgr::test {

template <typename... Colors>
  requires requires {
    requires(std::same_as<sgr::SgrColor<Colors::index>, Colors> && ...);
  }
bool testColors();

template <std::size_t I, std::size_t N>
bool testSgrColor(sgr::SgrColor<I> color, sgr::SgrColor<N> other);

} // namespace sgr::test

int main() {
  std::println(std::cout, "CTEST_FULL_OUTPUT");
  return sgr::test::testColors<sgr::Black, sgr::Red, sgr::Green, sgr::Yellow,
                               sgr::Blue, sgr::Magenta, sgr::Cyan, sgr::White>()
             ? 0
             : 1;
}

template <typename... Colors>
  requires requires {
    requires(std::same_as<sgr::SgrColor<Colors::index>, Colors> && ...);
  }
bool sgr::test::testColors() {
  auto lam = []<typename C, typename... Cs>(C &&c, Cs &&...cs) -> bool {
    return (testSgrColor(std::forward<C>(c), std::forward<Cs>(cs)) && ...);
  };
  return (lam(Colors{}, Colors{}...) && ...);
}

template <std::size_t I, std::size_t N>
bool sgr::test::testSgrColor(sgr::SgrColor<I> color, sgr::SgrColor<N> other) {
  auto &os = std::cout;
  std::println(os, "Testing {}{}{} + {}{}{}", color.foreground, color.name(),
               sgr::reset, other.foreground, other.name(), sgr::reset);
  constexpr std::string_view norm = "normal";
  constexpr std::string_view alt = "4bit";
  std::println(os, "Using {:{}} {}{}colors{} foreground: {} and background: {}",
               norm, norm.size(), color.foreground, other.background,
               sgr::reset, color.name(), other.name());
  std::println(os, "Using {:{}} {}{}colors{} foreground: {} and background: {}",
               alt, norm.size(), color.foreground, other.background, sgr::reset,
               color.name(), other.name());
  std::println(os, "");
  return true;
}
