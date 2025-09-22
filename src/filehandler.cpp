#include "filehandler.h"
#include "argumentParser.h"
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <vector>

std::vector<std::filesystem::directory_entry> FileHandler::getFileList() const
{
  std::vector<std::filesystem::directory_entry> paths{};
  for (auto const& entry : std::filesystem::directory_iterator{ "." }) {
    if (!options.showHiddenFiles && entry.path().filename().native().starts_with(".")) { continue; }
    paths.push_back(entry);
  }

  std::sort(paths.begin(), paths.end(), [](const auto& entry1, const auto& entry2) { return entry1.path().filename() < entry2.path().filename(); });

  return paths;
}
