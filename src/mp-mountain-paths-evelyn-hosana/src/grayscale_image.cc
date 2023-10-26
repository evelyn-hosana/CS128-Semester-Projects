#include "grayscale_image.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Default constructor
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  width_ = dataset.Width();
  height_ = dataset.Height();
  int max_ele = dataset.MaxEle();
  int min_ele = dataset.MinEle();
  std::vector<std::vector<Color>> two_dimensional_vector;
  std::vector<Color> vector_of_colors;
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      int elevation_point = dataset.DatumAt(i, j);
      int shade_of_gray = 0;
      if (min_ele != max_ele) {
        shade_of_gray = (int)std::round(((double)elevation_point - (double)min_ele) / ((double)max_ele - (double)min_ele) * kMaxColorValue);
      }
      Color shade(shade_of_gray, shade_of_gray, shade_of_gray);
      vector_of_colors.push_back(shade);
    }
    two_dimensional_vector.push_back(vector_of_colors);
    vector_of_colors.clear();
  }
  image_ = two_dimensional_vector;
}

// Parameterized constructor
GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height): GrayscaleImage(ElevationDataset(filename, width, height)) {}

// Returns the width of the image
size_t GrayscaleImage::Width() const { return width_; }

// 	Returns the height of the image
size_t GrayscaleImage::Height() const { return height_; }

// Returns the value stored in kMaxColorValue
unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }

// Returns the Color at row col by reference to const
const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_.at(row).at(col);
}

// Returns reference to const to image_
const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}

// Writes out image_ in plain PPM format; filename is name
void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  if(!ofs.is_open()) {
    throw std::runtime_error("File is not open!");
  }
  ofs << "P3" << std::endl;
  ofs << width_ << " " << height_ << std::endl;
  ofs << kMaxColorValue << std::endl;
  for (int i = 0; i < (int)height_; i++) {
    for (int j = 0; j < (int)width_; j++) {
    Color color = ColorAt(i, j);
    ofs << color.Red() << " " << color.Green() << " " << color.Blue() << " ";
    }
    ofs << std::endl;
  }
}