#pragma once
#include <string>


class IOperatingSystem
{

public:
  virtual std::string getFileUser(const char* filename) const = 0;
  virtual std::string getFileGroup(const char* filename) const = 0;
  virtual int getFileSize() const = 0;
};
