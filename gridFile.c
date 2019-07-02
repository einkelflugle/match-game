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
  while (true) {
    char c = fgetc(file);
    if (c == EOF) {
      // c is EOF, the file has been read
      break;
    } else if (c == '\n') {
      // c is a newline, signalling the end of a row
      if (j == 0) {
        // Width is unknown since this is the first row, set it
        width = i;
      } else if (i < width) {
        // Width is known but this row was shorter than it
        for (int p = 0; p < j; p++) {
          free(rows[p]);
        }
        free(row);
        free(rows);
        fclose(file);
        return NULL;
      }
      rows[j] = row;
      i = 0;
      j++;
    } else {
      // c is a regular grid cell character
      // If width is not yet known, realloc the row
      if (j == 0) {
        row = (char*) realloc(row, sizeof(char) * (i + 1));
      } else {
        // Width is known
        if (i == 0) {
          // This is the start of a new row, alloc it
          row = (char*) malloc(sizeof(char) * width);
        } else if (i >= width) {
          // Row is too long
          for (int p = 0; p < j; p++) {
            free(rows[p]);
          }
          free(row);
          free(rows);
          fclose(file);
          return NULL;
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
  if (height == 0) {
    // No lines were read
    free(rows);
    free(row);
    return NULL;
  }

  Grid* grid = (Grid*) malloc(sizeof(Grid));
  grid->rows = height;
  grid->cols = width;
  grid->cells = rows;

  return grid;
}

