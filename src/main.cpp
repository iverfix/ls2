#include "argumentParser.h"
#include "display.h"

int main(int args, const char* argv[])
{
  UserOptions options = parseArgs(args, argv);
  Display display{options};
  display.generatePermissionFileList();

  //display.generateBalancedGrid();

  return 0;
}
