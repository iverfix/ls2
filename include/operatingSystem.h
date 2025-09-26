#pragma once
#include <string>


class IOperatingSystem
{
public:
  virtual ~IOperatingSystem() = default;
  IOperatingSystem() = delete;
  IOperatingSystem(const IOperatingSystem&) = delete;
  IOperatingSystem& operator=(const IOperatingSystem&) = delete;
  IOperatingSystem(IOperatingSystem&&) = delete;
  IOperatingSystem& operator=(IOperatingSystem&&) = delete;

  virtual std::string getFileUser(const char* filename) const = 0;
  virtual std::string getFileGroup(const char* filename) const = 0;
};
