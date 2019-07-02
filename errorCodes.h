#ifndef ERROR_CODES_H
#define ERROR_CODES_H

typedef enum ErrorCode {
  E_OK = 0,
  E_INCORRECT_ARGUMENTS = 1,
  E_INVALID_GRID_DIMENSIONS = 2,
  E_INVALID_GRID_FILE = 3,
  E_UNREADABLE_GRID_CONTENTS = 4
} ErrorCode;

/**
 * Returns the integer corresponding to the given ErrorCode and prints a
 * helpful error message to stderr if applicable.
 *
 * Parameters:
 *   code (ErrorCode) - error code to exit with
 */
int exit_with_message(ErrorCode code);

#endif
