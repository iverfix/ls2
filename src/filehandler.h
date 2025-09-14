#include "stringFormater.h"
#include <string>
#include <vector>

class FileHandler
{

public:
  std::vector<std::string> getFileList();

private:
  StringFormater stringFormater{};
};
