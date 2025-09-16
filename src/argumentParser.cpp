#include "argumentParser.h"
#include "vector"
#include "string_view"


UserOptions parseArgs(int argc, const char* argv[]){
  
  UserOptions opts{};
  std::vector<std::string_view> args(argv + 1, argv + argc);
 
  for (auto it = args.begin(); it != args.end(); ++it) {
    if (*it == "-l")
      opts.showHiddenFiles = true;
  }
  return opts;
}
