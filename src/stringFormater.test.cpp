#include "stringFormater.h"
#include <gtest/gtest.h>

namespace {
TEST(StringFormater, PathFormatEmptyString)
{
  StringFormater sf{};
  ASSERT_EQ(sf.prunePathString(""), "");
}


TEST(StringFormater, PathFormatInvalidString)
{
  StringFormater sf{};
  ASSERT_EQ(sf.prunePathString("./"), "");
}


TEST(StringFormater, PathFormatFileString)
{
  StringFormater sf{};
  ASSERT_EQ(sf.prunePathString("./dataType.txt"), "dataType.txt");
}
}// namespace
