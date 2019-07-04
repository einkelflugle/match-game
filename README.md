# match-game
A command line game written in C. The specification is taken from the exercise at the end of the CSSE2310 2018 Semester 2 C Tutorial PDF.

## Building
```
$ cd match-game
$ make
```
## Running
```
$ ./match height width filename
```
For example:
```
$ ./match 5 5 grids/grid1.txt
```
At the prompt, enter two space-separated numbers representing the row and column index of the cell you wish to remove, starting from 0, with the top left corner being (0, 0).
To save the current state of the grid to a file, type "w" followed by the name of the file. For example:
```
> whello.txt
```
will write the grid to a file named 'hello.txt'.
