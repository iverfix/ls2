#pragma once
#include "argumentParser.h"
#include "filehandler.h"
#include "stringFormater.h"
#include "unixFileSystem.h"

class Display {

public:
  explicit Display(UserOptions options) : fileHandler(FileHandler(options)){};
  void generatePermissionFileList();
  void generateBalancedGrid();
private:
  const int columnPadding{2};
  const FileHandler fileHandler;
  const UnixFileSystem fileSystem{};
  const StringFormater stringFormater{};
};
