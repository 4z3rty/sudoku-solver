# Sudoku solver
A sudoku solver written in C++ that uses a backtracking algorithm and bit manipulation.

## How to use
```shell
make
cat puzzles/* | ./sudoku-solver
```

## More information

This solver uses a backtracking algorithm but before starting the recursion, it finds the case with the least amount of branches. To do that, it stores each cell of the grid in an uint16_t. Each possible digit being represented by a bit.

i.e.:
```
2:          00000000 00000010
7:          00000000 01000000
3, 4 and 6: 00000000 00101100
0:          00000001 11111111
```

## License
The MIT License (MIT) - see LICENSE for more details
