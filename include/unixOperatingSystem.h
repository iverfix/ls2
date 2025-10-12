#pragma once
#include "operatingSystem.h"
#include <optional>
#include <string>


class UnixOperatingSystem : public IOperatingSystem
{
public:
  explicit UnixOperatingSystem(const char* filename);
  [[nodiscard]] std::string getFileOwner() const override { return fileOwner.value_or(""); };
  [[nodiscard]] std::string getFileOwnerGroup() const override { return fileOwnerGroup.value_or(""); };
  [[nodiscard]] long getNumHardLinks() const override { return numHardLinks; };

private:
  static std::optional<std::string> fetchFileOwner(uid_t uid);
  static std::optional<std::string> fetchFileOwnerGroup(gid_t gid);

  static constexpr int DEFAULT_BUFFER_SIZE{ 16384 };
  long numHardLinks{ 0 };
  std::optional<std::string> fileOwner;
  std::optional<std::string> fileOwnerGroup;
};
