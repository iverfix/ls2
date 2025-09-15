#include "filehandler.h"
#include "stringFormater.h"
#include <algorithm>
#include <filesystem>
#include <string>
#include <vector>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <cmath>

std::vector<std::filesystem::directory_entry> FileHandler::getFileList()
{

  std::vector<std::filesystem::directory_entry> paths{};
  for (auto const& entry : std::filesystem::directory_iterator{ "." }) {
    paths.push_back(entry);
  }

  return paths;
}



void FileHandler::generateBalancedGrid(){

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  const int terminalRows = w.ws_row;
  const int terminalColumns = w.ws_col;

  std::vector<std::filesystem::directory_entry> paths = getFileList();
  size_t maxPathLength = std::ranges::max(paths, {}, [](std::filesystem::directory_entry& dirEntry){ return dirEntry.path().lexically_normal().string().size();}).path().lexically_normal().string().length();

  const int numCols = terminalColumns/(maxPathLength + columnPadding);
  const int numRows = std::ceil(static_cast<double>(paths.size()) / numCols);

  std::cout << "Num rows: " << numRows << std::endl;

  std::vector<int> columnPaddingPerRow{};

for (int column = 0; column < numCols; ++column){
  int maxValue{0};
  for (int row = 0; row < numRows; ++row) {
      size_t flattenedIndex = numRows*column + row;
      if (flattenedIndex >= paths.size()) break;
      if ( paths[flattenedIndex].path().lexically_normal().string().size() > maxValue){
        maxValue = paths[flattenedIndex].path().lexically_normal().string().size();
      }
    }
  columnPaddingPerRow.push_back(maxValue);
  }

  for (int row = 0; row < numRows; ++row) {
    for (int column = 0; column < numCols; ++column){

      size_t flattenedIndex = numRows*column + row;
     
      if (flattenedIndex >= paths.size()) break;

      size_t paddingLength = columnPadding + columnPaddingPerRow[column] - paths[numRows*column + row].path().lexically_normal().string().size();
      std::cout << stringFormater.colorFileType(paths[numRows*column + row]) << std::string(paddingLength, ' ');

    }
    std::cout << "\n";
  }
}
