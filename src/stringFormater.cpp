#include "stringFormater.h"
#include <filesystem>
#include <format>
#include <string>
#include <string_view>

constexpr inline std::string_view DirectoryColor{ "1;34" };
constexpr inline std::string_view ExecutableColor{ "1;32" };
constexpr inline std::string_view SymlinkColor{ "1;36" };
constexpr std::string_view RegularColor{ "0" };


constexpr std::string_view StringFormater::fileTypeColor(FileType fileType) const
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

std::string StringFormater::colorFileType(const std::filesystem::directory_entry& dirEntry) const
{
  const FileType fileType = getFileType(dirEntry);

  return std::format("\033[{}m{}\033[0m", fileTypeColor(fileType), dirEntry.path().lexically_normal().string());
}


StringFormater::FileType StringFormater::getFileType(const std::filesystem::directory_entry& dirEntry) const
{
  if (dirEntry.is_directory()) {
    return FileType::Directory;
  } else if (dirEntry.is_symlink()) {
    return FileType::Symlink;
  } else {
    std::filesystem::perms permissions = dirEntry.status().permissions();

    // Check if any of the execution properties are enabled
    if ((permissions & std::filesystem::perms::owner_exec) != std::filesystem::perms::none || (permissions & std::filesystem::perms::group_exec) != std::filesystem::perms::none
        || (permissions & std::filesystem::perms::others_exec) != std::filesystem::perms::none) {
      return FileType::Executable;
    } else {
      return FileType::RegularFile;// fallback
    }
  }
}
