#pragma once
#include "IFileHandler.h"
#include "entry.h"
#include <gmock/gmock.h>
#include <vector>


class MockFileHandler : public IFileHandler
{

public:
  MOCK_METHOD(std::vector<Entry>, getFolderContent, (), (const, override));
};
