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
#include "argumentParser.h"



FileHandler::FileHandler(UserOptions options) : options(options) {}

std::vector<std::filesystem::directory_entry> FileHandler::getFileList()
{
  std::vector<std::filesystem::directory_entry> paths{};
  for (auto const& entry : std::filesystem::directory_iterator{ "." }) { 
    if (!options.showHiddenFiles && entry.path().filename().string().starts_with("."))
      continue;
    paths.push_back(entry); }

  std::sort(paths.begin(), paths.end(), [](const auto& a, const auto& b) { return a.path().filename() < b.path().filename();});

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
    paths.push_back(e.path().filename().string());
  }

  size_t maxPathLength = std::ranges::max(paths, {}, [](const std::string& element) { return element.size(); }).size();

  const int numCols = terminalColumns / (maxPathLength + columnPadding);
  const int numRows = std::ceil(static_cast<double>(paths.size()) / numCols);

  std::vector<size_t> columnWidth(numCols, 0);

  for (auto&& [index, path] : std::views::enumerate(paths)){
    const size_t columnNumber = index / numRows;
    columnWidth[columnNumber] = std::max(columnWidth[columnNumber], path.size());
  }

  for (int row : std::views::iota(0, numRows)) {
    for (int column : std::views::iota(0, numCols)) {

      size_t flattenedIndex = numRows * column + row;

      if (flattenedIndex >= directory_entries.size()) break;

      size_t paddingLength = columnPadding + columnWidth[column] - paths[flattenedIndex].size();
      std::cout << stringFormater.colorFileType(directory_entries[flattenedIndex]) << std::string(paddingLength, ' ');
    }
    std::cout << "\n";
  }
}
