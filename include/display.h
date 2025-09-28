#pragma once
#include "argumentParser.h"
#include "filehandler.h"
#include "stringFormater.h"
#include "unixOperatingSystem.h"
#include <utility>
class Display
{

public:
  explicit Display(UserOptions options) : fileHandler(FileHandler(std::move(options))) {};
  void generatePermissionFileList() const;
  void generateBalancedGrid() const;

private:
  int columnPadding{ 2 };
  FileHandler fileHandler;
  UnixOperatingSystem fileSystem{};
  StringFormater stringFormater{};
};
