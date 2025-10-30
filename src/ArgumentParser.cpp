#include "ArgumentParser.h"
#include <ranges>
#include <span>
#include <stdexcept>
#include <unordered_set>
#include <vector>

std::vector<std::string> extractFeatureFlags(std::span<const char*> args) {

  // The map is necessary to perserve ordering later, regardless of user input
  static const std::vector<std::string> flagOrder{"l", "a", "all", "g", "o", "G", "no-group"};
  std::unordered_set<std::string> enabledFlags{};

  for (const std::string& arg : args.subspan(1)) {
    if (arg.starts_with("--")) {
      enabledFlags.emplace(arg.substr(2));
    } else {
      for (const char flag : arg.substr(1)) {
        enabledFlags.emplace(1, flag);
      }
    }
  } 

  return flagOrder | std::ranges::views::filter([&enabledFlags](const std::string& flag) { return enabledFlags.contains(flag);}) | std::ranges::to<std::vector<std::string>>();
}

UserOptions parseArgs(std::span<const char*> args)
{

  if (args.empty()) { throw std::invalid_argument("At least one argument is expected"); }

  UserOptions opts{};

  for (const auto& arg : extractFeatureFlags(args)) {

    if (arg == "a" || arg == "all") {
      opts.showHiddenFiles = true;
    } else if (arg == "l") {
      opts.showLongFormat = true;
      opts.longListOptions.showFilename = true;
      opts.longListOptions.showOwnerGroup = true;
      opts.longListOptions.showUserGroup = true;
      opts.longListOptions.showPermissionString = true;
      opts.longListOptions.showBytesize = true;
      opts.longListOptions.showWriteTime = true;
      opts.longListOptions.showNumHardLinks = true;
    } else if (arg == "g") {
      opts.showLongFormat = true;
      opts.longListOptions.showFilename = true;
      opts.longListOptions.showOwnerGroup = true;
      opts.longListOptions.showUserGroup = false;
      opts.longListOptions.showPermissionString = true;
      opts.longListOptions.showBytesize = true;
      opts.longListOptions.showWriteTime = true;
      opts.longListOptions.showNumHardLinks = true;
    } else if (arg == "o") {
      opts.showLongFormat = true;
      opts.longListOptions.showFilename = true;
      opts.longListOptions.showOwnerGroup = false;
      opts.longListOptions.showUserGroup = true;
      opts.longListOptions.showPermissionString = true;
      opts.longListOptions.showBytesize = true;
      opts.longListOptions.showWriteTime = true;
      opts.longListOptions.showNumHardLinks = true;
    } else if (arg == "G" || arg == "no-group") {
      opts.longListOptions.showOwnerGroup = false;
    } else {
      throw std::invalid_argument("Invalid input parameter");
    }
  }
  return opts;
}
