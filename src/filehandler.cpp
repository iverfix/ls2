#include "filehandler.h"
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>
#include "argumentParser.h"

std::vector<std::filesystem::directory_entry> FileHandler::getFileList() const 
{
  std::vector<std::filesystem::directory_entry> paths{};
  for (auto const& entry : std::filesystem::directory_iterator{ "." }) { 
    if (!options.showHiddenFiles && entry.path().filename().native().starts_with("."))
      continue;
    paths.push_back(entry); 
  }

  std::sort(paths.begin(), paths.end(), [](const auto& a, const auto& b) { return a.path().filename() < b.path().filename();});
  return paths;
}
