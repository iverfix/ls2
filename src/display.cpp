#include "display.h"
#include "filehandler.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <ranges>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

void Display::generatePermissionFileList()
{
  for (const auto& e : fileHandler.getFileList()) {
    const int fileSize = e.is_directory() ? 4096 : e.file_size();
    std::cout << fileSystem.getFileGroup(e.path().filename().native().data()) << " " << fileSystem.getFileGroup(e.path().filename().native().data()) << " " << fileSize << " "
              << e.last_write_time() << " " << e.path().filename().native() << '\n';
  }
}

void Display::generateBalancedGrid()
{

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  const int terminalColumns = w.ws_col;

  std::vector<std::filesystem::directory_entry> directory_entries = fileHandler.getFileList();
  std::vector<std::string> paths{};
  paths.reserve(directory_entries.size());

  for (const auto& e : directory_entries) { paths.push_back(e.path().filename().string()); }

  size_t maxPathLength = std::ranges::max(paths, {}, [](const std::string& element) { return element.size(); }).size();

  const int numCols = terminalColumns / (maxPathLength + columnPadding);
  const int numRows = std::ceil(static_cast<double>(paths.size()) / numCols);

  std::vector<size_t> columnWidth(numCols, 0);

  for (auto&& [index, path] : std::views::enumerate(paths)) {
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
