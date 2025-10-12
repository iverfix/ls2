#pragma once
#include "operatingSystem.h"
#include <string>


class UnixOperatingSystem : public IOperatingSystem
{
public:
  std::string getFileUser(const char* filename) const override;
  std::string getFileGroup(const char* filename) const override;
  long getNumHardLinks(const char* filename) const override;
};
