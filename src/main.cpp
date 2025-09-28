#include "argumentParser.h"
#include "lsCore.h"

int main(int args, const char* argv[])
{
  const UserOptions options = parseArgs(args, argv);
  LsCore program{ options };
  program.SetOutput();

  return 0;
}
