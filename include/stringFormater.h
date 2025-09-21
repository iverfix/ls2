#pragma once
#include <string>
#include <filesystem>


class StringFormater
{

enum class FileType { Directory, Executable, Symlink, RegularFile };

public:
  std::string colorFileType(const std::filesystem::directory_entry& dirEntry) const;
  FileType getFileType(const std::filesystem::directory_entry& dirEntry) const;

private:
  constexpr std::string_view fileTypeColor(FileType fileType) const;
};
