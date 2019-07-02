#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "grid.h"

/*
 * HELPER METHODS
 */

/**
 * Prints a horizontal border for a grid of 'length' columns wide to the given
 * output stream.
 */
void print_horizontal_border(int length, FILE* out);

void print_horizontal_border(int length, FILE* out) {
  fprintf(out, "+");
  for (int i = 0; i < length; ++i) {
    fprintf(out, "-");
  }
  fprintf(out, "+\n");
}

/*
 * PUBLIC METHODS
 */

void print_grid(Grid* grid, FILE* out) {
  print_horizontal_border(grid->cols, out);
  for (int i = 0; i < grid->rows; i++) {
    fprintf(out, "|");
    for (int j = 0; j < grid->cols; j++) {
      fprintf(out, "%c", grid->cells[i][j]);
    }
    fprintf(out, "|\n");
  }
  print_horizontal_border(grid->cols, out);
}

void free_grid(Grid* grid) {
  for (int i = 0; i < grid->rows; i++) {
    free(grid->cells[i]);
  }
  free(grid->cells);
  free(grid);
}

bool has_legal_moves(Grid* grid) {
  for (int i = 0; i < grid->rows; i++) {
    for (int j = 0; j < grid->cols; j++) {
      if (grid->cells[i][j] == EMPTY_GRID_CELL) {
        continue;
      }
      if (i - 1 >= 0 && grid->cells[i - 1][j] == grid->cells[i][j]) {
        return true;
      }
      if (i + 1 < grid->rows && grid->cells[i + 1][j] == grid->cells[i][j]) {
        return true;
      }
      if (j - 1 >= 0 && grid->cells[i][j - 1] == grid->cells[i][j]) {
        return true;
      }
      if (j + 1 < grid->cols && grid->cells[i][j + 1] == grid->cells[i][j]) {
        return true;
      }
    }
  }
  return false;
}
