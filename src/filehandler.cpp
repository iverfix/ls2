#include "filehandler.h"
#include "stringFormater.h"
#include <filesystem>
#include <string>
#include <vector>


std::vector<std::string> FileHandler::getFileList()
{

  std::vector<std::string> paths{};
  for (auto const& entry : std::filesystem::directory_iterator{ "." }) {
    paths.push_back(stringFormater.colorFileType(stringFormater.prunePathString(entry.path()), entry));
  }

  return paths;
}
