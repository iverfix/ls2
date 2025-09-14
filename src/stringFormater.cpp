#include "stringFormater.h"
#include <algorithm>
#include <format>
#include <string>
#include <string_view>
#include <filesystem>

constexpr inline std::string_view DirectoryColor{ "1;34" };
constexpr inline std::string_view ExecutableColor{ "1;32" };
constexpr inline std::string_view SymlinkColor{ "1;36" };
constexpr std::string_view RegularColor{ "0" };


constexpr std::string_view StringFormater::fileTypeColor(FileType fileType) {

  switch (fileType) {
    case StringFormater::FileType::Directory: return DirectoryColor;
    case StringFormater::FileType::Executable: return ExecutableColor;
    case StringFormater::FileType::Symlink: return SymlinkColor;
    default: return RegularColor;
  }
}



std::string StringFormater::prunePathString(std::string inputString)
{
  auto it = std::find_if(inputString.begin(), inputString.end(), [](unsigned char c) { return std::isalnum(c); });

  return (it != inputString.end()) ? std::string(it, inputString.end()) : "";
}


std::string StringFormater::colorFileType(const std::string& filename, const std::filesystem::directory_entry& dirEntry){
  FileType fileType = getFileType(dirEntry);

  return std::format("\033[{}m{}\033[0m", fileTypeColor(fileType), filename); }


StringFormater::FileType StringFormater::getFileType(const std::filesystem::directory_entry& dirEntry)
{
  if (dirEntry.is_directory()) {
    return FileType::Directory;
  } else if (dirEntry.is_symlink()) {
    return FileType::Symlink;
  } else {
    std::filesystem::perms p = dirEntry.status().permissions();

    // Check if any of the execution properties are enabled
    if ((p & std::filesystem::perms::owner_exec) != std::filesystem::perms::none || (p & std::filesystem::perms::group_exec) != std::filesystem::perms::none
        || (p & std::filesystem::perms::others_exec) != std::filesystem::perms::none) {
      return FileType::Executable;
    } else {
      return FileType::RegularFile;// fallback
    }
  }
}
