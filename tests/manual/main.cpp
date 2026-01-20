#include "TermSeq/ControlSequence.hpp"

#include <print>

int main() {
  std::println("First we {}bold{} one word", termseq::bold, termseq::reset);
  std::println("Then we {}italic{} a single word", termseq::italic,
               termseq::reset);
  std::println("The {}color{} is {}red{}", termseq::bold, termseq::reset,
               termseq::red.foreground, termseq::reset);
  std::println("The {}color{} is {}green{}", termseq::bold, termseq::reset,
               termseq::green.foreground, termseq::reset);
  return 0;
}
