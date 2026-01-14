#include <TermSeq>

#include <print>

int main() {
  std::println("The {}color{} is {}red{}", termseq::bold, termseq::reset,
               termseq::Red::foreground, termseq::reset);
  std::println("The {}color{} is {}green{}", termseq::bold, termseq::reset,
               termseq::Green::foreground, termseq::reset);
  return 0;
}
