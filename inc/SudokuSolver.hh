#ifndef SUDOKU_SOLVER_HH_
# define SUDOKU_SOLVER_HH_

# include "SudokuGrid.hh"
# include "ISudokuSolver.hh"

class SudokuSolver : public ISudokuSolver
{
private:
  unsigned int getNbrSetBits(uint16_t value) const;
  inline bool hasOnlyOneBitSet(uint16_t possibility) const;

  void removePossibilityOnRow(uint16_t possibility,
    SudokuGrid &grid, unsigned int i);
  void removePossibilityOnColumn(uint16_t possibility,
    SudokuGrid &grid, unsigned int j);
  void removePossibilityOnBlock(uint16_t possibility,
    SudokuGrid &grid, unsigned int i, unsigned int j);
  void removePossibility(uint16_t possibility,
    SudokuGrid &grid, unsigned int i, unsigned int j);

  void findUnique(SudokuGrid &grid);
  void findCaseWithLessPossibilities(SudokuGrid const& grid,
    unsigned int &iMin, unsigned int &jMin);
  bool iterateForeachPossibilities(SudokuGrid &grid,
    unsigned int iMin, unsigned int jMin);

public:
  virtual ~SudokuSolver() {}
  virtual bool isSolved(SudokuGrid const& grid) const;
  virtual bool solve(SudokuGrid &grid);
};

#endif // !SUDOKU_SOLVER_HH_
