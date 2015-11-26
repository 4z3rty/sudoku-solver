#ifndef SUDOKU_GRID_HH_
# define SUDOKU_GRID_HH_

# include <cstdint>
# include <iostream>
# include "ASudokuGrid.hh"

class SudokuGrid : public ASudokuGrid<uint16_t>
{
public:
  static uint16_t const AllPossibilities = 511;

public:
  SudokuGrid(void);
  SudokuGrid(uint16_t grid[9][9]);
  SudokuGrid(SudokuGrid const &);
  SudokuGrid &operator=(SudokuGrid &);

  virtual ~SudokuGrid(void) {}

  virtual bool operator==(ASudokuGrid const& other);
  virtual bool operator!=(ASudokuGrid const& other);

  virtual void reset(void);

  char getAlphaValue(unsigned int i, unsigned int j) const;
  virtual void display(void) const;
  void debugDisplay(void) const;
};

std::ostream& operator<<(std::ostream& output, SudokuGrid const& grid);

#endif // !SUDOKU_GRID_HH_
