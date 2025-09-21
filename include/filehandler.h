#pragma once
#include "stringFormater.h"
#include <argumentParser.h>
#include <vector>

class FileHandler
{

public:
  explicit FileHandler(UserOptions options) : options(options) {}
  std::vector<std::filesystem::directory_entry> getFileList() const;

private:
  const int columnPadding{2};
  StringFormater stringFormater{};
  UserOptions options{};
};
