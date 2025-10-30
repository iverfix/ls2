#pragma once
#include "ArgumentParser.h"
#include "Entry.h"
#include "IFileHandler.h"
#include "StringFormater.h"
#include <memory>
#include <sstream>
#include <utility>

class Display
{

public:
  explicit Display(std::shared_ptr<IFileHandler> handler) : fileHandler(std::move(handler)) {};
  void generatePermissionFileList(const LongListFormatOptions& options) const;
  void generateBalancedGrid() const;

private:
  static constexpr int columnPadding{ 2 };
  std::shared_ptr<IFileHandler> fileHandler;
  StringFormater stringFormater{};
  [[nodiscard]] std::ostringstream buildLongFormatString(const Entry& entry, const LongListFormatOptions& options, const int byteSizeLength) const;
};
