#include "argumentParser.h"
#include "lsCore.h"
#include <cstddef>

int main(int args, const char* argv[])
{
  const UserOptions options = parseArgs({ argv, static_cast<size_t>(args) });
  const LsCore program{ options };
  program.SetOutput();

  return 0;
}
