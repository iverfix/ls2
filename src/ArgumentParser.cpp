#include "ArgumentParser.h"
#include <span>
#include <stdexcept>
#include <string_view>

UserOptions parseArgs(std::span<const char*> args)
{

  if (args.empty()) { throw std::invalid_argument("At least one argument is expected"); }

  UserOptions opts{};


  for (const std::string_view arg : args.subspan(1)) {
    if (arg == "-a" || arg == "--all") {
      opts.showHiddenFiles = true;
    } else if (arg == "-l") {
      opts.showLongFormat = true;
      opts.longListOptions.showFilename = true;
      opts.longListOptions.showOwnerGroup = true;
      opts.longListOptions.showUserGroup = true;
      opts.longListOptions.showPermissionString = true;
      opts.longListOptions.showBytesize = true;
      opts.longListOptions.showWriteTime = true;
      opts.longListOptions.showNumHardLinks = true;
    } else if (arg == "-g") {
      opts.showLongFormat = true;
      opts.longListOptions.showFilename = true;
      opts.longListOptions.showOwnerGroup = true;
      opts.longListOptions.showUserGroup = false;
      opts.longListOptions.showPermissionString = true;
      opts.longListOptions.showBytesize = true;
      opts.longListOptions.showWriteTime = true;
      opts.longListOptions.showNumHardLinks = true;
    } else if (arg == "-o") {
      opts.showLongFormat = true;
      opts.longListOptions.showFilename = true;
      opts.longListOptions.showOwnerGroup = false;
      opts.longListOptions.showUserGroup = true;
      opts.longListOptions.showPermissionString = true;
      opts.longListOptions.showBytesize = true;
      opts.longListOptions.showWriteTime = true;
      opts.longListOptions.showNumHardLinks = true;
    } else if (arg == "-G" || arg == "--no-group") {
      opts.longListOptions.showOwnerGroup = false;
    } else {
      throw std::invalid_argument("Invalid input parameter");
    }
  }
  return opts;
}
