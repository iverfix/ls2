#include "ArgumentParser.h"
#include <functional>
#include <ranges>
#include <span>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>


void flag_a (UserOptions& options) {
  options.showHiddenFiles = true;
}

void flag_l (UserOptions& options) {
  options.showLongFormat = true;
  options.longListOptions = LongListFormatOptions::enableAllLongListOptions();
}

void flag_g (UserOptions& options) {
  options.showLongFormat = true;
  options.longListOptions = LongListFormatOptions::enableAllLongListOptions();
  options.longListOptions.showUserGroup = false;
}

void flag_o (UserOptions& options) {
  options.showLongFormat = true;
  options.longListOptions = LongListFormatOptions::enableAllLongListOptions();
  options.longListOptions.showOwnerGroup = false;
}

void flag_G (UserOptions& options) {
  options.longListOptions.showOwnerGroup = false;
}


 std::unordered_map<std::string, std::function<void(UserOptions&)>> getFlagActions(){

  const static std::unordered_map<std::string, std::function<void(UserOptions&)>> flagActions {
    {"a", flag_a},
    {"all", flag_a},
    {"l", flag_l},
    {"g", flag_g},
    {"o", flag_o},
    {"G", flag_G},
    {"no-group", flag_G}
  };
  return flagActions;

}


std::vector<std::string> extractFeatureFlags(std::span<const char*> args) {

  // The map is necessary to perserve ordering later, regardless of user input
  static constexpr std::array<std::string, 7> flagOrder{"l", "a", "all", "g", "o", "G", "no-group"};
  const std::unordered_set<std::string> allowedFlags{flagOrder.begin(), flagOrder.end()};
  
  std::unordered_set<std::string> enabledFlags{};

  for (const std::string& arg : args.subspan(1)) {
    if (arg.starts_with("--")) {
      if (!allowedFlags.contains(arg.substr(2))){
        throw std::invalid_argument("Invalid flag: " + arg);
      }
      enabledFlags.emplace(arg.substr(2));
    } else {
      for (const char flag : arg.substr(1)) {
        if (!allowedFlags.contains(std::string(1, flag))){
          throw std::invalid_argument("Invalid flag: " + std::string{flag});
        }
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
  auto flagActions = getFlagActions();

  for (const auto& arg : extractFeatureFlags(args)) {
    flagActions[arg](opts);
  }
  return opts;
}
