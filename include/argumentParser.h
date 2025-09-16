#pragma once
#include <string>

struct UserOptions {
  bool showHiddenFiles = false;
  std::string path = "";

  bool operator==(const UserOptions&) const = default;
};

UserOptions parseArgs(int argc, const char* argv[]);
