#include "TermSeq/ControlSequence.hpp"

#include <iostream>
#include <print>

namespace termseq::test {

void testPrintColor(std::string_view name, std::string_view foreground);

}  // namespace termseq::test

int main() {
  std::println(std::cout, "CTEST_FULL_OUTPUT");
  termseq::test::testPrintColor("black", termseq::black.foreground);
  termseq::test::testPrintColor("red", termseq::red.foreground);
  termseq::test::testPrintColor("green", termseq::green.foreground);
  termseq::test::testPrintColor("yellow", termseq::yellow.foreground);
  termseq::test::testPrintColor("blue", termseq::blue.foreground);
  termseq::test::testPrintColor("magenta", termseq::magenta.foreground);
  termseq::test::testPrintColor("cyan", termseq::cyan.foreground);
  termseq::test::testPrintColor("white", termseq::white.foreground);
  return 0;
}

void termseq::test::testPrintColor(std::string_view name,
                                   std::string_view foreground) {
  std::array backgrounds{termseq::black.background, termseq::red.background,
                         termseq::green.background, termseq::yellow.background,
                         termseq::blue.background,  termseq::magenta.background,
                         termseq::cyan.background,  termseq::white.background};
  for (std::string_view bg : backgrounds) {
    std::println("Using {}{}{}{}", foreground, bg, name, termseq::reset);
  }
}
