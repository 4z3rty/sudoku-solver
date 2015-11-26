#include <iostream>
#include <bitset>
#include "SudokuGrid.hh"

SudokuGrid::SudokuGrid(void)
{
  reset();
}

SudokuGrid::SudokuGrid(uint16_t grid[9][9])
{
  for (unsigned int i = 0; i < 9; i++) {
    for (unsigned int j = 0; j < 9; j++) {
      _grid[i][j] = grid[i][j];
    }
  }
}

SudokuGrid::SudokuGrid(SudokuGrid const &sudokuGrid)
{
  for (unsigned int i = 0; i < 9; i++) {
    for (unsigned int j = 0; j < 9; j++) {
      _grid[i][j] = sudokuGrid._grid[i][j];
    }
  }
}

SudokuGrid& SudokuGrid::operator=(SudokuGrid &sudokuGrid)
{
  if (&sudokuGrid != this) {
    for (unsigned int i = 0; i < 9; i++) {
      for (unsigned int j = 0; j < 9; j++) {
        _grid[i][j] = sudokuGrid._grid[i][j];
      }
    }
  }
  return *this;
}

bool SudokuGrid::operator==(ASudokuGrid const& other)
{
  const SudokuGrid *o = dynamic_cast<const SudokuGrid*>(&other);

  if (!o)
    return false;
  for (unsigned int i = 0; i < 9; i++) {
    for (unsigned int j = 0; j < 9; j++) {
      if (_grid[i][j] != o->_grid[i][j])
        return false;
    }
  }
  return true;
}

bool SudokuGrid::operator!=(ASudokuGrid const& other)
{
  return !(*this == other);
}

void SudokuGrid::reset(void)
{
  for (unsigned int i = 0; i < 9; i++) {
    for (unsigned int j = 0; j < 9; j++) {
      _grid[i][j] = SudokuGrid::AllPossibilities;
    }
  }
}

char SudokuGrid::getAlphaValue(unsigned int i, unsigned int j) const
{
  uint16_t value = _grid[i][j];
  unsigned int k = 0;
  unsigned int nbrSetBits = 0;

  while (value != 0) {
    if (value & 1) {
      nbrSetBits++;
    }
    value >>= 1;
    k++;
  }
  if (nbrSetBits == 1) {
    return k + '0';
  } else {
    return ' ';
  }
}

void SudokuGrid::display(void) const
{
  std::cout << *this;
}

void SudokuGrid::debugDisplay(void) const
{
  std::bitset<10> value;
  for (unsigned int i = 0; i < 9; i++) {
    for (unsigned int j = 0; j < 9; j++) {
      value = _grid[i][j];
      std::cout << value;
      if (j == 2 || j == 5) {
        std::cout << " | ";
      } else {
        std::cout << " ";
      }
    }
    if (i == 2 || i == 5) {
      std::cout << std::endl << std::string(102, '-');
    }
    std::cout << std::endl;
  }
}

std::ostream& operator<<(std::ostream& output, SudokuGrid const& grid)
{
  for (unsigned int i = 0; i < 9; i++) {
    for (unsigned int j = 0; j < 9; j++) {
      output << grid.getAlphaValue(i, j);
      if (j == 2 || j == 5) {
        output << " | ";
      } else {
        output << " ";
      }
    }
    if (i == 2 || i == 5) {
      output << std::endl << std::string(21, '-');
    }
    output << std::endl;
  }
  return output;
}
