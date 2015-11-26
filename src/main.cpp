#include <cstdint>
#include <iostream>
#include "SudokuGrid.hh"
#include "SudokuSolver.hh"

int main(void)
{
  SudokuSolver ss = SudokuSolver();
  SudokuGrid sg = SudokuGrid();
  unsigned int j = 0;

  for (std::string line; std::getline(std::cin, line); j++) {
    if (j > 8) {
        j = 0;
    }
    for (unsigned int i = 0; i < 9; i++) {
        char c = line[i * 2] - '0';
        if (c > 0 && c <= 9) {
          sg[j][i] = 1 << (c - 1);
        }
    }
    if (j == 8) {
      if (ss.solve(sg)) {
        std::cout << sg << std::endl;
      } else {
        std::cout << "Puzzle is not solvable." << std::endl;
      }
      sg.reset();
    }
  }

  std::cout << "Sudoku solver - Copyright (c) 2015 Romain Vermot" << std::endl;
  return 0;
}
