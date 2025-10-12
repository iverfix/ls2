#pragma once
#include "Entry.h"
#include <format>
#include <string>
#include <string_view>

class StringFormater
{

public:
  [[nodiscard]] static std::string colorFileType(const Entry& dirEntry) { return std::format("\033[{}m{}\033[0m", fileTypeColor(dirEntry), dirEntry.entryName); }


private:
  static constexpr std::string_view DirectoryColor{ "1;34" };
  static constexpr std::string_view ExecutableColor{ "1;32" };
  static constexpr std::string_view SymlinkColor{ "1;36" };
  static constexpr std::string_view RegularColor{ "0" };


  [[nodiscard]] static constexpr std::string_view fileTypeColor(const Entry& entry)
  {

    switch (entry.type) {
    case EntryType::Directory:
      return DirectoryColor;
    case EntryType::Executable:
      return ExecutableColor;
    case EntryType::Symlink:
      return SymlinkColor;
    default:
      return RegularColor;
    }
  }
};
