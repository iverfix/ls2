#include "Display.h"
#include "ArgumentParser.h"
#include "Entry.h"
#include <algorithm>
#include <asm-generic/ioctls.h>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <format>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

void Display::generatePermissionFileList(const LongListFormatOptions& options) const
{
  const auto entries = fileHandler->getFolderContent();
  if (entries.empty()) { return; }
  const Entry max = std::ranges::max(entries, {}, &Entry::bytesize);
  const auto entryToLongFormatString = [&](const Entry& entry) { std::cout << buildLongFormatString(entry, options, static_cast<int>(std::to_string(max.bytesize).size())).str(); };
  std::ranges::for_each(entries, entryToLongFormatString);
}

std::ostringstream Display::buildLongFormatString(const Entry& entry, const LongListFormatOptions& options, const int byteSizeLength) const
{
  std::ostringstream outputString{};

  if (options.showPermissionString) { outputString << entry.permissionString << " "; }

  if (options.showNumHardLinks) { outputString << entry.numHardLinks << " "; }

  if (options.showUserGroup) { outputString << entry.userGroup << " "; }

  if (options.showOwnerGroup) { outputString << entry.entryGroup << " "; }

  if (options.showBytesize) { outputString << std::setw(byteSizeLength) << entry.bytesize << " "; }

  if (options.showWriteTime) {
    const std::chrono::zoned_time local_time{ std::chrono::current_zone(), entry.lastWriteTime };
    outputString << std::format("{:%b %d %H:%M}", local_time) << " ";
  }

  if (options.showFilename) { outputString << stringFormater.colorFileType(entry); }

  outputString << "\n";

  return outputString;
}

void Display::generateBalancedGrid() const
{

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
