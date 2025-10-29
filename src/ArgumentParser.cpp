#include "ArgumentParser.h"
#include <span>
#include <stdexcept>
#include <string_view>
#include <map>
#include <vector>
#include <ranges>


std::vector<std::string> extractFeatureFlags(std::span<const char*> args) {

  // The map is necessary to perserve ordering later, regardless of user input
  std::map<std::string, bool> enabledFeatureFlags{
    {"a", false},
    {"g", false},
    {"l", false},
    {"o", false},
    {"G", false}
  };

  for (const std::string_view arg : args.subspan(1)) {
    if (arg.starts_with("--")) {

    } else {
      for (const char flag : arg.substr(1)) {
        enabledFeatureFlags[std::string(1, flag)] = true;
      }
    }

  } 

  auto view = enabledFeatureFlags | std::views::filter([](const auto& pair) { return pair.second; }) | std::views::transform([](const auto& pair) { return pair.first; });
  return {view.begin(), view.end()};
}

UserOptions parseArgs(std::span<const char*> args)
{

  if (args.empty()) { throw std::invalid_argument("At least one argument is expected"); }

  UserOptions opts{};

  /*
  * 1. Create a vector of pairs with true false flags set
  * 2. Extract all letters or flags from the input
  * 3. Filter through the entire object for true values
  * 4. Build UserOptions from the filtered vector of pairs
  * 5. Switch-case on selection to make it instant and perserve evaluation ordering
  */


  for (const auto& arg : extractFeatureFlags(args)) {
    if (arg == "a" || arg == "--all") {
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
    } else if (arg == "G" || arg == "--no-group") {
      opts.longListOptions.showOwnerGroup = false;
    } else {
      throw std::invalid_argument("Invalid input parameter");
    }
  }
  return opts;
}
