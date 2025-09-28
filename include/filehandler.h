#pragma once
#include "entry.h"
#include "stringFormater.h"
#include <argumentParser.h>
#include <filesystem>
#include <unixOperatingSystem.h>
#include <utility>
#include <vector>


class FileHandler
{

public:
  explicit FileHandler(UserOptions options) : options(std::move(options)) {}
  [[nodiscard]] std::vector<Entry> getFolderContent() const;

private:
  static constexpr int columnPadding{ 2 };
  StringFormater stringFormater{};
  UserOptions options{};
  UnixOperatingSystem fileSystem{};
  [[nodiscard]] static EntryType getFileType(const std::filesystem::directory_entry& dirEntry)
  {
    if (dirEntry.is_directory()) {
      return EntryType::Directory;
    } else if (dirEntry.is_symlink()) {
      return EntryType::Symlink;
    } else {
      std::filesystem::perms const permissions = dirEntry.status().permissions();

      // Check if any of the execution properties are enabled
      if ((permissions & std::filesystem::perms::owner_exec) != std::filesystem::perms::none || (permissions & std::filesystem::perms::group_exec) != std::filesystem::perms::none
          || (permissions & std::filesystem::perms::others_exec) != std::filesystem::perms::none) {
        return EntryType::Executable;
      } else {
        return EntryType::RegularFile;// fallback
      }
    }
  }
};
