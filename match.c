#include <stdio.h>
#include <stdlib.h>

#include "errorCodes.h"
#include "gridFile.h"
#include "grid.h"

// Minimum number of rows/columns in a valid grid
#define MIN_GRID_DIMENSION 1

// Maximum number of rows/columns in a valid grid
#define MAX_GRID_DIMENSION 1000

int main(int argc, char** argv) {
  if (argc != 4) {
    return exit_with_message(E_INCORRECT_ARGUMENTS);
  }
  long dimensionArg;
  int width, height;

  dimensionArg = strtol(argv[1], NULL, 10);
  if (dimensionArg < MIN_GRID_DIMENSION || dimensionArg > MAX_GRID_DIMENSION) {
    return exit_with_message(E_INVALID_GRID_DIMENSIONS);
  }
  height = (int) dimensionArg;

  dimensionArg = strtol(argv[2], NULL, 10);
  if (dimensionArg < MIN_GRID_DIMENSION || dimensionArg > MAX_GRID_DIMENSION) {
    return exit_with_message(E_INVALID_GRID_DIMENSIONS);
  }
  width = (int) dimensionArg;

  const char* filename = argv[3];
  Grid* grid = read_gridfile(filename);
  if (grid == NULL) {
    return exit_with_message(E_UNREADABLE_GRID_CONTENTS);
  }
  if (grid->rows != height || grid->cols != width) {
    free_grid(grid);
    return exit_with_message(E_UNREADABLE_GRID_CONTENTS);
  }
  print_grid(grid, stdout);
  if (has_legal_moves(grid)) {
    printf("%s\n", "Grid has legal moves.");
  } else {
    printf("%s\n", "Game over: Grid has no legal moves.");
  }
  free_grid(grid);

  return 0;
}
