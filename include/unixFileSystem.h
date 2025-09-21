#pragma once
#include <string>
#include "filesystem.h"


class UnixFileSystem: public IFileSystem {

public:
  std::string getFileUser(const char* filename) const;
  std::string getFileGroup(const char* filename) const;
  int getFileSize(const char* filename) const;


};
