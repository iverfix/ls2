#include "display.h"
#include "filehandler.h"
#include <algorithm>
#include <asm-generic/ioctls.h>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <filesystem>
#include <iostream>
#include <ranges>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

void Display::generatePermissionFileList()
{
  for (const auto& entry : fileHandler.getFileList()) {
    const uintmax_t fileSize = entry.is_directory() ? 4096 : entry.file_size();
    std::cout << fileSystem.getFileGroup(entry.path().filename().native().data()) << " " << fileSystem.getFileGroup(entry.path().filename().native().data()) << " " << fileSize
              << " " << entry.last_write_time() << " " << entry.path().filename().native() << '\n';
    std::chrono::minutes();
  }
}

void Display::generateBalancedGrid()
{

  struct winsize window = {};
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);// NOLINT(hicpp-vararg, cppcoreguidelines-pro-type-vararg)
  const int terminalColumns = window.ws_col;

  std::vector<std::filesystem::directory_entry> directory_entries = fileHandler.getFileList();
  std::vector<std::string> paths{};
  paths.reserve(directory_entries.size());

  for (const auto& entry : directory_entries) { paths.push_back(entry.path().filename().string()); }

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
