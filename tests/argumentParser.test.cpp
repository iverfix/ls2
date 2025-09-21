#include "argumentParser.h"
#include <gtest/gtest.h>
#include <initializer_list>
#include <stdexcept>
#include <vector>


// Equality operator for simpler test cases below
auto operator==(const UserOptions& lhs, const UserOptions& rhs) -> bool { return lhs.showHiddenFiles == rhs.showHiddenFiles && lhs.path == rhs.path; };

namespace {
// Helper to create argc/argv argument lists from literals
auto makeArgs(std::initializer_list<const char*> args) -> std::vector<const char*> { return std::vector<const char*>{ args }; }

TEST(ArgumentParser, NoArguments) { EXPECT_THROW(parseArgs(0, nullptr), std::invalid_argument); }

TEST(ArgumentParser, SingleArgument)
{
  auto argv = makeArgs({ "program.a" });
  const UserOptions options = parseArgs(argv.size(), argv.data());
  EXPECT_EQ(options, UserOptions());
}

TEST(ArgumentParser, ParsesAllFlag_ShortAndLongEquivalent)
{
  auto validAllArgument = makeArgs({ "program.a", "-a" });
  auto validExtendedAllArguments = makeArgs({ "program.a", "--all" });
  const UserOptions options = parseArgs(validAllArgument.size(), validAllArgument.data());
  const UserOptions optionsExtended = parseArgs(validExtendedAllArguments.size(), validExtendedAllArguments.data());
  EXPECT_EQ(options, optionsExtended);
  EXPECT_EQ(options.showHiddenFiles, true);
}

TEST(ArgumentParser, InvalidArgument)
{
  auto invalidArguments = makeArgs({ "program.a", "kake" });
  EXPECT_THROW(parseArgs(invalidArguments.size(), invalidArguments.data()), std::runtime_error);
}
}// namespace
