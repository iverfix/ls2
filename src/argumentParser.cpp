#include "argumentParser.h"
#include <stdexcept>
#include <string_view>
#include <span>


UserOptions parseArgs(int argc, const char* argv[]){
  
  if (argc < 1) throw std::invalid_argument("At least one argument is expected");
  UserOptions opts{};
 

  for (const std::string_view arg : std::span{argv + 1, static_cast<size_t>(argc -1)}) {
    if (arg == "-a" || arg == "--all")
      opts.showHiddenFiles = true;
    else
      throw std::runtime_error("Invalid input parameter");
  }
  return opts;
}
