#include "filehandler.h"
#include "stringFormater.h"
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

std::vector<std::filesystem::directory_entry> FileHandler::getFileList()
{

  std::vector<std::filesystem::directory_entry> paths{};
  for (auto const& entry : std::filesystem::directory_iterator{ "." }) { paths.push_back(entry); }

  return paths;
}


void FileHandler::generateBalancedGrid()
{

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  const int terminalRows = w.ws_row;
  const int terminalColumns = w.ws_col;

  std::vector<std::filesystem::directory_entry> directory_entries = getFileList();
  std::vector<std::string> paths{};
  paths.reserve(directory_entries.size());

  for (const auto& e : directory_entries){
    paths.push_back(e.path().lexically_normal().string());
  }

  size_t maxPathLength = std::ranges::max(paths, {}, [](std::string element) { return element.size(); }).size();

  const int numCols = terminalColumns / (maxPathLength + columnPadding);
  const int numRows = std::ceil(static_cast<double>(paths.size()) / numCols);

  std::vector<int> columnPaddingPerRow{};

  for (int column = 0; column < numCols; ++column) {
    int maxValue{ 0 };
    for (int row = 0; row < numRows; ++row) {
      size_t flattenedIndex = numRows * column + row;
      if (flattenedIndex >= directory_entries.size()) break;
      if (paths[flattenedIndex].size() > maxValue) { maxValue = paths[flattenedIndex].size(); }
    }
    columnPaddingPerRow.push_back(maxValue);
  }

  for (int row = 0; row < numRows; ++row) {
    for (int column = 0; column < numCols; ++column) {

      size_t flattenedIndex = numRows * column + row;

      if (flattenedIndex >= directory_entries.size()) break;

      size_t paddingLength = columnPadding + columnPaddingPerRow[column] - paths[flattenedIndex].size();
      std::cout << stringFormater.colorFileType(directory_entries[flattenedIndex]) << std::string(paddingLength, ' ');
    }
    std::cout << "\n";
  }
}
