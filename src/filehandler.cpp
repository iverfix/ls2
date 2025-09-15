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
#include <ranges>

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
  const int terminalColumns = w.ws_col;

  std::vector<std::filesystem::directory_entry> directory_entries = getFileList();
  std::vector<std::string> paths{};
  paths.reserve(directory_entries.size());

  for (const auto& e : directory_entries){
    paths.push_back(e.path().lexically_normal().string());
  }

  size_t maxPathLength = std::ranges::max(paths, {}, [](const std::string& element) { return element.size(); }).size();

  const int numCols = terminalColumns / (maxPathLength + columnPadding);
  const int numRows = std::ceil(static_cast<double>(paths.size()) / numCols);

  std::vector<size_t> columnWidth(numCols, 0);

  for (size_t index : std::ranges::iota_view(size_t{0}, paths.size())){
    const int columnNumber = index / numRows;
    columnWidth[columnNumber] = std::max(columnWidth[columnNumber], paths[index].size());
  }

  for (int row : std::ranges::iota_view(0, numRows)) {
    for (int column : std::ranges::iota_view(0, numCols)) {

      size_t flattenedIndex = numRows * column + row;

      if (flattenedIndex >= directory_entries.size()) break;

      size_t paddingLength = columnPadding + columnWidth[column] - paths[flattenedIndex].size();
      std::cout << stringFormater.colorFileType(directory_entries[flattenedIndex]) << std::string(paddingLength, ' ');
    }
    std::cout << "\n";
  }
}
