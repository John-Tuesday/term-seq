#include "TermSeq/detection.hpp"

#include <fstream>
#include <iostream>
#include <print>
#include <string_view>
#include <syncstream>

namespace termseq::test {

template <typename StringLike>
constexpr bool softAssert(bool value, StringLike&& message);

template <typename StringLike>
constexpr bool softAssert(bool value, StringLike&& message) {
  if (!value) {
    std::println("{}", std::forward<StringLike>(message));
  }
  return value;
}

struct TestResult;

bool runTests();

TestResult identifiesStdStreams();

TestResult nonStdStreamsAreFalse();

TestResult identifiesStdStreamsInOsyncstream();

struct TestResult {
  std::string_view message() { return m_message; }

  bool failed() const { return m_failed; }
  bool passed() const { return !failed(); }

  template <typename T>
  auto checkIfStreamIsTerminalOutput(this auto&& self,
                                     T&& stream,
                                     bool expect,
                                     std::string_view msg = {})
      -> decltype(auto);

  explicit operator bool(this auto&& self) { return self.passed(); }

 private:
  bool m_failed{false};
  std::string m_message{};
};

}  // namespace termseq::test

int main() {
  return (termseq::test::runTests() ? 0 : 1);
}

template <typename T>
auto termseq::test::TestResult::checkIfStreamIsTerminalOutput(
    this auto&& self,
    T&& stream,
    bool expect,
    std::string_view msg) -> decltype(auto) {
  if (self.failed())
    return self;
  bool result = termseq::isTerminalOutputStream(std::forward<T>(stream));
  bool isStd =
      termseq::isStdoutBuffer(termseq::bufferOf(std::forward<T>(stream))) ||
      termseq::isStderrBuffer(termseq::bufferOf(std::forward<T>(stream)));
  self.m_failed = result != expect;
  self.m_message = std::format(
      "Is terminal output stream? {}: {:<15} {:>5} "
      "== {:<5} \nis std buffer {}",
      self.passed() ? "PASS" : "FAIL", msg, result, expect, isStd);
  return self;
}

bool termseq::test::runTests() {
  bool failed{false};
  if (TestResult result = identifiesStdStreams(); !result) {
    std::println("{}", result.message());
    failed = true;
  }
  if (TestResult result = nonStdStreamsAreFalse(); !result) {
    std::println("{}", result.message());
    failed = true;
  }
  if (TestResult result = identifiesStdStreamsInOsyncstream(); !result) {
    std::println("{}", result.message());
    failed = true;
  }
  if (!failed) {
    std::println("All tests passed!");
  }
  return !failed;
}

termseq::test::TestResult termseq::test::identifiesStdStreams() {
  TestResult result =
      TestResult{}
          .checkIfStreamIsTerminalOutput(std::cout, true, "cout")
          .checkIfStreamIsTerminalOutput(std::cerr, true, "cerr")
          .checkIfStreamIsTerminalOutput(std::clog, true, "clog")
          .checkIfStreamIsTerminalOutput(std::wcerr, true, "wcerr")
          .checkIfStreamIsTerminalOutput(std::wcout, true, "wcout")
          .checkIfStreamIsTerminalOutput(std::wclog, true, "wclog");
  return result;
}

termseq::test::TestResult termseq::test::nonStdStreamsAreFalse() {
  std::ostream nullStream{nullptr};
  std::ofstream file{};
  std::osyncstream sync{file};
  TestResult result =
      TestResult{}
          .checkIfStreamIsTerminalOutput(nullStream, false, "null ostream")
          .checkIfStreamIsTerminalOutput(file, false, "file")
          .checkIfStreamIsTerminalOutput(sync, false, "sync(file)");
  return result;
}

termseq::test::TestResult termseq::test::identifiesStdStreamsInOsyncstream() {
  TestResult result =
      TestResult{}
          .checkIfStreamIsTerminalOutput(std::osyncstream{std::cout}, true,
                                         "sync(cout)")
          .checkIfStreamIsTerminalOutput(std::osyncstream{std::cerr}, true,
                                         "sync(cerr)")
          .checkIfStreamIsTerminalOutput(std::osyncstream{std::clog}, true,
                                         "sync(clog)")
          .checkIfStreamIsTerminalOutput(std::wosyncstream{std::wcout}, true,
                                         "sync(wcout)")
          .checkIfStreamIsTerminalOutput(std::wosyncstream{std::wcerr}, true,
                                         "sync(wcerr)")
          .checkIfStreamIsTerminalOutput(std::wosyncstream{std::wclog}, true,
                                         "sync(wclog)");
  return result;
}
