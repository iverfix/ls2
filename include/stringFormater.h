#pragma once
#include <cstdint>
#include <filesystem>
#include <format>
#include <string>
#include <string_view>


class StringFormater
{

  enum class FileType : std::uint8_t { Directory, Executable, Symlink, RegularFile };

public:
  [[nodiscard]] static FileType getFileType(const std::filesystem::directory_entry& dirEntry)
  {
    if (dirEntry.is_directory()) {
      return FileType::Directory;
    } else if (dirEntry.is_symlink()) {
      return FileType::Symlink;
    } else {
      std::filesystem::perms const permissions = dirEntry.status().permissions();

      // Check if any of the execution properties are enabled
      if ((permissions & std::filesystem::perms::owner_exec) != std::filesystem::perms::none || (permissions & std::filesystem::perms::group_exec) != std::filesystem::perms::none
          || (permissions & std::filesystem::perms::others_exec) != std::filesystem::perms::none) {
        return FileType::Executable;
      } else {
        return FileType::RegularFile;// fallback
      }
    }
  }

  [[nodiscard]] static std::string colorFileType(const std::filesystem::directory_entry& dirEntry)
  {
    const FileType fileType = getFileType(dirEntry);

    return std::format("\033[{}m{}\033[0m", fileTypeColor(fileType), dirEntry.path().lexically_normal().string());
  }


private:
  static constexpr std::string_view DirectoryColor{ "1;34" };
  static constexpr std::string_view ExecutableColor{ "1;32" };
  static constexpr std::string_view SymlinkColor{ "1;36" };
  static constexpr std::string_view RegularColor{ "0" };


  [[nodiscard]] static constexpr std::string_view fileTypeColor(FileType fileType)
  {

    switch (fileType) {
    case StringFormater::FileType::Directory:
      return DirectoryColor;
    case StringFormater::FileType::Executable:
      return ExecutableColor;
    case StringFormater::FileType::Symlink:
      return SymlinkColor;
    default:
      return RegularColor;
    }
  }
};
