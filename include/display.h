#pragma once
#include "argumentParser.h"
#include "filehandler.h"
#include "stringFormater.h"
#include "unixOperatingSystem.h"

class Display
{

public:
  explicit Display(UserOptions options) : fileHandler(FileHandler(options)){};
  void generatePermissionFileList();
  void generateBalancedGrid();

private:
  const int columnPadding{ 2 };
  const FileHandler fileHandler;
  const UnixOperatingSystem fileSystem{};
  const StringFormater stringFormater{};
};
