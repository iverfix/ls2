#include "stringFormater.h"
#include <algorithm>
#include <string>

std::string StringFormater::formatPathString(std::string inputString)
{
  auto it = std::find_if(inputString.begin(), inputString.end(), [](unsigned char c) { return std::isalnum(c); });

  return (it != inputString.end()) ? std::string(it, inputString.end()) : "";
}
