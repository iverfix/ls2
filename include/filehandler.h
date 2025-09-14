#include "stringFormater.h"
#include <vector>

class FileHandler
{

public:
  std::vector<std::filesystem::directory_entry> getFileList();
  void generateBalancedGrid();

private:
  const int columnPadding{3};
  StringFormater stringFormater{};
};
