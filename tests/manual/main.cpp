#include "TermSeq/ControlSequence.hpp"
#include "TermSeq/ScopedReset.hpp"

#include <print>
#include <syncstream>

void testScopedReset();

int main() {
  testScopedReset();
  std::println("This is after the reset function...");
  std::println("First we {}bold{} one word", termseq::bold, termseq::reset);
  std::println("Then we {}italic{} a single word", termseq::italic,
               termseq::reset);
  std::println("The {}color{} is {}red{}", termseq::bold, termseq::reset,
               termseq::red.foreground, termseq::reset);
  std::println("The {}color{} is {}green{}", termseq::bold, termseq::reset,
               termseq::green.foreground, termseq::reset);
  return 0;
}

void testScopedReset() {
  std::println("Testing scoped reset...");
  termseq::ScopedReset scoped{std::osyncstream{std::cout}};
  // termseq::ScopedReset scoped{std::cout};
  std::println("This is formatted {}silly{} :P", termseq::italic,
               termseq::green.foreground);
}
