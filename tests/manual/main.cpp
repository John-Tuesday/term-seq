#include <TermColor>

#include <print>

int main() {
  std::println("The {}color{} is {}red{}", sgr::bold, sgr::reset,
               sgr::Red::foreground, sgr::reset);
  std::println("The {}color{} is {}green{}", sgr::bold, sgr::reset,
               sgr::Green::foreground, sgr::reset);
  return 0;
}
