#pragma once
#include <cstdint>
#include <filesystem>
#include <string>
#include <string_view>


class StringFormater
{

  enum class FileType : std::uint8_t { Directory, Executable, Symlink, RegularFile };

public:
  [[nodiscard]] std::string colorFileType(const std::filesystem::directory_entry& dirEntry) const;
  [[nodiscard]] FileType getFileType(const std::filesystem::directory_entry& dirEntry) const;

private:
  [[nodiscard]] constexpr std::string_view fileTypeColor(FileType fileType) const;
};
