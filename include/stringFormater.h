#pragma once
#include <string>
#include <filesystem>


class StringFormater
{

enum class FileType { Directory, Executable, Symlink, RegularFile };

public:
  std::string colorFileType(const std::filesystem::directory_entry& dirEntry);
  FileType getFileType(const std::filesystem::directory_entry& dirEntry);

private:
  constexpr std::string_view fileTypeColor(FileType fileType);
};
