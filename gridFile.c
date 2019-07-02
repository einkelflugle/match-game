#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "gridFile.h"

#include "grid.h"

Grid* read_gridfile(const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    return NULL;
  }

  // Initialise a block of memory for storing the first row
  int height = 1;
  int width = 1;
  char** rows = (char**) malloc(sizeof(char*) * height);
  char* row = (char*) malloc(sizeof(char) * width);

  int i = 0; // Position in row
  int j = 0; // Position in list of rows
  while (!feof(file)) {
    char c = fgetc(file);
    // Newline signals the end of a row
    if (c == '\n') {
      if (j == 0) {
        width = i;
      }
      rows[j] = row;
      i = 0;
      j++;
    } else if (c == EOF) {
      break;
    } else {
      // c is a regular grid cell character
      // If width is not yet known, realloc the row
      if (j == 0) {
        row = (char*) realloc(row, sizeof(char) * (i + 1));
      } else {
        if (i == 0) {
          // Width is known and this is the start of a new row, alloc it
          row = (char*) malloc(sizeof(char) * width);
        }
      }
      // If this is a new row, realloc the list of rows
      if (i == 0) {
        rows = (char**) realloc(rows, sizeof(char*) * (j + 1));
      }
      row[i] = c;
      i++;
    }
  }
  fclose(file);
  height = j;

  Grid* grid = (Grid*) malloc(sizeof(Grid));
  grid->rows = height;
  grid->cols = width;
  grid->cells = rows;

  return grid;
}

