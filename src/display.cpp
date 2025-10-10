#include "display.h"
#include "entry.h"
#include <algorithm>
#include <asm-generic/ioctls.h>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

void Display::generatePermissionFileList() const {
  auto entries = fileHandler->getFolderContent();
  const Entry max = std::ranges::max(entries, {}, &Entry::bytesize);
  std::ranges::for_each(entries, [&](const Entry& entry) {
    std::chrono::zoned_time local_time{ std::chrono::current_zone(), entry.lastWriteTime };
    std::cout << entry.userGroup << " " << entry.entryGroup << " " << std::setw(static_cast<int>(std::to_string(max.bytesize).size())) << entry.bytesize << " "
              << std::format("{:%b %d %H:%M}", local_time) << " " << stringFormater.colorFileType(entry) << '\n';
  });
}

void Display::generateBalancedGrid() const {

  struct winsize window = {};
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);// NOLINT(hicpp-vararg, cppcoreguidelines-pro-type-vararg)
  const int terminalColumns = window.ws_col;

  std::vector<Entry> directory_entries = fileHandler->getFolderContent();
  auto paths = directory_entries | std::views::transform([](const Entry& entry) { return entry.entryName; });

  if (std::ranges::empty(paths)) { return; }

  const size_t maxPathLength = std::ranges::max(paths, {}, &std::string::size).size();

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

      const size_t paddingLength = columnPadding + columnWidth[column] - directory_entries[flattenedIndex].entryName.size();
      std::cout << stringFormater.colorFileType(directory_entries[flattenedIndex]) << std::string(paddingLength, ' ');
    }
    std::cout << "\n";
  }
}
