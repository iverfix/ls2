#include "filehandler.h"
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <entry.h>
#include <filesystem>
#include <ranges>
#include <string>
#include <vector>

std::vector<Entry> FileHandler::getFolderContent() const
{

  auto filter = [&](const std::filesystem::directory_entry& entry) { return options.showHiddenFiles || !entry.path().filename().native().starts_with("."); };
  auto transform = [&](const std::filesystem::directory_entry& entry) -> Entry {
    const std::string filename = entry.path().filename().string();
    const uintmax_t fileSize = entry.is_directory() ? 4096 : entry.file_size();
    const std::chrono::time_point filetime = entry.last_write_time();
    return { .entryName = filename,
      .entryGroup = fileSystem.getFileGroup(filename.c_str()),
      .userGroup = fileSystem.getFileUser(filename.c_str()),
      .bytesize = fileSize,
      .lastWriteTime = std::chrono::clock_cast<std::chrono::system_clock>(entry.last_write_time()),
      .type = getFileType(entry),
      .numHardLinks = fileSystem.getNumHardLinks(filename.c_str()) };
  };
  auto entries = std::filesystem::directory_iterator{ ".", std::filesystem::directory_options::skip_permission_denied } | std::views::filter(filter)
                 | std::views::transform(transform) | std::ranges::to<std::vector>();

  std::ranges::sort(
    entries,
    [](const std::string& entry1, const std::string& entry2) {
      return std::ranges::lexicographical_compare(entry1 | std::views::transform(::tolower), entry2 | std::views::transform(::tolower));
    },
    &Entry::entryName);
  return entries;
}
