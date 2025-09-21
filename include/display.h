#pragma once
#include "argumentParser.h"
#include "filehandler.h"
#include "stringFormater.h"
#include "unixOperatingSystem.h"

class Display
{

public:
  explicit Display(UserOptions options) : fileHandler(FileHandler(std::move(options))){};
  void generatePermissionFileList();
  void generateBalancedGrid();

private:
  int columnPadding{ 2 };
  FileHandler fileHandler;
  UnixOperatingSystem fileSystem{};
  StringFormater stringFormater{};
};
