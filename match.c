#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errorCodes.h"
#include "gridFile.h"
#include "grid.h"

// Minimum number of rows/columns in a valid grid
#define MIN_GRID_DIMENSION 1

// Maximum number of rows/columns in a valid grid
#define MAX_GRID_DIMENSION 1000

void play_game(Grid* grid) {
  while (has_legal_moves(grid)) {
    print_grid(grid, stdout);
    int row, col;
    while (true) {
      printf("> ");
      char buf[256];
      if (fgets(buf, 256, stdin) == NULL) {
        fprintf(stderr, "End of user input\n");
        free_grid(grid);
        return;
      }
      if (sscanf(buf, "%d %d", &row, &col) == 2) {
        // Check if the cell coordinates entered are out of bounds
        if (row < 0 || row >= grid->rows || col < 0 || col >= grid->cols) {
          continue;
        }
        if (process_move(grid, row, col)) {
          break;
        } else {
          continue;
        }
      }
      if (strstr(buf, "w")) {
        // Write grid to file
        printf("Written to file\n");
      }
    }
  }
  print_grid(grid, stdout);
  printf("No moves left\n");
  free_grid(grid);
}

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

  play_game(grid);

  return 0;
}
