#include "display.h"
#include "mocks/MockFileHandler.h"
#include <gtest/gtest.h>
#include <memory>


TEST(DisplayTest, HandleEmptyDirectoryGracefully)
{


  auto fileHandler = std::make_shared<MockFileHandler>();
  EXPECT_CALL(*fileHandler, getFolderContent()).WillOnce(testing::Return(std::vector<Entry>{}));


  Display display(fileHandler);


  std::stringstream output;
  std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

  display.generateBalancedGrid();

  std::cout.rdbuf(oldCout);

  EXPECT_TRUE(output.str().empty());
}
