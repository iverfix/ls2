#include "argumentParser.h"
#include "lsCore.h"


void LsCore::SetOutput() const
{

  if (options.showHiddenFiles) {
    display.generatePermissionFileList();
  } else if (options.showLongFormat) {
    display.generateBalancedGrid();
  } else {
    // TODO: Use a better way of handling user input
    display.generateBalancedGrid();
  }
}
