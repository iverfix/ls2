#pragma once
#include "Display.h"
#include "Filehandler.h"
#include <memory>
#include <utility>

class LsCore
{

public:
  explicit LsCore(UserOptions options) : options(std::move(options)), display(Display(std::make_shared<FileHandler>(options))) {}
  void SetOutput() const;

private:
  Display display;
  UserOptions options{};
};
