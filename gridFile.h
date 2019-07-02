#ifndef GRID_FILE_H_
#define GRID_FILE_H_

#include "grid.h"

/**
 * Loads a Grid from the file with the given filename. If the file could not
 * be found or the grid is invalid, returns a null pointer. On success, returns
 * a pointer to the allocated Grid.
 */
Grid* read_gridfile(const char* filename);

#endif
