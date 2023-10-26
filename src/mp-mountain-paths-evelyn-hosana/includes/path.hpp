#ifndef PATH_H
#define PATH_H

#include <cstdlib>  // for size_t
#include <vector>

class Path {
public:
  /*
  Initializes the primitive data members with their respective values from arguments; 
  initializes path_ std::vector<size_t> of length elements.
  */
  Path(size_t length, size_t starting_row);
  size_t Length() const; // Returns the length_.
  size_t StartingRow() const; // Returns the starting_row_.
  unsigned int EleChange() const; // Returns the ele_change_.
  void IncEleChange(unsigned int value); // Increments ele_change_ by value (must be positive).
  const std::vector<size_t>& GetPath() const; // Returns reference to const to path_
  void SetLoc(size_t col, size_t row); // Assigns the value of row (path_.at(col) will evaluate to row)

private:
  size_t length_; // Number of columns in path_.
  size_t starting_row_; // Row that this path begins from.
  /*
  1 row by length_ columns. This std::vector<int> encodes the path starting at row 
  starting_row across the image (from “left” to “right”). Each “index” of path_ 
  represents a column and stores the row index of the path as it traverses that column.
  */
  std::vector<size_t> path_;
  unsigned int ele_change_ = 0; // Total elevation change “experienced” by a person walking the path.
};

#endif