#ifndef GRID_H_
#define GRID_H_

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

/**
 * Returns true if there are legal moves to be made on the given Grid.
 */
bool has_legal_moves(Grid* grid);

/**
 * Alters the given grid for a player removing the cell at the given row and
 * column position, starting from (0,0) in the top left corner.
 * Returns true if the move resulted in a change in the board; false if no
 * cells were altered.
 */
bool process_move(Grid* grid, int row, int col);

#endif
