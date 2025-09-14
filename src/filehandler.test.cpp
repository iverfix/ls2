#include "filehandler.h"
#include <gtest/gtest.h>


namespace {

TEST(Equality, Equal) { ASSERT_EQ(1, 1); }

TEST(FileHandler, Formatting) { FileHandler fh{}; }

}// namespace
