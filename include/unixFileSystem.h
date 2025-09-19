#include <string>
#include "filesystem.h"


class UnixFileSystem: public IFileSystem {

public:
  std::string getFileUser(const char* filename);
  std::string getFileGroup(const char* filename);
  int getFileSize(const char* filename);

};
