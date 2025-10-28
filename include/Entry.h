#pragma once
#include <chrono>
#include <cstdint>
#include <string>


enum class EntryType : std::uint8_t { Directory, Executable, Symlink, RegularFile };

struct Entry
{
  std::string entryName;
  std::string entryGroup;
  std::string userGroup;
  std::string permissionString;
  uintmax_t bytesize;
  std::chrono::time_point<std::chrono::system_clock> lastWriteTime;
  EntryType type;
  long numHardLinks;
};
