#include "argumentParser.h"
#include <stdexcept>
#include <string_view>
#include <span>


UserOptions parseArgs(int argc, const char* argv[]){
  
  UserOptions opts{};
 
  for (const std::string_view arg : std::span{argv + 1, static_cast<size_t>(argc -1)}) {
    if (arg == "-a")
      opts.showHiddenFiles = true;
    else
      throw std::runtime_error("Invalid input parameter");
  }
  return opts;
}
