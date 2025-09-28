#include "filehandler.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <vector>

std::vector<Entry> FileHandler::getFileList() const
{

  std::vector<Entry> paths{};
  for (auto const& entry : std::filesystem::directory_iterator{ "." }) {
    // TODO: Filter with ranges
    if (!options.showHiddenFiles && entry.path().filename().native().starts_with(".")) { continue; }

    const uintmax_t fileSize = entry.is_directory() ? 4096 : entry.file_size();
    const std::string userGroup = fileSystem.getFileUser(entry.path().filename().native().data());
    const std::string entryGroup = fileSystem.getFileGroup(entry.path().filename().native().data());
    std::chrono::month();
    paths.push_back({ entry.path().filename().native(), entryGroup, userGroup, fileSize, 0, getFileType(entry) });
  }

  std::sort(paths.begin(), paths.end(), [](const auto& entry1, const auto& entry2) { return entry1.entryName < entry2.entryName; });

  return paths;
}
