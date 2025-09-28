#pragma once
#include <span>
#include <string>

struct UserOptions
{
  bool showHiddenFiles = false;
  bool showLongFormat = false;
  std::string path;
};

UserOptions parseArgs(std::span<const char*> args);
