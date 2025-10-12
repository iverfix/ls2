#pragma once
#include <string>


class IOperatingSystem
{
public:
  virtual ~IOperatingSystem() = default;

  IOperatingSystem() = default;
  IOperatingSystem(const IOperatingSystem&) = default;
  IOperatingSystem& operator=(const IOperatingSystem&) = default;
  IOperatingSystem(IOperatingSystem&&) = default;
  IOperatingSystem& operator=(IOperatingSystem&&) = default;

  virtual std::string getFileUser(const char* filename) const = 0;
  virtual std::string getFileGroup(const char* filename) const = 0;
  virtual long getNumHardLinks(const char* filename) const = 0;
};
