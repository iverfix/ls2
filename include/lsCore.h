#include "argumentParser.h"
#include "display.h"
#include <utility>

class LsCore
{

public:
  explicit LsCore(UserOptions options) : options(std::move(options)), display(Display(options)) {}
  void SetOutput() const;

private:
  Display display;
  UserOptions options{};
};
