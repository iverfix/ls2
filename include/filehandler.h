#pragma once
#include "stringFormater.h"
#include <argumentParser.h>
#include <vector>

class FileHandler
{

public:
  explicit FileHandler(UserOptions options) : options(std::move(options)) {}
  [[nodiscard]] std::vector<std::filesystem::directory_entry> getFileList() const;

private:
  static constexpr int columnPadding{ 2 };
  StringFormater stringFormater{};
  UserOptions options{};
};
