#pragma once
#include "entry.h"
#include <vector>

class IFileHandler
{

public:
  IFileHandler() = default;
  IFileHandler(const IFileHandler&) = default;
  IFileHandler& operator=(const IFileHandler&) = default;
  IFileHandler(IFileHandler&&) = default;
  IFileHandler& operator=(IFileHandler&&) = default;

  virtual ~IFileHandler() = default;
  [[nodiscard]] virtual std::vector<Entry> getFolderContent() const = 0;
};
