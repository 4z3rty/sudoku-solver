#include "SudokuSolver.hh"

unsigned int SudokuSolver::getNbrSetBits(uint16_t value) const
{
  value -= ((value >> 1) & 0x55555555);
  value = (value & 0x33333333) + ((value >> 2) & 0x33333333);
  value = (value + (value >> 4)) & 0x0F0F0F0F;
  value += (value >> 8);
  value += (value >> 16);
  return value & 0x0000003F;
}

inline bool SudokuSolver::hasOnlyOneBitSet(uint16_t possibility) const
{
  return possibility && !(possibility & (possibility - 1));
}

void SudokuSolver::removePossibilityOnRow(uint16_t possibility,
  SudokuGrid &grid, unsigned int i)
{
  for (unsigned int j = 0; j < 9; j++) {
    grid[i][j] &= ~possibility;
  }
}

void SudokuSolver::removePossibilityOnColumn(uint16_t possibility,
  SudokuGrid &grid, unsigned int j)
{
  for (unsigned int i = 0; i < 9; i++) {
    grid[i][j] &= ~possibility;
  }
}

void SudokuSolver::removePossibilityOnBlock(uint16_t possibility,
  SudokuGrid &grid, unsigned int i, unsigned int j)
{
  unsigned int iMin = i - (i % 3);
  unsigned int jMin = j - (j % 3);

  for (unsigned int _i = iMin; _i < iMin + 3; _i++) {
    for (unsigned int _j = jMin; _j < jMin + 3; _j++) {
      grid[_i][_j] &= ~possibility;
    }
  }
}

void SudokuSolver::removePossibility(uint16_t possibility,
  SudokuGrid &grid, unsigned int i, unsigned int j)
{
  grid[i][j] = 0;
  removePossibilityOnRow(possibility, grid, i);
  removePossibilityOnColumn(possibility, grid, j);
  removePossibilityOnBlock(possibility, grid, i, j);
  grid[i][j] = possibility;
}

void SudokuSolver::findUnique(SudokuGrid &grid)
{
  for (unsigned int i = 0; i < 9; i++) {
    for (unsigned int j = 0; j < 9; j++) {
      if (hasOnlyOneBitSet(grid[i][j])) {
        removePossibility(grid[i][j], grid, i, j);
      }
    }
  }
}

void SudokuSolver::findCaseWithLessPossibilities(SudokuGrid const& grid,
  unsigned int &iMin, unsigned int &jMin)
{
  unsigned int nbrSetBits = 0;
  unsigned int minSetBits = 9;

  for (unsigned int i = 0; i < 9; i++) {
    for (unsigned int j = 0; j < 9; j++) {
      if (!hasOnlyOneBitSet(grid[i][j])) {
        nbrSetBits = getNbrSetBits(grid[i][j]);
        if (nbrSetBits < minSetBits) {
          iMin = i;
          jMin = j;
          minSetBits = nbrSetBits;
        }
      }
    }
  }
}

bool SudokuSolver::iterateForeachPossibilities(SudokuGrid &grid,
  unsigned int iMin, unsigned int jMin)
{
  for (uint16_t k = 0, value = grid[iMin][jMin];
    value != 0; k++, value >>= 1) {
    if (value & 1) {
      SudokuGrid tmp = SudokuGrid(grid);
      tmp[iMin][jMin] = (1 << k);
      removePossibility(tmp[iMin][jMin], tmp, iMin, jMin);
      solve(tmp);
      if (isSolved(tmp)) {
        grid = tmp;
        return true;
      }
    }
  }
  return false;
}

bool SudokuSolver::isSolved(SudokuGrid const& grid) const
{
  for (unsigned int i = 0; i < 9; i++) {
    for (unsigned int j = 0; j < 9; j++) {
      if (!hasOnlyOneBitSet(grid[i][j])) {
        return false;
      }
    }
  }
  return true;
}

bool SudokuSolver::solve(SudokuGrid &grid)
{
  if (isSolved(grid)) {
    return true;
  }

  findUnique(grid);

  if (isSolved(grid)) {
    return true;
  }

  unsigned int iMin = 0, jMin = 0;

  findCaseWithLessPossibilities(grid, iMin, jMin);
  if (iterateForeachPossibilities(grid, iMin, jMin))
    return true;
  return false;
}
