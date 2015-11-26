#ifndef ASUDOKU_GRID_HH_
# define ASUDOKU_GRID_HH_

# include <array>

template <typename T>
class ASudokuGrid
{
protected:
  template <typename U>
  class SudokuGridRow
  {
  private:
    std::array<U, 9> _row;
  public:
    const U operator[](unsigned int j) const { return _row[j % 9]; }
    U& operator[](unsigned int j) { return _row[j % 9]; }
  };

protected:
  std::array<SudokuGridRow<T>, 9> _grid;

public:
  virtual ~ASudokuGrid(void) {}

  virtual const SudokuGridRow<uint16_t> operator[](int i) const { return _grid[i % 9]; }
  virtual SudokuGridRow<uint16_t>& operator[](int i) { return _grid[i % 9]; }

  virtual bool operator==(ASudokuGrid const& other) = 0;
  virtual bool operator!=(ASudokuGrid const& other) = 0;

  virtual void reset(void) = 0;
  virtual void display(void) const = 0;
};

#endif // !ASUDOKU_GRID_HH_
