#include "stringFormater.h"
#include <argumentParser.h>
#include <vector>

class FileHandler
{

public:
  FileHandler(UserOptions options);
  std::vector<std::filesystem::directory_entry> getFileList();
  void generatePermissionFileList();
  void generateBalancedGrid();

private:
  const int columnPadding{2};
  StringFormater stringFormater{};
  UserOptions options{};
};
