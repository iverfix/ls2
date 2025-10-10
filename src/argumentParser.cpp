#include "argumentParser.h"
#include <span>
#include <stdexcept>
#include <string_view>

UserOptions parseArgs(std::span<const char*> args) {

  if (args.empty()) { throw std::invalid_argument("At least one argument is expected"); }

  UserOptions opts{};


  for (const std::string_view arg : args.subspan(1)) {
    if (arg == "-a" || arg == "--all") {
      opts.showHiddenFiles = true;
    } else if (arg == "-l") {
      opts.showLongFormat = true;
    } else {
      throw std::invalid_argument("Invalid input parameter");
    }
  }
  return opts;
}
