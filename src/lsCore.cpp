#include "argumentParser.h"
#include "lsCore.h"


void LsCore::SetOutput() const
{

  if (options.showHiddenFiles) {
    display.generateBalancedGrid();
  } else if (options.showLongFormat) {
    display.generatePermissionFileList();
  } else {
    // TODO: Use a better way of handling user input
    display.generateBalancedGrid();
  }
}
