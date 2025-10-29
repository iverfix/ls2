#pragma once
#include <span>
#include <string>

struct LongListFormatOptions 
{
  bool showFilename = false;
  bool showOwnerGroup = false;
  bool showUserGroup = false;
  bool showPermissionString = false;
  bool showBytesize = false;
  bool showWriteTime = false;
  bool showNumHardLinks = false;
};

struct UserOptions
{
  bool showHiddenFiles = false;
  bool showLongFormat = false;
  std::string path;
  LongListFormatOptions longListOptions{};
};

UserOptions parseArgs(std::span<const char*> args);
