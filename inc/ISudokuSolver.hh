#ifndef ISUDOKU_SOLVER_HH_
# define ISUDOKU_SOLVER_HH_

# include "SudokuGrid.hh"

class ISudokuSolver
{
public:
  virtual ~ISudokuSolver() {}

  virtual bool isSolved(SudokuGrid const& grid) const = 0;
  virtual bool solve(SudokuGrid &grid) = 0;
};

#endif // !ISUDOKU_SOLVER_HH_
