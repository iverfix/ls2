#pragma once
#include <string>

struct UserOptions
{
  bool showHiddenFiles = false;
  std::string path = "";
};

UserOptions parseArgs(int argc, const char* argv[]);
