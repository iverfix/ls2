#include "ArgumentParser.h"
#include <gtest/gtest.h>
#include <initializer_list>
#include <span>
#include <stdexcept>
#include <vector>


namespace {
// Helper to create argc/argv argument lists from literals
std::vector<const char*> makeArgs(std::initializer_list<const char*> args) { return std::vector<const char*>{ args }; }

TEST(ArgumentParser, ThrowsIfNoArgs)
{
  std::vector<const char*> args;
  EXPECT_THROW(parseArgs(args), std::invalid_argument);
}

TEST(ArgumentParser, ParsesSingleShortFlag)
{
  auto args = makeArgs({ "program", "-a" });
  auto opts = parseArgs(args);

  EXPECT_TRUE(opts.showHiddenFiles);
  EXPECT_FALSE(opts.showLongFormat);
}

TEST(ArgumentParser, ParsesSingleLongFlag)
{
  auto args = makeArgs({ "program", "--all" });
  auto opts = parseArgs(args);

  EXPECT_TRUE(opts.showHiddenFiles);
  EXPECT_FALSE(opts.showLongFormat);
}

TEST(ArgumentParser, ParsesLongListFlag)
{
  auto args = makeArgs({ "program", "-l" });
  auto opts = parseArgs(args);

  EXPECT_TRUE(opts.showLongFormat);
  EXPECT_TRUE(opts.longListOptions.showUserGroup);
  EXPECT_TRUE(opts.longListOptions.showOwnerGroup);
}

TEST(ArgumentParser, ParsesGFlagDisablesUserGroup)
{
  auto args = makeArgs({ "program", "-g" });
  auto opts = parseArgs(args);

  EXPECT_TRUE(opts.showLongFormat);
  EXPECT_FALSE(opts.longListOptions.showUserGroup);
  EXPECT_TRUE(opts.longListOptions.showOwnerGroup);
}

TEST(ArgumentParser, ParsesOFlagDisablesOwnerGroup)
{
  auto args = makeArgs({ "program", "-o" });
  auto opts = parseArgs(args);

  EXPECT_TRUE(opts.showLongFormat);
  EXPECT_TRUE(opts.longListOptions.showUserGroup);
  EXPECT_FALSE(opts.longListOptions.showOwnerGroup);
}

TEST(ArgumentParser, ParsesGCapitalFlagOrAlias)
{
  auto args1 = makeArgs({ "program", "-G" });
  auto args2 = makeArgs({ "program", "--no-group" });

  EXPECT_EQ(parseArgs(args1), parseArgs(args2));
}

TEST(ArgumentParser, CombinesMultipleFlags)
{
  auto args = makeArgs({ "program", "-al" });
  auto opts = parseArgs(args);

  EXPECT_TRUE(opts.showHiddenFiles);
  EXPECT_TRUE(opts.showLongFormat);
}

TEST(ArgumentParser, InvalidFlagThrows)
{
  auto args = makeArgs({ "program", "-z" });
  EXPECT_THROW(parseArgs(args), std::invalid_argument);
}

TEST(ArgumentParser, InvalidLongFlagThrows)
{
  auto args = makeArgs({ "program", "--foobar" });
  EXPECT_THROW(parseArgs(args), std::invalid_argument);
}

TEST(ArgumentParser, PreserveFlagOrder)
{
  auto firstArgs = makeArgs({ "program", "-l", "-a" });
  auto secondArgs = makeArgs({ "program", "-a", "-l" });

  EXPECT_EQ(parseArgs(firstArgs), parseArgs(secondArgs));
}

TEST(ArgumentParser, SingleCombinedFlagSet)
{
  auto args = makeArgs({ "program", "-la" });
  auto opts = parseArgs(args);

  // Both flags applied
  EXPECT_TRUE(opts.showHiddenFiles);
  EXPECT_TRUE(opts.showLongFormat);
  EXPECT_TRUE(opts.longListOptions.showUserGroup);
  EXPECT_TRUE(opts.longListOptions.showOwnerGroup);
}

TEST(ArgumentParser, CombinedFlagWithGDisablesUserGroup)
{
  auto args = makeArgs({ "program", "-lag" });// combined: l, a, g
  auto opts = parseArgs(args);

  EXPECT_TRUE(opts.showHiddenFiles);
  EXPECT_TRUE(opts.showLongFormat);
  EXPECT_FALSE(opts.longListOptions.showUserGroup);// g disables user
  EXPECT_TRUE(opts.longListOptions.showOwnerGroup);// owner still enabled
}

TEST(ArgumentParser, CombinedFlagWithODisablesOwnerGroup)
{
  auto args = makeArgs({ "program", "-lao" });// l + a + o
  auto opts = parseArgs(args);

  EXPECT_TRUE(opts.showHiddenFiles);
  EXPECT_TRUE(opts.showLongFormat);
  EXPECT_TRUE(opts.longListOptions.showUserGroup);
  EXPECT_FALSE(opts.longListOptions.showOwnerGroup);// o disables owner
}

TEST(ArgumentParser, CombinedFlagsWithCapitalGDisablesOwnerGroup)
{
  auto args = makeArgs({ "program", "-laG" });// l + a + G
  auto opts = parseArgs(args);

  EXPECT_TRUE(opts.showHiddenFiles);
  EXPECT_TRUE(opts.showLongFormat);
  EXPECT_TRUE(opts.longListOptions.showUserGroup);
  EXPECT_FALSE(opts.longListOptions.showOwnerGroup);// G disables owner
}

TEST(ArgumentParser, CombinedFlagsWithDuplicateLetters)
{
  auto args = makeArgs({ "program", "-lla" });// repeated 'l'
  auto opts = parseArgs(args);

  // Repeated flags should not break logic
  EXPECT_TRUE(opts.showHiddenFiles);
  EXPECT_TRUE(opts.showLongFormat);
  EXPECT_TRUE(opts.longListOptions.showUserGroup);
  EXPECT_TRUE(opts.longListOptions.showOwnerGroup);
}

TEST(ArgumentParser, CombinedFlagsWithInvalidLetterThrows)
{
  auto args = makeArgs({ "program", "-laz" });// 'z' invalid
  EXPECT_THROW(parseArgs(args), std::invalid_argument);
}

TEST(ArgumentParser, CombinedShortAndLongFlags)
{
  auto args = makeArgs({ "program", "-la", "--no-group" });
  auto opts = parseArgs(args);

  EXPECT_TRUE(opts.showHiddenFiles);
  EXPECT_TRUE(opts.showLongFormat);
  EXPECT_TRUE(opts.longListOptions.showUserGroup);
  EXPECT_FALSE(opts.longListOptions.showOwnerGroup);// disabled by --no-group
}

TEST(ArgumentParser, AllFlagsCombined)
{
  auto args = makeArgs({ "program", "-laGo" });// l, a, G, o
  auto opts = parseArgs(args);

  EXPECT_TRUE(opts.showHiddenFiles);
  EXPECT_TRUE(opts.showLongFormat);

  // G disables owner, o disables owner — still disabled
  EXPECT_TRUE(opts.longListOptions.showUserGroup);
  EXPECT_FALSE(opts.longListOptions.showOwnerGroup);
}


}// namespace
