#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "grid.h"

void print_grid(Grid* grid, FILE* out) {
  for (int i = 0; i < grid->rows; i++) {
    for (int j = 0; j < grid->cols; j++) {
      printf("%c", grid->cells[i][j]);
    }
    printf("\n");
  }
}

void free_grid(Grid* grid) {
  for (int i = 0; i < grid->rows; i++) {
    free(grid->cells[i]);
  }
  free(grid->cells);
  free(grid);
}

