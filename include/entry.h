#pragma once
#include <cstdint>
#include <string>


enum class EntryType : std::uint8_t { Directory, Executable, Symlink, RegularFile };

struct Entry
{
  std::string entryName;
  std::string entryGroup;
  std::string userGroup;
  uintmax_t bytesize;
  int lastWriteTime;
  EntryType type;
};
