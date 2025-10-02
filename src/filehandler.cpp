#include "filehandler.h"
#include <algorithm>
#include <cstdint>
#include <entry.h>
#include <filesystem>
#include <ranges>
#include <vector>

std::vector<Entry> FileHandler::getFolderContent() const
{

  auto filter = [&](const std::filesystem::directory_entry& entry) { return options.showHiddenFiles || !entry.path().filename().string().starts_with("."); };
  auto transform = [&](const std::filesystem::directory_entry& entry) -> Entry {
    std::string filename = entry.path().filename().string();
    const uintmax_t fileSize = entry.is_directory() ? 4096 : entry.file_size();
    return { .entryName = filename,
      .entryGroup = fileSystem.getFileGroup(filename.data()),
      .userGroup = fileSystem.getFileUser(filename.data()),
      .bytesize = fileSize,
      .lastWriteTime = 0,
      .type = getFileType(entry)

    };
  };
  auto entries = std::filesystem::directory_iterator{ ".", std::filesystem::directory_options::skip_permission_denied } | std::ranges::views::filter(filter)
                 | std::views::transform(transform) | std::ranges::to<std::vector>();

  std::ranges::sort(entries, {}, &Entry::entryName);
  return entries;
}
