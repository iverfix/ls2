#include "argumentParser.h"
#include <gtest/gtest.h>
#include <initializer_list>
#include <stdexcept>


// Equality operator for simpler test cases below
bool operator==(const UserOptions& lhs, const UserOptions& rhs) { return lhs.showHiddenFiles == rhs.showHiddenFiles && lhs.path == rhs.path; };

namespace {
// Helper to create argc/argv argument lists from literals
std::vector<const char*> makeArgs(std::initializer_list<const char*> args) { return std::vector<const char*>{ args }; }

TEST(ArgumentParser, NoArguments) { EXPECT_THROW(parseArgs(0, nullptr), std::invalid_argument); }

TEST(ArgumentParser, SingleArgument)
{
  auto argv = makeArgs({ "program.a" });
  UserOptions options = parseArgs(argv.size(), argv.data());
  EXPECT_EQ(options, UserOptions());
}

TEST(ArgumentParser, ParsesAllFlag_ShortAndLongEquivalent)
{
  auto validAllArgument = makeArgs({ "program.a", "-a" });
  auto validExtendedAllArguments = makeArgs({ "program.a", "--all" });
  UserOptions options = parseArgs(validAllArgument.size(), validAllArgument.data());
  UserOptions optionsExtended = parseArgs(validExtendedAllArguments.size(), validExtendedAllArguments.data());
  EXPECT_EQ(options, optionsExtended);
  EXPECT_EQ(options.showHiddenFiles, true);
}

TEST(ArgumentParser, InvalidArgument)
{
  auto invalidArguments = makeArgs({ "program.a", "kake" });
  EXPECT_THROW(parseArgs(invalidArguments.size(), invalidArguments.data()), std::runtime_error);
}
}// namespace
