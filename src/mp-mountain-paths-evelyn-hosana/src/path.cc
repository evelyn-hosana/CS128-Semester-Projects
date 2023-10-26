#include "path.hpp"

#include <stdexcept>
#include <vector>

// Initializes the primitive data members with their respective values from
// arguments Initializes path_ std::vector<size_t> of length elements.
Path::Path(size_t length, size_t starting_row):
    length_(length), starting_row_(starting_row) {
  path_.push_back(length);
}

// Returns the length_.
size_t Path::Length() const { return length_; }

// Returns the starting_row_.
size_t Path::StartingRow() const { return starting_row_; }

// Returns the ele_change_.
unsigned int Path::EleChange() const { return ele_change_; }

// Increments ele_change_ by value (must be positive).
void Path::IncEleChange(unsigned int value) {
  if (value < 0) {
    throw std::invalid_argument("Incrementation cannot be negative");
  }
  ele_change_ = value++;
}

// Returns reference to const to path_
const std::vector<size_t>& Path::GetPath() const { return path_; }

// Assigns the value of row (path_.at(col) will evaluate to row)
void Path::SetLoc(size_t col, size_t row) { path_.at(col) = row; }