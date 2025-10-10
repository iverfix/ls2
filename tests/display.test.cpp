#include "display.h"
#include "entry.h"
#include "mocks/MockFileHandler.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

TEST(DisplayTest, HandleEmptyDirectoryGracefully)
{


  auto fileHandler = std::make_shared<MockFileHandler>();
  EXPECT_CALL(*fileHandler, getFolderContent()).WillOnce(testing::Return(std::vector<Entry>{}));


  const Display display(fileHandler);


  const std::stringstream output;
  std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

  display.generateBalancedGrid();

  std::cout.rdbuf(oldCout);

  EXPECT_TRUE(output.str().empty());
}
