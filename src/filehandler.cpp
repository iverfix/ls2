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
  for (auto const& entry : std::filesystem::directory_iterator{ ".", std::filesystem::directory_options::skip_permission_denied }) {
    // TODO: Filter with ranges
    if (!options.showHiddenFiles && entry.path().filename().string().starts_with(".")) { continue; }

    const uintmax_t fileSize = entry.is_directory() ? 4096 : entry.file_size();
    const std::string userGroup = fileSystem.getFileUser(entry.path().filename().string().data());
    const std::string entryGroup = fileSystem.getFileGroup(entry.path().filename().string().data());
    std::chrono::month();
    paths.push_back({ entry.path().filename().string(), entryGroup, userGroup, fileSize, 0, getFileType(entry) });
  }

  std::ranges::sort(paths, {}, &Entry::entryName);

  return paths;
}
