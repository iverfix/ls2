#pragma once
#include "IFileHandler.h"
#include "stringFormater.h"
#include <memory>

class Display
{

public:
  explicit Display(std::shared_ptr<IFileHandler> handler) : fileHandler(std::move(handler)) {};
  void generatePermissionFileList() const;
  void generateBalancedGrid() const;

private:
  int columnPadding{ 2 };
  std::shared_ptr<IFileHandler> fileHandler;
  StringFormater stringFormater{};
};
