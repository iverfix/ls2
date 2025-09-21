#pragma once
#include "operatingSystem.h"
#include <string>


class UnixOperatingSystem : public IOperatingSystem
{

public:
  std::string getFileUser(const char* filename) const;
  std::string getFileGroup(const char* filename) const;
  int getFileSize(const char* filename) const;
};
