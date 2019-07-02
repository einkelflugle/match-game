#ifndef GRID_H
#define GRID_H

#include <stdbool.h>

#define EMPTY_GRID_CELL '.'

typedef struct Grid {
  // Number of rows (height)
  int rows;
  // Number of columns (width)
  int cols;
  // 2D array of characters of dimension [height][width]
  char** cells;
} Grid;

/**
 * Prints the characters representing the Grid to the given output stream.
 */
void print_grid(Grid* grid, FILE* out);


/**
 * Frees the memory associated with the given Grid.
 */
void free_grid(Grid* grid);

#endif
