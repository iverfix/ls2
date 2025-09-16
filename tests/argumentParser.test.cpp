#include "argumentParser.h"
#include <gtest/gtest.h>


namespace {

  TEST(ArgumentParser, NoArguments){
    
    UserOptions options = parseArgs(0, nullptr);

    EXPECT_EQ(options, UserOptions());
  }

  TEST(ArgumentParser, SingleArgument) {
    const char* argumentList[] = { "program" };
    UserOptions options = parseArgs(1, argumentList);

    EXPECT_EQ(options, UserOptions());
  }

  TEST(ArgumentParser, AFlag) {
    const char* validArguments[] = { "program.a", "-a" };
    const char* validExtendedArguments[] = { "program.a", "--all" };

    UserOptions options = parseArgs(2, validArguments);
    UserOptions optionsExtended = parseArgs(2, validExtendedArguments);

    EXPECT_EQ(options, optionsExtended);
  }

  TEST(ArgumentParser, InvalidArgument) {
    const char* invalidArgument[] = { "program.a", "kake" };
    
    EXPECT_THROW(parseArgs(2, invalidArgument), std::runtime_error);
    
  }

}
