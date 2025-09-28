#include "argumentParser.h"
#include <cstddef>
#include <span>
#include <stdexcept>
#include <string_view>

UserOptions parseArgs(int argc, const char* argv[])
{

  if (argc < 1) { throw std::invalid_argument("At least one argument is expected"); }
  UserOptions opts{};


  for (const std::string_view arg : std::span{ argv, static_cast<size_t>(argc) }.subspan(1)) {
    if (arg == "-a" || arg == "--all") {
      opts.showHiddenFiles = true;
    } else if (arg == "-l") {
      opts.showLongFormat = true;
    } else {
      throw std::runtime_error("Invalid input parameter");
    }
  }
  return opts;
}
