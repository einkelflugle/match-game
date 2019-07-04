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

/**
 * Searches the neighbouring cells to the cell at the given row and column
 * position for a matching cell value. If a neighbouring cell is found in the
 * cellsToIgnore array, it is not considered a matching cell.
 * The cellsToIgnore parameter is optional (ie. can be NULL). If null, all
 * neighbours will be considered.
 *
 * Returns true if a matching neighbour cell was found and sets foundRow and
 * foundCol to the position of the found cell.
 *
 * Returns false if no non-ignored neighbours have the same value, and does not
 * change foundRow and foundCol.
 */
bool find_matching_neighbour(Grid* grid, int row, int col, int* const foundRow,
      int* const foundCol, bool* const * const cellsToIgnore);

void print_horizontal_border(int length, FILE* out) {
  fprintf(out, "+");
  for (int i = 0; i < length; ++i) {
    fprintf(out, "-");
  }
  fprintf(out, "+\n");
}

bool find_matching_neighbour(Grid* grid, int row, int col, int* const foundRow,
      int* const foundCol, bool* const * const cellsToIgnore) {
    if (row - 1 >= 0 && grid->cells[row - 1][col] == grid->cells[row][col]) {
      if (cellsToIgnore == NULL || cellsToIgnore[row - 1][col] == false) {
        *foundRow = row - 1;
        *foundCol = col;
        return true;
      }
    }
    if (row + 1 < grid->rows &&
          grid->cells[row + 1][col] == grid->cells[row][col]) {
      if (cellsToIgnore == NULL || cellsToIgnore[row + 1][col] == false) {
        *foundRow = row + 1;
        *foundCol = col;
        return true;
      }
    }
    if (col - 1 >= 0 && grid->cells[row][col - 1] == grid->cells[row][col]) {
      if (cellsToIgnore == NULL || cellsToIgnore[row][col - 1] == false) {
        *foundRow = row;
        *foundCol = col - 1;
        return true;
      }
    }
    if (col + 1 < grid->cols &&
          grid->cells[row][col + 1] == grid->cells[row][col]) {
      if (cellsToIgnore == NULL || cellsToIgnore[row][col + 1] == false) {
        *foundRow = row;
        *foundCol = col + 1;
        return true;
      }
    }
    return false;
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
      int foundRow, foundCol;
      if (find_matching_neighbour(grid, i, j, &foundRow, &foundCol, NULL)) {
        return true;
      }
    }
  }
  return false;
}

bool process_move(Grid* grid, int row, int col) {
  if (grid == NULL) {
    return false;
  }
  int foundRow, foundCol;
  bool** cellsToDelete = (bool**) malloc(sizeof(bool*) * grid->rows);
  for (int i = 0; i < grid->rows; ++i) {
    cellsToDelete[i] = (bool*) malloc(sizeof(bool) * grid->cols);
    for (int j = 0; j < grid->cols; ++j) {
      cellsToDelete[i][j] = false;
    }
  }
  cellsToDelete[row][col] = true;

  if (find_matching_neighbour(grid, row, col, &foundRow, &foundCol,
        cellsToDelete)) {
    bool keepLooking = true;
    while (keepLooking) {
      keepLooking = false;
      for (int i = 0; i < grid->rows; i++) {
        for (int j = 0; j < grid->cols; j++) {
          if (cellsToDelete[i][j] == true) {
            if (find_matching_neighbour(grid, i, j, &foundRow, &foundCol,
                  cellsToDelete)) {
              if (cellsToDelete[foundRow][foundCol] == false) {
                cellsToDelete[foundRow][foundCol] = true;
                keepLooking = true;
              }
            }
          }
        }
      }
    }
    // Delete the cells
    for (int i = 0; i < grid->rows; i++) {
      for (int j = 0; j < grid->cols; j++) {
        if (cellsToDelete[i][j] == true) {
          grid->cells[i][j] = EMPTY_GRID_CELL;
        }
      }
    }
    // Free the memory storing cells to delete
    for (int i = 0; i < grid->rows; i++) {
      free(cellsToDelete[i]);
    }
    free(cellsToDelete);
    // Shift all cells down to fill any vertical gaps
    for (int i = 0; i < grid->rows; i++) {
      // Repeat this process as many times as the number of rows to ensure that
      // there are no outstanding gaps in any column
      for (int row = 1; row < grid->rows; row++) {
        for (int col = 0; col < grid->cols; col++) {
          if (grid->cells[row][col] != EMPTY_GRID_CELL) {
            // Only shift down when there is an empty cell
            continue;
          }
          // The current position is an empty cell, check the cell directly
          // above it to see whether it is empty or not
          if (grid->cells[row - 1][col] == EMPTY_GRID_CELL) {
            continue;
          }
          // The gap has a non-empty cell above it, so swap the two cells
          grid->cells[row][col] = grid->cells[row - 1][col];
          grid->cells[row - 1][col] = EMPTY_GRID_CELL;
        }
      }
    }
    // Shift any empty columns to the left, repeating the process as many times
    // as the number of columns
    for (int i = 0; i < grid->cols; i++) {
      for (int col = 0; col < grid->cols - 1; col++) {
        bool isEmpty = true;
        for (int row = 0; row < grid->rows; row++) {
          if (grid->cells[row][col] != EMPTY_GRID_CELL) {
            isEmpty = false;
            break;
          }
        }
        if (!isEmpty) {
          continue;
        }
        for (int row = 0; row < grid->rows; row++) {
          grid->cells[row][col] = grid->cells[row][col + 1];
          grid->cells[row][col + 1] = EMPTY_GRID_CELL;
        }
      }
    }
    return true;
  } else {
    // Free and exit
    for (int i = 0; i < grid->rows; i++) {
      free(cellsToDelete[i]);
    }
    free(cellsToDelete);
    return false;
  }
}
