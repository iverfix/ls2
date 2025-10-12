#include "ArgumentParser.h"
#include <gtest/gtest.h>
#include <initializer_list>
#include <span>
#include <stdexcept>
#include <vector>


// Equality operator for simpler test cases below
auto operator==(const UserOptions& lhs, const UserOptions& rhs) -> bool { return lhs.showHiddenFiles == rhs.showHiddenFiles && lhs.path == rhs.path; };

namespace {
// Helper to create argc/argv argument lists from literals
std::vector<const char*> makeArgs(std::initializer_list<const char*> args) { return std::vector<const char*>{ args }; }

TEST(ArgumentParser, NoArguments)
{
  std::vector<const char*> argv{};
  EXPECT_THROW(parseArgs(argv), std::invalid_argument);
}

TEST(ArgumentParser, SingleArgument)
{
  auto argv = makeArgs({ "program.a" });
  const UserOptions options = parseArgs(argv);
  EXPECT_EQ(options, UserOptions());
}

TEST(ArgumentParser, ParsesAllFlag_ShortAndLongEquivalent)
{
  auto validAllArgument = makeArgs({ "program.a", "-a" });
  auto validExtendedAllArguments = makeArgs({ "program.a", "--all" });
  const UserOptions options = parseArgs(validAllArgument);
  const UserOptions optionsExtended = parseArgs(validExtendedAllArguments);
  EXPECT_EQ(options, optionsExtended);
  EXPECT_EQ(options.showHiddenFiles, true);
}

TEST(ArgumentParser, InvalidArgument)
{
  auto invalidArguments = makeArgs({ "program.a", "kake" });
  EXPECT_THROW(parseArgs(invalidArguments), std::invalid_argument);
}
}// namespace
