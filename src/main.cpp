#include "filehandler.h"
#include <iostream>

int main()
{
  FileHandler fh{};
  std::vector<std::string> files = fh.getFileList();

  for (const auto& file : files) { std::cout << file << std::endl; }

  return 0;
}
