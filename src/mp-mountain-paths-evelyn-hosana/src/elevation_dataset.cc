#include "elevation_dataset.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Parameterized constructor (default is defined)
ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height): width_(width), height_(height) {
  std::vector<std::vector<int>> two_dimensional_vector;
  int ifs_values = 0;
  max_ele_ = INT32_MIN;
  min_ele_ = INT32_MAX;
  std::ifstream ifs(filename);
  if (!(ifs.is_open())) {
    throw std::runtime_error("Error opening file!");
  }
  while (ifs.good() && !ifs.bad()) {
    std::vector<int> vector_of_rows;
    for (size_t i = 0; i < width; i++) {
      if (ifs.fail()) {
        throw std::runtime_error("File is corrupted");
      }
      ifs >> ifs_values;
      if (ifs_values > max_ele_) {
        max_ele_ = ifs_values;
      }
      if (ifs_values < min_ele_) {
        min_ele_ = ifs_values;
      }
      vector_of_rows.push_back(ifs_values);
    }
    two_dimensional_vector.push_back(vector_of_rows);
    if (two_dimensional_vector.size() == height) {
      if (ifs >> ifs_values) {
        throw std::runtime_error("Too many elements");
      }
    }
  }
  data_ = two_dimensional_vector;
  ifs.close();
}

// Returns the “width” of the dataset
size_t ElevationDataset::Width() const { return width_; }

// Returns the “height” of the dataset
size_t ElevationDataset::Height() const { return height_; }

// Returns the maximum elevation value observed in the dataset
int ElevationDataset::MaxEle() const { return max_ele_; }

// Returns the minimum elevation value observed in the dataset
int ElevationDataset::MinEle() const { return min_ele_; }

// Returns the value recorded for (row, col)
int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_.at(row).at(col);
}

// Returns reference to const to data_
const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}