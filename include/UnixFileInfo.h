#pragma once
#include "OsFileInfo.h"
#include <filesystem>
#include <optional>
#include <string>
#include <sys/types.h>

class UnixFileInfo : public IOperatingSystem
{
public:
  explicit UnixFileInfo(const std::filesystem::directory_entry& entry);
  [[nodiscard]] std::string getFileOwner() const override { return fileOwner.value_or(""); }
  [[nodiscard]] std::string getFileOwnerGroup() const override { return fileOwnerGroup.value_or(""); }
  [[nodiscard]] long getNumHardLinks() const override { return numHardLinks; }
  [[nodiscard]] std::string getPermissionString() const override { return permissionString; }

private:
  static std::optional<std::string> fetchFileOwner(uid_t uid);
  static std::optional<std::string> fetchFileOwnerGroup(gid_t gid);
  static std::string fetchPermissionString(const std::filesystem::directory_entry& entry);

  static constexpr int DEFAULT_BUFFER_SIZE{ 16384 };
  long numHardLinks{ 0 };
  std::optional<std::string> fileOwner{ std::nullopt };
  std::optional<std::string> fileOwnerGroup{ std::nullopt };
  std::string permissionString;
};
