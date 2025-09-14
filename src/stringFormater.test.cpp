#include "stringFormater.h"
#include <gtest/gtest.h>

namespace {
TEST(StringFormater, PathFormatEmptyString)
{
  StringFormater sf{};
  ASSERT_EQ(sf.formatPathString(""), "");
}


TEST(StringFormater, PathFormatInvalidString)
{
  StringFormater sf{};
  ASSERT_EQ(sf.formatPathString("./"), "");
}


TEST(StringFormater, PathFormatFileString)
{
  StringFormater sf{};
  ASSERT_EQ(sf.formatPathString("./dataType.txt"), "dataType.txt");
}
}// namespace
