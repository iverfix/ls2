#include "display.h"
#include "filehandler.h"
#include <algorithm>
#include <asm-generic/ioctls.h>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

void Display::generatePermissionFileList() const
{
  for (const auto& entry : fileHandler.getFileList()) {
    std::cout << entry.userGroup << " " << entry.entryGroup << " " << entry.bytesize << " " << entry.lastWriteTime << " " << entry.entryName << '\n';
  }
}

void Display::generateBalancedGrid() const
{

  struct winsize window = {};
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);// NOLINT(hicpp-vararg, cppcoreguidelines-pro-type-vararg)
  const int terminalColumns = window.ws_col;

  std::vector<Entry> directory_entries = fileHandler.getFileList();
  std::vector<std::string> paths{};
  paths.reserve(directory_entries.size());

  for (const auto& entry : directory_entries) { paths.push_back(entry.entryName); }

  const size_t maxPathLength = std::ranges::max(paths, {}, [](const std::string& element) { return element.size(); }).size();

  const int numCols = static_cast<int>(terminalColumns) / (static_cast<int>(maxPathLength) + columnPadding);
  const int numRows = std::ceil(static_cast<double>(paths.size()) / numCols);

  std::vector<size_t> columnWidth(numCols, 0);

  for (auto&& [index, path] : std::views::enumerate(paths)) {
    const size_t columnNumber = index / numRows;
    columnWidth[columnNumber] = std::max(columnWidth[columnNumber], path.size());
  }

  for (const int row : std::views::iota(0, numRows)) {
    for (const int column : std::views::iota(0, numCols)) {

      const size_t flattenedIndex = (numRows * column) + row;

      if (flattenedIndex >= directory_entries.size()) { break; }

      const size_t paddingLength = columnPadding + columnWidth[column] - paths[flattenedIndex].size();
      std::cout << stringFormater.colorFileType(directory_entries[flattenedIndex]) << std::string(paddingLength, ' ');
    }
    std::cout << "\n";
  }
}
