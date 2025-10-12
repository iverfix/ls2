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

  [[nodiscard]] virtual std::string getFileOwner() const = 0;
  [[nodiscard]] virtual std::string getFileOwnerGroup() const = 0;
  [[nodiscard]] virtual long getNumHardLinks() const = 0;
};
