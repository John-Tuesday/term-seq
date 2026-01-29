#include "TermSeq/ScopedReset.hpp"

#include <print>
#include <syncstream>

namespace termseq::test {

void testScopedReset();

void testScopedRestoreCursor();

}  // namespace termseq::test

int main() {
  termseq::test::testScopedReset();
  termseq::test::testScopedRestoreCursor();
  return 0;
}

void termseq::test::testScopedReset() {
  std::println("[Testing scoped reset]");
  {
    termseq::ScopedReset scoped{std::cout};
    std::println("This {}is {}formatted {}silly :P", termseq::italic,
                 termseq::bold, termseq::green.foreground);
  }
  std::println("[ reset ] this should be reset{}", termseq::reset);
  {
    termseq::ScopedReset scoped{std::osyncstream{std::cout}};
    std::println("This {}is {}formatted {}silly :P", termseq::italic,
                 termseq::bold, termseq::green.foreground);
  }
  std::println("[ reset ] this should be reset{}", termseq::reset);
}

void termseq::test::testScopedRestoreCursor() {
  auto& out = std::cout;
  std::println(out, "[Testing scoped restore cursor]");
  constexpr termseq::StaticString scopeEndText = "[ SCOPE END ]";
  constexpr termseq::StaticString originalText = "=+=+=\n=+=+=\n=+=+=\n>";
  constexpr auto expectedText =
      termseq::joinStaticStrings("=+=+=\nOVERWRITE\n=+=+=\n>", scopeEndText);
  std::println(out, "[Original]\n{}", originalText);
  std::println(out, "[Expected]\n{}", expectedText);
  std::println(out, "[Begin]");
  {
    termseq::ScopedRestoreCursor scoped{out};
    std::print(out, "{}", originalText);
    std::print(out, "{}", termseq::saveCursor);
    termseq::cursorPreviousLine(out, 2);
    std::print(out, "OVERWRITE");
  }
  std::println(out, "{}", scopeEndText);
  {
    termseq::ScopedRestoreCursor scoped{std::osyncstream{out}};
    std::osyncstream synced{out};
    std::print(synced, "{}", originalText);
    std::print(synced, "{}", termseq::saveCursor);
    termseq::cursorPreviousLine(synced, 2);
    std::print(synced, "OVERWRITE");
  }
  std::println(out, "{}", scopeEndText);
}
