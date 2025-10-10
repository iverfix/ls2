#include "lsCore.h"

void LsCore::SetOutput() const {

  if (options.showLongFormat) {
    display.generatePermissionFileList();
  } else {
    // TODO: Use a better way of handling user input
    // TODO: This is the case for both default and the showHiddenFiles
    display.generateBalancedGrid();
  }
}
