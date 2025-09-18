#include "filehandler.h"
#include "argumentParser.h"

int main(int args, const char* argv[])
{
  UserOptions options = parseArgs(args, argv);

  FileHandler fh{options};

  fh.generatePermissionFileList();

  //fh.generateBalancedGrid();

  return 0;
}
