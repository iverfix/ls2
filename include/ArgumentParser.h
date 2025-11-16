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

  static LongListFormatOptions enableAllLongListOptions()
  {
    return { .showFilename = true, .showOwnerGroup = true, .showUserGroup = true, .showPermissionString = true, .showBytesize = true, .showWriteTime = true };
  }

  bool operator==(const LongListFormatOptions& opts) const = default;
};

struct UserOptions
{
  bool showHiddenFiles = false;
  bool showLongFormat = false;
  std::string path;
  LongListFormatOptions longListOptions{};

  bool operator==(const UserOptions& opts) const = default;
};

UserOptions parseArgs(std::span<const char*> args);
