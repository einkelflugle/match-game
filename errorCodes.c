#include <stdio.h>
#include "errorCodes.h"

int exit_with_message(ErrorCode code) {
  switch(code) {
    case E_OK:
      break;
    case E_INCORRECT_ARGUMENTS:
      fprintf(stderr, "%s\n", "Usage: match height width filename");
      break;
    case E_INVALID_GRID_DIMENSIONS:
      fprintf(stderr, "%s\n", "Invalid grid dimensions");
      break;
    case E_INVALID_GRID_FILE:
      fprintf(stderr, "%s\n", "Invalid grid file");
      break;
    case E_UNREADABLE_GRID_CONTENTS:
      fprintf(stderr, "%s\n", "Error reading grid contents");
      break;
  }
  return code;
}

